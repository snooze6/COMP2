%{
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
"ABSTRACT"                      {printf("ABSTRACT"); return 300;}
"ALIAS"                         {printf("ALIAS"); return 301;}
"ALIGN"                         {printf("ALIGN"); return 302;}
"ASM"                           {printf("ASM"); return 303;}
"ASSERT"                        {printf("ASSERT"); return 304;}
"AUTO"                          {printf("AUTO"); return 305;}
"BODY"                          {printf("BODY"); return 306;}
"BOOL"                          {printf("BOOL"); return 307;}
"BREAK"                         {printf("BREAK"); return 308;}
"BYTE"                          {printf("BYTE"); return 309;}
"CASE"                          {printf("CASE"); return 310;}
"CAST"                          {printf("CAST"); return 311;}
"CATCH"                         {printf("CATCH"); return 312;}
"CDOUBLE"                       {printf("CDOUBLE"); return 313;}
"CENT"                          {printf("CENT"); return 314;}
"CFLOAT"                        {printf("CFLOAT"); return 315;}
"CHAR"                          {printf("CHAR"); return 316;}
"CLASS"                         {printf("CLASS"); return 317;}
"CONST"                         {printf("CONST"); return 318;}
"CONTINUE"                      {printf("CONTINUE"); return 319;}
"CREAL"                         {printf("CREAL"); return 320;}
"DCHAR"                         {printf("DCHAR"); return 321;}
"DEBUG"                         {printf("DEBUG"); return 322;}
"DEFAULT"                       {printf("DEFAULT"); return 323;}
"DELEGATE"                      {printf("DELEGATE"); return 324;}
"DELETE"                        {printf("DELETE"); return 325;}
"DEPRECATED"                    {printf("DEPRECATED"); return 326;}
"DO"                            {printf("DO"); return 327;}
"DOUBLE"                        {printf("DOUBLE"); return 328;}
"ELSE"                          {printf("ELSE"); return 329;}
"ENUM"                          {printf("ENUM"); return 330;}
"EXPORT"                        {printf("EXPORT"); return 331;}
"EXTERN"                        {printf("EXTERN"); return 332;}
"FALSE"                         {printf("FALSE"); return 333;}
"FINAL"                         {printf("FINAL"); return 334;}
"FINALLY"                       {printf("FINALLY"); return 335;}
"FLOAT"                         {printf("FLOAT"); return 336;}
"FOR"                           {printf("FOR"); return 337;}
"FOREACH"                       {printf("FOREACH"); return 338;}
"FOREACH_REVERSE"               {printf("FOREACH_REVERSE"); return 339;}
"FUNCTION"                      {printf("FUNCTION"); return 340;}
"GOTO"                          {printf("GOTO"); return 341;}
"IDOUBLE"                       {printf("IDOUBLE"); return 342;}
"IF"                            {printf("IF"); return 343;}
"IFLOAT"                        {printf("IFLOAT"); return 344;}
"IMMUTABLE"                     {printf("IMMUTABLE"); return 345;}
"IMPORT"                        {printf("IMPORT"); return 346;}
"IN"                            {printf("IN"); return 347;}
"INOUT"                         {printf("INOUT"); return 348;}
"INT"                           {printf("INT"); return 349;}
"INTERFACE"                     {printf("INTERFACE"); return 350;}
"INVARIANT"                     {printf("INVARIANT"); return 351;}
"IREAL"                         {printf("IREAL"); return 352;}
"IS"                            {printf("IS"); return 353;}
"LAZY"                          {printf("LAZY"); return 354;}
"LONG"                          {printf("LONG"); return 355;}
"MACRO"                         {printf("MACRO"); return 356;}
"MIXIN"                         {printf("MIXIN"); return 357;}
"MODULE"                        {printf("MODULE"); return 358;}
"NEW"                           {printf("NEW"); return 359;}
"NOTHROW"                       {printf("NOTHROW"); return 360;}
"NULL"                          {printf("NULL"); return 361;}
"OUT"                           {printf("OUT"); return 362;}
"OVERRIDE"                      {printf("OVERRIDE"); return 363;}
"PACKAGE"                       {printf("PACKAGE"); return 364;}
"PRAGMA"                        {printf("PRAGMA"); return 365;}
"PRIVATE"                       {printf("PRIVATE"); return 366;}
"PROTECTED"                     {printf("PROTECTED"); return 367;}
"PUBLIC"                        {printf("PUBLIC"); return 368;}
"PURE"                          {printf("PURE"); return 369;}
"REAL"                          {printf("REAL"); return 370;}
"REF"                           {printf("REF"); return 371;}
"RETURN"                        {printf("RETURN"); return 372;}
"SCOPE"                         {printf("SCOPE"); return 373;}
"SHARED"                        {printf("SHARED"); return 374;}
"SHORT"                         {printf("SHORT"); return 375;}
"STATIC"                        {printf("STATIC"); return 376;}
"STRUCT"                        {printf("STRUCT"); return 377;}
"SUPER"                         {printf("SUPER"); return 378;}
"SWITCH"                        {printf("SWITCH"); return 379;}
"SYNCHRONIZED"                  {printf("SYNCHRONIZED"); return 380;}
"TEMPLATE"                      {printf("TEMPLATE"); return 381;}
"THIS"                          {printf("THIS"); return 382;}
"THROW"                         {printf("THROW"); return 383;}
"TRUE"                          {printf("TRUE"); return 384;}
"TRY"                           {printf("TRY"); return 385;}
"TYPEDEF"                       {printf("TYPEDEF"); return 386;}
"TYPEID"                        {printf("TYPEID"); return 387;}
"TYPEOF"                        {printf("TYPEOF"); return 388;}
"UBYTE"                         {printf("UBYTE"); return 389;}
"UCENT"                         {printf("UCENT"); return 390;}
"UINT"                          {printf("UINT"); return 391;}
"ULONG"                         {printf("ULONG"); return 392;}
"UNION"                         {printf("UNION"); return 393;}
"UNITTEST"                      {printf("UNITTEST"); return 394;}
"USHORT"                        {printf("USHORT"); return 395;}
"VERSION"                       {printf("VERSION"); return 396;}
"VOID"                          {printf("VOID"); return 397;}
"VOLATILE"                      {printf("VOLATILE"); return 398;}
"WCHAR"                         {printf("WCHAR"); return 399;}
"WHILE"                         {printf("WHILE"); return 400;}
"WITH"                          {printf("WITH"); return 401;}
"__FILE__"                      {printf("__FILE__"); return 402;}
"__FILE_FULL_PATH__"            {printf("__FILE_FULL_PATH__"); return 403;}
"__MODULE__"                    {printf("__MODULE__"); return 404;}
"__LINE__"                      {printf("__LINE__"); return 405;}
"__FUNCTION__"                  {printf("__FUNCTION__"); return 406;}
"__PRETTY_FUNCTION__"           {printf("__PRETTY_FUNCTION__"); return 407;}
"__GSHARED"                     {printf("__GSHARED"); return 408;}
"__TRAITS"                      {printf("__TRAITS"); return 409;}
"__VECTOR"                      {printf("__VECTOR"); return 410;}
"__PARAMETERS"                  {printf("__PARAMETERS"); return 411;}
"/="                            {printf("/="); return 412;}
".."                            {printf(".."); return 413;}
"&="                            {printf("&="); return 414;}
"&&"                            {printf("&&"); return 415;}
"|="                            {printf("|="); return 416;}
"||"                            {printf("||"); return 417;}
"-="                            {printf("-="); return 418;}
"--"                            {printf("--"); return 419;}
"+="                            {printf("+="); return 420;}
"++"                            {printf("++"); return 421;}
"<="                            {printf("<="); return 422;}
"<<"                            {printf("<<"); return 423;}
"<>"                            {printf("<>"); return 424;}
">="                            {printf(">="); return 425;}
">>"                            {printf(">>"); return 426;}
"!="                            {printf("!="); return 427;}
"!<"                            {printf("!<"); return 428;}
"!>"                            {printf("!>"); return 429;}
"=="                            {printf("=="); return 430;}
"*="                            {printf("*="); return 431;}
"%="                            {printf("%="); return 432;}
"^="                            {printf("^="); return 433;}
"^^"                            {printf("^^"); return 434;}
"~="                            {printf("~="); return 435;}
"=>"                            {printf("=>"); return 436;}
"<<="                           {printf("<<="); return 437;}
"..."                           {printf("..."); return 438;}
"<>="                           {printf("<>="); return 439;}
">>="                           {printf(">>="); return 440;}
">>>"                           {printf(">>>"); return 441;}
"!<>"                           {printf("!<>"); return 442;}
"!<="                           {printf("!<="); return 443;}
"!>="                           {printf("!>="); return 444;}
"^^="                           {printf("^^="); return 445;}
">>>="                          {printf(">>>="); return 446;}
"!<>="                          {printf("!<>="); return 447;}
"."                             {printf("."); return 448;}
","                             {printf(","); return 449;}
"["                             {printf("["); return 450;}
"]"                             {printf("]"); return 451;}
"{"                             {printf("{"); return 452;}
"}"                             {printf("}"); return 453;}
"("                             {printf("("); return 454;}
")"                             {printf(")"); return 455;}
"+"                             {printf("+"); return 456;}
"-"                             {printf("-"); return 457;}
"*"                             {printf("*"); return 458;}
"="                             {printf("="); return 459;}
"!"                             {printf("!"); return 460;}
"~"                             {printf("~"); return 461;}
"&"                             {printf("&"); return 462;}
"|"                             {printf("|"); return 463;}
"<"                             {printf("<"); return 464;}
">"                             {printf(">"); return 465;}
"%"                             {printf("%"); return 466;}
"^"                             {printf("^"); return 467;}
[ ]                             {printf(" "); return 468;}
[;]                             {printf(";"); return 469;}
[\n]                            {printf("\n"); return 470;}
[\r]                            {printf("\r"); return 471;}
[ ]                             {printf(" "); return 472;}
[\t]                            {printf("\t"); return 473;}
[/]                             {printf("/"); return 474;}
L?\"(\\.|[^\\"])*\"             {printf("STRING"); return 1; }
{L}({L}|{D})*                   {printf("IDENTIFIER"); return 1; }
{CM}[^\n]*                      {printf("COMMENT"); return 1; }
0[xX]{H}+{IS}?                  {printf("INT_CONSTANT"); return 1; }
0{D}+{IS}?                      {printf("INT_CONSTANT"); return 1; }
{D}+{IS}?                       {printf("INT_CONSTANT"); return 1; }
L?'(\\.|[^\\'])+'               {printf("INT_CONSTANT"); return 1; }
{D}+{E}{FS}?                    {printf("REAL_CONSTANT"); return 1; }
{D}*"."{D}+({E})?{FS}?          {printf("REAL_CONSTANT"); return 1; }
{D}+"."{D}*({E})?{FS}?          {printf("REAL_CONSTANT"); return 1; }
%%