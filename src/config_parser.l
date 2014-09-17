%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "utils.h"
	#include "config_parser.tab.h"
	//extern int yylval;

%}
a2Z  [a-zA-Z0-9]
passString  [a-z.A-Z0-9]
host server_host
port server_port 
dir   data_directory

%%
([a-zA-Z0-9]*[ ]+[:]) { return TABLE_INVALID;}
([:][ ]+char) { return TABLE_INVALID;}
([:][ ]+int) { return TABLE_INVALID;}
([ ]+\[[0-9]+\]) {return TABLE_INVALID;}
#.*\n	    { 	  }

char		{ return CHAR; }
int			{ return INT; }
concurrency { return CONCURRENCY;}
{host}	    { return HOST_PROPERTY; }
{port}	    { return PORT_PROPERTY; }
table	    { return TABLE; }
username	{ return USER_NAME;}
password	{ return PASSWORD;}
{dir}	    { return DDIR_PROPERTY; }

[\t ]+	    {              }
[\n]		{return NEWLINE;}

[0-9]+	    { yylval.pval = (int) atoi(yytext);
                   return NUMBER; }
{a2Z}*	    { yylval.sval = strdup(yytext);
	  	     return STRING; }
{passString}*  {yylval.sval = strdup(yytext); return passString;}	  	     
','			{ return ',';}		
':'			{ return ':';}
\[[0-9]+\]	{    char * text = strdup(yytext+1);
				 char * pch = strchr(text,']');
				 int length = pch-text;
				 strncpy(pch, text, length);
				 pch[length] = NULL;
				 yylval.sval = pch; return SIZE;}


.           	    { return yytext[0]; }
<<EOF>> { static int once;
          return once++ ? 0 : NEWLINE; }

%%

int yywrap (void) {return 1;}


