%{
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "storage.h"
#include "hashTable.h"

struct configuration {
	char *host;
	int port;
	char *username;
	char *password;

	struct table *tlist;
	char *data_dir;
};

struct config_params params;
struct config_params census_params;
HashTable *ourHashTable[MAX_TABLES];
%}

%union {
	char *sval;	//String value (user defined)
	int pval;	// Port number value (user defined)
}

%token <sval> STRING SIZE CHAR INT passString
%token <pval> NUMBER
%token HOST_PROPERTY PORT_PROPERTY DDIR_PROPERTY TABLE USER_NAME PASSWORD NEWLINE TABLE_INVALID CONCURRENCY

%%


process_line: line
			| process_line line
			;

line    : serverhost NEWLINE
		| table NEWLINE 		
		| serverport NEWLINE	
		| username NEWLINE		
		| password NEWLINE
		| concurrency NEWLINE	 				
		| NEWLINE 
		;

serverhost: HOST_PROPERTY STRING 	{
									strcpy(params.server_host, $2); 
									free($2);
									}
		   ;

serverport: PORT_PROPERTY NUMBER 	{params.server_port = $2;}
			;

username: USER_NAME STRING 			{
									strcpy(params.username,$2); 
									free($2);
									}
		;

password: PASSWORD passString 		{
									strcpy(params.password, $2); 
									free($2);
									}
		| PASSWORD STRING  			{
									strcpy(params.password, $2); 
									free($2);
									}
		;

concurrency: CONCURRENCY NUMBER     {
									params.concurrencyMode = $2;
									}


table : TABLE STRING exp  {	if (params.table_number >= MAX_TABLES) return -1;
							int table_index = isTableNameExist ($2, &params);
							if (table_index != -1) {
							return -1;
							free($2);
							}
							printf("table number is %d\n", params.table_number);
							 updateTableName ($2);  
							free($2);}
		;


exp   : term	
	  | exp ',' term  
	  ;	

term	: STRING ':' CHAR SIZE 		{updateTableChar ($1,$4);
									//free($4);
									free($1);
									//free($3);
									}
		| STRING ':' INT			{ 
									updateTableInt ($1);
									//free($3);
									free($1);}
		;  

%%

int parse (char * config_file, struct config_params* params ) {

	FILE *f;
	extern FILE *yyin;

		f= fopen(config_file, "r");
		if (!f) {
			printf("file is not opening \n");
			return -1;
		}
		yyin = f;

		while (!feof(yyin)) {
			if (yyparse() != 0)
			{
				return -1;

			}
			//fclose(f);
		}

	return 0;
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 



void updateTableName(char *table_name)
{

	strcpy(params.table_names[params.table_number].tablename, table_name);
	ourHashTable[params.table_number] = ht_create(2000);
	params.table_number ++;

}

void updateTableChar(char *column_name, char *size) {

	char temp_pointer[MAX_STRING_SIZE];
	snprintf(temp_pointer, sizeof temp_pointer, "%s#char#%s#",column_name, size);

	char *temp = params.table_names[params.table_number].column_info;
	temp = strcat(temp, temp_pointer);

}

void updateTableInt(char *column_name) {
	char temp_pointer[MAX_STRING_SIZE];
	snprintf(temp_pointer, sizeof temp_pointer, "%s#int#",column_name);

	char *temp = params.table_names[params.table_number].column_info;
	temp = strcat(temp, temp_pointer);
	
}

void freeMemory(char *string) {
	free(string);
}
