%option noyywrap

%{
#include "global.h"
%}

delim           [\t ]
ws              {delim}+
digit           [0-9]
num             {digit}+
alpha           [_a-zA-Z]
identifier      {alpha}({alpha}|{digit})*
string		["][ a-zA-Z0-9]*["]
comparator 	[=][=]|[!][=]|[<]|[>]|[<][=]|[>][=]

%%

"="		{return '=';}
"*"             {return '*';}
"+"             {return '+';}
"-"             {return '-';}
"/"             {return '/';}
"("             {return '(';}
")"             {return ')';}
";"             {return ';';}
"\n"            {lineno++;}
<<EOF>>         {return DONE;}

"END"           {return END;}
"BEGIN"         {return BEGN;}
"READ"          {return READ;}
"PRINT"         {return PRINT;}
"IF"            {return IF;}
"ELSE"          {return ELSE;}
"THEN"          {return THEN;}
"GOTO"          {return GOTO;}
"LABEL"         {return LABEL;}
"NULL"          {return NUL;}

{string}        {return STRING;}
{comparator}    {return COMPARATOR;}


{ws}            {/* skip blanks and tabs */}

{num} {
  tokenval = atoi(yytext);
  return NUM;
}

{identifier} {
  if (strlen(yytext) >= BSIZE) {
    error("compiler error");
  }

 
  tokensym = lookup(yytext, ID);
  tokensym->count += 1;
//  printf("%d\n", tokensym->count);

  return ID;

//  return (int)tokensym->token;
  
}

%%
