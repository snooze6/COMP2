%{
   #include <stdarg.h>
   #include "simple_shared.h"
   #define YYSTYPE char *
   int yydebug=1;
   int indent=0;
   char *iden_dum;
%}
%token FLOAT
%token INT
%token IDENTIFIER

%% /* Grammar rules and actions follow */
declaration:
      type_specifier identifier_dum ';'
        { printf("%3d: FROM BISON declaration\n", line_number); }
;
type_specifier:
      FLOAT
         { printf("%3d: FROM BISON FLOAT\n", line_number); }
   |  INT
         { printf("%3d: FROM BISON INT\n", line_number); }
;
identifier_dum:
      IDENTIFIER
         { iden_dum = $1; printf("%3d: IDENTIFIER: %s\n", line_number, &iden_dum); }
;
%%

main ()
{
  yyparse ();
}