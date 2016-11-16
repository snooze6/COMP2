import os

defname = 'dlang.lex'

if __name__ == "__main__":
    if os.path.exists(defname):
        os.remove(defname)

    dest = open(defname, 'w')

    dest.write(
"""
%{
#include <stdio.h>
#include "definitions.h"
%}

%option caseless

%%
""")

    with open("reserved.txt") as f:
        content = f.readlines()

        symbols = [
            # Puntuation
            ".",",",
            # Brackets
            "[","]","{","}","(",")",
            # Operators
            "+","-","*","=","!","~","&","|","<",">","%","^"]
        endings = [
            # Endings
            " ",";", "\\n","\\r"," ","\\t",
            # Comments
            "/"]

        i = 300
        for line in content:
            # dest.write('"'+str(line.rstrip())+'"'+(' '*(30-len(line.rstrip())))+'{printf("'+str(line.rstrip())+'"); return '+ str(i) + ';}\n')
            dest.write('"'+str(line.rstrip())+'"'+(' '*(30-len(line.rstrip())))+'{printf("'+str(line.rstrip())+'"); return '+ str(i) + ';}\n')
            i+=1
        for sym in symbols:
            # dest.write('"'+str(sym)+'"'+(' '*(32-len(sym)))+'{printf("'+str(sym)+' - '+str(i)+'"); return '+ str(i) + ';}\n')
            dest.write('"'+str(sym)+'"'+(' '*(32-len(sym)))+'{printf("'+str(sym)+'"); return '+ str(i) + ';}\n')
            i+=1
        for sym in endings:
            # dest.write('['+str(sym)+']'+(' '*(32-len(sym)))+'{printf("'+str(sym)+' - '+str(i)+'"); return '+ str(i) + ';}\n')
            dest.write('['+str(sym)+']'+(' '*(32-len(sym)))+'{printf("'+str(sym)+'"); return '+ str(i) + ';}\n')
            i+=1

        mine = [
            {
                'regex': '',
                'function': ''
            }
        ]


    dest.write('%%')

    os.system("flex dlang.lex && gcc lex.yy.c -lfl -o dlangLexer && cat ../../regression.d | dlangLexer")