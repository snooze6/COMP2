# -*- coding: utf-8 -*-
import os
import platform

defname = 'dlang.lex'

if __name__ == "__main__":
    if os.path.exists(defname):
        os.remove(defname)

    dest = open(defname, 'w')

    dest.write(
        """%{
    #include <stdio.h>
    #include "../external/model/hash.h"
    #include "../config.h"

    int nested_depth = 0;
    int identifiers = 500;
    line = 1;
%}

%option caseless

D			[0-9_]
L			[a-zA-Z_]
T			[a-zA-Z0-9_.]
A			[a-zA-Z]
B           [01_]
H			[a-fA-F0-9_]
E			[Ee][+-]?{D}+
EE			[Ee][+-]?{T}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
LP                      "{"
RP                      "}"
SM                      ";"
CM                      "//"
WS          [ \\r\\n\\t]*

%s MULTILINE_COMMENT
%s DOCUMENTATION_COMMENT
%s NESTED_COMMENT

%%

<MULTILINE_COMMENT>{
  "*/"                            {printf("<MULTILINE_COMMENT>"); BEGIN(INITIAL); return 468; }
  .                               {}
  \\n                              {printf("\\n"); line++; printf("%3d - ", line);}
}
<DOCUMENTATION_COMMENT>{
  "*/"                            {printf("<DOCUMENTATION_COMMENT>"); BEGIN(INITIAL); return 468; }
  .                               {}
  \\n                              {printf("\\n"); line++; printf("%3d - ", line);}
}
<NESTED_COMMENT>{
  "/+"                            {nested_depth++;}
  "+/"                            {
                                    if (nested_depth==0) {
                                      printf("<NESTED_COMMENT>");
                                      BEGIN(INITIAL);
                                      return 468;
                                    } else {
                                      nested_depth--;
                                    };
                                  }
  .                               {}
  \\n                              {printf("\\n"); line++; printf("%3d - ", line);}
}
<INITIAL>{
  "/**/"                          {printf("<MULTILINE_COMMENT>"); BEGIN(INITIAL); return 468; }
  "/*"                            {BEGIN(MULTILINE_COMMENT);}
  "/+"                            {BEGIN(NESTED_COMMENT);}
  "/++/"                          {printf("<NESTED_COMMENT>"); return 468; }
  [/]"**"[^*|/]*"*"+([^*/][^*]*"*"+)*[/] {
                                     printf("<DOCUMENTATION_COMMENT>");
                                     int j = 0, i=0;
                                     for (i=0; yytext[i]!='\\0'; i++){
                                         if (yytext[i]=='\\n') j++;
                                     }
                                     for (i=0; i<j; i++){
                                        printf("\\n"); line++; printf("%3d - ", line);
                                     }
                                     return 468;
                                   }
""")

    with open("reserved.txt") as f:
        content = f.readlines()

        symbols = [
            # Puntuation
            ".", ",",
            # Brackets
            "[", "]", "{", "}", "(", ")",
            # Operators
            "+", "-", "*", "=", "!", "~", "&", "|", "<", ">", "%", "^"]
        endings = [
            # Endings
            " ", ";", "\\r", " ", "\\t",
            # Comments
            "/"]

        i = 300
        for line in content:
            dest.write('  "' + str(line.rstrip()) + '"' + (' ' * (30 - len(line.rstrip()))) + '{printf("' + str(
                line.rstrip()) + '"); return ' + str(i) + ';}\n')
            i += 1
        for sym in symbols:
            dest.write('  "' + str(sym) + '"' + (' ' * (30 - len(sym))) + '{printf("' + str(sym) + '"); return ' + str(
                i) + ';}\n')
            i += 1
        for sym in endings:
            dest.write('  [' + str(sym) + ']' + (' ' * (30 - len(sym))) + '{printf("' + str(sym) + '"); return ' + str(
                i) + ';}\n')
            i += 1

        mine = [
            # Strings
            {
                'regex': 'L?\\\"(\\\\.|[^\\\\"])*\\\"',
                'function': """{
                                    printf("STRING_CONSTANT");
                                    int j = 0, i=0;
                                    for (i=0; yytext[i]!='\\0'; i++){
                                         if (yytext[i]=='\\n') j++;
                                    }
                                    for (i=0; i<j; i++){
                                        printf("\\n"); line++; printf("%3d - ", line);
                                     }
                                    return 1;
                                  }"""
            },
            # Identificadores
            {
                'regex': '{L}({L}|{D})*',
                'function': """{
                                    struct item *aux = ht_get(hashtable, yytext);
                                    if (aux == NULL) {
                                        aux = malloc(sizeof(struct item));
                                        aux->code = identifiers;
                                        identifiers++;
                                        aux->instance = yytext;
                                        ht_set(hashtable, yytext, aux);
                                        aux = ht_get(hashtable, yytext);;
                                    }
                                    printf("%s(%d)", yytext, aux->code);
                                    return aux->code;
                                  }"""
                # 'function': '{printf("IDENTIFIER"); return 1; }'
            },
            # Comentario monolínea
            {
                'regex': '{CM}[^\\n]*',
                'function': '{printf("COMMENT"); return 1; }'
            },
            # Constantes enteras
            {
                'regex': '0[xX]{H}+',
                'function': '{printf("HEX_CONSTANT"); return 1; }'
            },
            {
                'regex': '0[bB]{B}+',
                'function': '{printf("BIN_CONSTANT"); return 1; }'
            },
            {
                'regex': '0{D}+{IS}?',
                'function': '{printf("INT_CONSTANT"); return 1; }'
            },
            {
                'regex': '{D}+{IS}?',
                'function': '{printf("INT_CONSTANT"); return 1; }'
            },
            # Constantes reales
            {
                'regex': '{D}+{E}{FS}?',
                'function': '{printf("REAL_CONSTANT"); return 1; }'
            },
            {
                'regex': '{D}*"."{D}+({E})?{FS}?',
                'function': '{printf("REAL_CONSTANT"); return 1; }'
            },
            {
                'regex': '{D}+"."{D}*({E})?{FS}?',
                'function': '{printf("REAL_CONSTANT"); return 1; }'
            },
            # Newlines
            {
                'regex': '\\n',
                'function': '{printf("\\n"); line++; printf("%3d - ", line); return 499;}'
            },
            # Errors
            {
                'regex': '0[xX]{T}+',
                'function': '{printf("ERROR_HEXADETIMAL(%s)",yytext); return 999; }'
            },
            {
                'regex': '0[bB]{T}+',
                'function': '{printf("ERROR_BINARY(%s)",yytext); return 999; }'
            },
            # {
            #     'regex': '{D}+{EE}{FS}?',
            #     'function': '{printf("ERROR_EXPONENTIAL(%s)",yytext); return 999; }'
            # },
            # {
            #     'regex': '{D}*"."{D}+({EE})?{FS}?',
            #     'function': '{printf("ERROR_EXPONENTIAL(%s)",yytext); return 999; }'
            # },
            # {
            #     'regex': '{D}+"."{D}*({EE})?{FS}?',
            #     'function': '{printf("ERROR_EXPONENTIAL(%s)",yytext); return 999; }'
            # },
            {
                'regex': '{D}+[^\\n\\r\\v\\f\\t ,;=/\\]\\)\\}]*',
                'function': '{printf("ERROR_NUMBER(%s)",yytext); return 999; }'
            },
            {
                'regex': '<*>.|\\n',
                'function': '{printf("ERROR_UNKNOWN(%s)",yytext); return  999; }'
            },
        ]
        for m in mine:
            dest.write('  '+m['regex'] + (' ' * (32 - len(m['regex']))) + m['function'] + '\n')
    dest.write('}\n%%')
    dest.write(
        """
int yywrap (void ){
    return 1;
}

int main(int argc, char **argv) {
    printf(COLOR_MAGENTA"D Lexical_Analyzer v0.1\\n"COLOR_RESET);

    if ( argc > 1 ) {
            yyin = fopen( argv[1], "r" );
            //printf(COLOR_MAGENTA"Argumento\\n"COLOR_RESET);
    } else {
            yyin = stdin;
            //printf(COLOR_MAGENTA"Stdin\\n"COLOR_RESET);
    }

    hashtable = ht_create(65536);

    printf("\\n"); printf("%3d - ", line);
    while (yylex() != 0){}

    printf("\\n");
    ht_print_identifiers(hashtable);

    ht_free(hashtable);

    return EXIT_SUCCESS;
}
"""
    )
    dest.close()

    if platform.system()=='Windows':
        os.system("flex dlang.lex && gcc lex.yy.c ../external/model/hash.c ../external/model/list.c -lfl -o dlangLexer && dlangLexer ../../regression.d")
    else:
        os.system("flex dlang.lex && gcc lex.yy.c ../external/model/hash.c ../external/model/list.c -lfl -o dlangLexer && ./dlangLexer ../../regression.d")