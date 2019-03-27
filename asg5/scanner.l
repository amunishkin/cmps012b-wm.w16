%{
// $Id: scanner.l,v 1.2 2013-03-14 16:52:45-07 - - $

#include <stdlib.h>

#include "yyextern.h"

%}

%option 8bit
%option debug
%option ecs
%option interactive
%option nodefault
%option noyywrap
%option yylineno

NUMBER  ([[:digit:]]+([-:.][[:digit:]]+)*)
WORD    ([[:alnum:]]+([-&'.][[:alnum:]]+)*)
OTHER   (.|\n)

%%

{NUMBER}        { }
{WORD}          { return 1;  }
{OTHER}         { }

%%

void yycleanup (void) {
   yylex_destroy();
}

