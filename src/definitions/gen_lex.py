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
%}

%option caseless

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
LP                      "{"
RP                      "}"
SM                      ";"
CM                      "//"

%%
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
            # dest.write('"'+str(line.rstrip())+'"'+(' '*(30-len(line.rstrip())))+'{printf("'+str(line.rstrip())+'"); return '+ str(i) + ';}\n')
            dest.write('"' + str(line.rstrip()) + '"' + (' ' * (30 - len(line.rstrip()))) + '{printf("' + str(
                line.rstrip()) + '"); return ' + str(i) + ';}\n')
            i += 1
        for sym in symbols:
            # dest.write('"'+str(sym)+'"'+(' '*(32-len(sym)))+'{printf("'+str(sym)+' - '+str(i)+'"); return '+ str(i) + ';}\n')
            dest.write('"' + str(sym) + '"' + (' ' * (30 - len(sym))) + '{printf("' + str(sym) + '"); return ' + str(
                i) + ';}\n')
            i += 1
        for sym in endings:
            # dest.write('['+str(sym)+']'+(' '*(32-len(sym)))+'{printf("'+str(sym)+' - '+str(i)+'"); return '+ str(i) + ';}\n')
            dest.write('[' + str(sym) + ']' + (' ' * (30 - len(sym))) + '{printf("' + str(sym) + '"); return ' + str(
                i) + ';}\n')
            i += 1

        mine = [
            {
                'regex': 'L?\\\"(\\\\.|[^\\\\"])*\\\"',
                'function': '{printf("STRING"); return 1; }'
            },
            {
                'regex': '{L}({L}|{D})*',
                'function': '{printf("IDENTIFIER"); return 1; }'
            },
            {
                'regex': '{CM}[^\\n]*',
                'function': '{printf("COMMENT"); return 1; }'
            },
            # Constantes enteras
            {
                'regex': '0[xX]{H}+{IS}?',
                'function': '{printf("INT_CONSTANT"); return 1; }'
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
            dest.write(m['regex'] + (' ' * (32 - len(m['regex']))) + m['function'] + '\n')

    dest.write('%%')
#     dest.write(
#         """
#
# int yyerror(const char *msg) {
#     std::cerr << "FlexError:" << msg; return 0;
# }
# """
#     )
    dest.close()

    os.system("flex dlang.lex && gcc lex.yy.c -lfl -o dlangLexer && cat ../../regression.d | dlangLexer")
