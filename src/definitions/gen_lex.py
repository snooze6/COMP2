import os

defname = 'dlang.lex'

if __name__ == "__main__":
    if os.path.exists(defname):
        os.remove(defname)

    dest = open(defname, 'w')

    dest.write(
        """%{
    #include <stdio.h>
    #include "definitions.h"
    #include "../external/model/hash.h"
    #include "../config.h"

    int nested_depth = 0;
    int identifiers = 500;
%}

%option caseless

D			[0-9_]
L			[a-zA-Z_]
B           [01]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
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
  \\n                              {}
}
<DOCUMENTATION_COMMENT>{
  "*/"                            {printf("<DOCUMENTATION_COMMENT>"); BEGIN(INITIAL); return 468; }
  .                               {}
  \\n                              {}
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
  \\n                              {}
}
<INITIAL>{
  "/**/"                          {printf("<MULTILINE_COMMENT>"); BEGIN(INITIAL); return 468; }
  "/*"                            {BEGIN(MULTILINE_COMMENT);}
  "/+"                            {BEGIN(NESTED_COMMENT);}
  "/++/"                          {printf("<NESTED_COMMENT>"); return 468; }
  [/]"**"[^*|/]*"*"+([^*/][^*]*"*"+)*[/] {printf("<DOCUMENTATION_COMMENT>"); return 468;}
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
            " ", ";", "\\n", "\\r", " ", "\\t",
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
            {
                'regex': 'L?\\\"(\\\\.|[^\\\\"])*\\\"',
                'function': '{printf("STRING_CONSTANT"); return 1; }'
            },
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
                                  }
"""
                # 'function': '{printf("IDENTIFIER"); return 1; }'
            },
            {
                'regex': '{CM}[^\\n]*',
                'function': '{printf("COMMENT"); return 1; }'
            },
            # Constantes enteras
            {
                'regex': '0[xX]{H}+{IS}?',
                'function': '{printf("HEX_CONSTANT"); return 1; }'
            },
            {
                'regex': '0[bB]{B}+{IS}?',
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
            {
                'regex': 'L?\'(\\\\.|[^\\\\\'])+\'',
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
            # Comentarios multilínea
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
            printf(COLOR_MAGENTA"Argumento\\n"COLOR_RESET);
    } else {
            yyin = stdin;
            printf(COLOR_MAGENTA"Stdin\\n"COLOR_RESET);
    }

    hashtable = ht_create(65536);

    while (yylex() != 0){}

    printf("\\n");
    ht_print_identifiers(hashtable);

    ht_free(hashtable);

    return EXIT_SUCCESS;
}
"""
    )
    dest.close()

    os.system("flex dlang.lex && gcc lex.yy.c ../external/model/hash.c ../external/model/list.c -lfl -o dlangLexer && cat ../../regression.d | dlangLexer")
