/**
 * @file
 * @brief This file implements various utility functions that are
 * can be used by the storage server and client library. 
 */
#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include "utils.h"


/**
 * @brief Checks a line for any white space
 *
 * @param input A string in the config file
 * @return 0 on success, -1 if otherwise
 */
int checkWhiteSpace (char*input){

	int i = 0; 
	
	for (i = 0; i < strlen(input); i++){
		if (input[i]== '\n')
			return 0;
		if ((int)input[i]!= 32 && (int)input[i] != 9)
			return -1;
	}
	return 0;
}

bool isWhiteCharacter (char*input) {
	int i=0;

	for (i=0; i< strlen(input); i++) {
		if (input[i] == ' ')
			return true;
	}
	return false;
}


/**
 * @brief Sends message to either client to server or server to client. 
 *
 * @param sock A socket created by either server or client
 * @param buf A message sent to either client or server
 * @param len A size of the buf
 * @return 0 on success, -1 if otherwise
 */
int sendall(const int sock, const char *buf, const size_t len)
{
	size_t tosend = len;
	while (tosend > 0) {
		ssize_t bytes = send(sock, buf, tosend, 0);
		if (bytes <= 0) 
			break; // send() was not successful, so stop.
		tosend -= (size_t) bytes;
		buf += bytes;
	};

	return tosend == 0 ? 0 : -1;
}

/**
 * In order to avoid reading more than a line from the stream,
 * this function only reads one byte at a time.  This is very
 * inefficient, and you are free to optimize it or implement your
 * own function.
 */
/**
 * @brief Receives a message from either a client or a server. 
 *
 * @param sock A socket created by either server or client
 * @param buf A message sent to either client or server
 * @param buflen A size of the buf
 * @return 0 on success, -1 if otherwise
 */
int recvline(const int sock, char *buf, const size_t buflen)
{
	int status = 0; // Return status.
	size_t bufleft = buflen;

	while (bufleft > 1) {
		// Read one byte from scoket.
		ssize_t bytes = recv(sock, buf, 1, 0);
		if (bytes <= 0) {
			// recv() was not successful, so stop.
			status = -1;
			break;
		} else if (*buf == '\n') {
			// Found end of line, so stop.
			*buf = 0; // Replace end of line with a null terminator.
			status = 0;
			break;
		} else {
			// Keep going.
			bufleft -= 1;
			buf += 1;
		}
	}
	*buf = 0; // add null terminator in case it's not already there.

	return status;
}


/**
 * @brief Parse and process a line in the config file.
 *
 * @param line A single line from the config file.
 * @param params A variable that should be modified according to the information within the "line" string
 * @return 0 on success, 1 if otherwise
 */
 /*
int process_config_line(char *line, struct config_params *params)
{
	// Ignore comments.
	if (line[0] == CONFIG_COMMENT_CHAR || checkWhiteSpace(line) == 0)
		return 0;

	// Extract config parameter name and value.
	//char name[MAX_CONFIG_LINE_LEN];
	int port = 0;
	char *name = getNextWord(&line, ' ');
	
	if (name == NULL) {
		return 1;
	}

	if (strcmp(name, "server_host") == 0 && strcmp(params->server_host, "NOTINIT") == 0 ) {
			char *value = getNextWord(&line, '\n');
			if (value == NULL) {
				return 1;
			}
		strncpy(params->server_host, value, sizeof params->server_host);
		free(value);
	} else if (strcmp(name, "server_port") == 0 && params->server_port == 0 ) {
		int items = sscanf(line, "%d\n", &port);
		if (items != 1)
			return 1;
		else
			params->server_port = port;
	} else if (strcmp(name, "username") == 0 && strcmp(params->username, "NOTINIT") == 0 ) {
		char *value = getNextWord(&line, '\n');
		if (value == NULL) {
				return 1;
			}
		strncpy(params->username, value, sizeof params->username);
		free(value);
	} else if (strcmp(name, "password") == 0 && strcmp(params->password, "NOTINIT") == 0 ) {
		char *value = getNextWord(&line, '\n');
		if (value == NULL) {
				return 1;
			}
		strncpy(params->password, value, sizeof params->password);
		free(value);
	} else if (strcmp(name, "table") == 0 ) {

		char value[MAX_CONFIG_LINE_LEN];
		char testValue[MAX_CONFIG_LINE_LEN];
		int items2 = sscanf(line," %s", value);
		int items = sscanf(line, "%s %s", value, testValue);

		if (items == 2)
			return 1;

		//duplicate value exists
		if (strcmp(params->tablename, value) == 0)
			return 1;
		
		//never initialized
		if (strcmp(params->tablename, "NOTINIT") == 0)
			strncpy(params->tablename, value, sizeof params->tablename);



		return 0;
	}
	else {
		return 1;
	}

	free(name);
	return 0;
}*/

/**
 * @brief Checks a line for any white space
 *
 * @param input A string in the config file
 * @return 0 on success, -1 if otherwise
 */

 /*
int read_config(const char *config_file, struct config_params *params)
{
	int error_occurred = 0;

	// Open file for reading.
	FILE *file = fopen(config_file, "r");
	if (file == NULL)
		error_occurred = 1;

	// Process the config file.
	while (!error_occurred && !feof(file)) {
		// Read a line from the file.
		char line[MAX_CONFIG_LINE_LEN];
		char *l = fgets(line, sizeof line, file);

		// Process the line.
		if (l == line)
			error_occurred = process_config_line(line, params);
		else if (!feof(file))
			error_occurred = 1;
	}

	return error_occurred ? -1 : 0;
}
*/
/**
 * @brief Creates a file to log the server and client commands
 *
 * @param file A file containg the logs
 * @param message A message loggeERR_KEY_NOT_FOUNDd to the file
 * @return void
 */
void logger(FILE *file,char* message)
{
	if  (file != NULL){
			fprintf(file,message);
			fflush(file);
	}

}

/**ERR_KEY_NOT_FOUND
 * @brief Generates an encryted password
 *
 * @param passwd A string that needs to be encryted.
 * @param salt A variable used for future milestone.
 * @return encryted password string pointer.
 */
char *generate_encrypted_password(const char *passwd, const char *salt)
{
	if(salt != NULL)
		return crypt(passwd, salt);
	else
		return crypt(passwd, DEFAULT_CRYPT_SALT);
}


/* JAMES CODE 
1) getting the string until # appears 
2) need to deallocate the memory later!!*/
/**
 * @brief Gets the next word before the delimeter appears
 *
 * @param string The entire line containing the delimeter.
 * @param delimeter A character used to indicate the end of the word.
 * @return NULL if the string is empty, pointer to the string otherwise.
 */
char *getNextWord(char **string, char delimeter) 
{
   char *pointer;
   char *word = *string;
   int i;

   //No Character
   if (word == NULL) {
   	return NULL;
   }
   
   pointer = (char *)malloc(sizeof(char) * MAX_CONFIG_LINE_LEN);
   for ( i = 0; i < strlen(word); i++) {
   	 if ( *(word +i) != delimeter) {
   	 	*(pointer+i) = *(word+i);
   	 	(*string)++;
   	 }
   	 else {
   	 	//adding the null character at the end
   	 	*(pointer+i) = '\0';
   	 	(*string)++;
   	 	return pointer;
   	 }
   }
   if (pointer != NULL)
   free(pointer);
   pointer = NULL;
   //no # appeared until the end of file.
   return pointer;
}

/**
 * @brief Checks the parameter enter by the user to see if it is valid.
 *
 * @param parameter A string that needs to be checked.
 * @return true if valid, false otherwise.
 */
bool parameterCheck(char *parameter)
{

    //Fix the newline character to a NULL character
   	char *fix = strchr(parameter,'\n');
    if (fix)
        *fix = '\0';
    //End of fixing

    char *temp = parameter;
    bool valid = true;
   	
    while(*temp!='\0' && valid == true)
    {
        if((*temp>='0'&&*temp<='9')||(*temp>='a'&&*temp<='z')||(*temp>='A' && *temp <='Z')){
            valid = true;
            temp++; 
        }
        else{
            valid = false;
            return false;
        }
    }
    return valid;
}

/**
 * @brief Checks the parameter if it is a valid record value
 *
 * @param parameter A string that needs to be checked.
 * @return true if valid, false otherwise.
 */

bool valueCheck(char *parameter)
{

	if (parameter == NULL)
		return false;
    //Fix the newline character to a NULL character
    char *fix = strchr(parameter,'\n');
    if (fix)
        *fix = '\0';
    //End of fixing

    char *temp = parameter;
    bool valid = true;;

    while(*temp!='\0' && valid == true)
    {
        if((*temp>='0'&&*temp<='9')||(*temp>='a'&&*temp<='z')||(*temp>='A'&&*temp<='Z')||(*temp==' ')){
            valid = true;
            temp++; 
        }
        else{
            valid = false;
        }
    }
    
    return valid;
}


char* getColumnName(char **string)
{
   char *pointer;
   char *word = *string;
   int i;

   //No Character
   if (word == NULL) {
   	return NULL;
   }
   
   pointer = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
   for ( i = 0; i < strlen(word); i++) {
   	 if ( (*(word +i) != '>') && (*(word +i) != '<') && (*(word +i) != '=')) {
   	 	*(pointer+i) = *(word+i);
   	 	(*string)++;
   	 }
   	 else {
   	 	//adding the null character at the end
   	 	*(pointer+i) = '\0';
   	 	//(*string)++;
   	 	return pointer;
   	 }
   }
   if (pointer != NULL)
   free(pointer);
   pointer = NULL;
   //no # appeared until the end of file.
   return pointer;
}

void delete_char(char *stringS, int i)
{
	i =0;
	if (stringS == NULL)
		return;

	int totalLen = strlen(stringS);

	while(i<(totalLen-1))
	{

		*(stringS + i) = *(stringS + i +1);
		//fprintf(stderr, "%s",stringS[i]); //= stringS[i+1];

		i++;
	}


	stringS[i] = '\0';


}

char* delete_whiteSpace(char *string)
{
	if (string == NULL)
		return NULL;

	char* pointer = string;
	//Delete from the beginning
	while(*pointer== ' ')
	{
		delete_char(pointer,0);
	}
	
	int totalLen = strlen(pointer);
	int i;
	char *endPointer = pointer;
	//Delete at the end

	for(i = totalLen-1; endPointer[i] == ' '; i-- ){
		delete_char(pointer,i);
	}
	
	return pointer;
}

bool queryCheck(char *predicates)
{	
	if(predicates == NULL)
		return false;
	//Fix the newline character to a NULL character
    char *fix = strchr(predicates,'\n');
    if (fix)
        *fix = '\0';
    //End of fixing

    char *temp = predicates;

    bool valid = true;;

    //Check to make sure all characters are valid
    while(*temp!='\0' && valid == true)
    {
        if((*temp>='0'&&*temp<='9')||(*temp>='a'&&*temp<='z')||(*temp>='A'&&*temp<='Z')||(*temp==' ') 
        	|| (*temp==',') || (*temp=='<') || (*temp=='>') || (*temp=='=') || (*temp=='-')){
            valid = true;
            temp++; 
        }
        else{
            valid = false;
            return valid;
        }
    }


	char *findPredicates = predicates;
    int numPredicates = 0;
    int numSeparators = 0;
    while(*findPredicates){
       	if((*findPredicates=='>')||(*findPredicates=='<')||(*findPredicates=='='))
       		numPredicates++;
       		*findPredicates++;
        }

    //Check if they entered comparators
    if(numPredicates==0)
    	return false;

    findPredicates = predicates;
    while(*findPredicates){
       	if(*findPredicates==',')
       		numSeparators++;
       		*findPredicates++;
        }

    //Check if the number of comparators match the number of commas
    if(numSeparators!=(numPredicates-1))
    	return false;

    
    
    temp = predicates;
    //printf("%s\n",temp);
    temp = delete_whiteSpace(predicates);
    //printf("%s\n",temp);

    //Check to make sure correct format
    while(*temp!='\0')
    {
    	//Check if Column name correct
    	temp = delete_whiteSpace(temp);
    	//printf("%s\n",temp);
    	while(*temp!=' ' && *temp!='\0' && *temp!='>'&& *temp!='<'&&*temp!='='){
    		//printf("%c\n",*temp);
    		temp++;
    	}

    	if(*temp == '\0'){
    		valid = false;
    		return valid;
    	}
    	else{
    		printf("%c\n",*temp);
    		temp = delete_whiteSpace(temp);

    		printf("%s\n",temp);
    	}	
    	
    	if(*temp!='>'&& *temp!='<'&&*temp!='=')
    		return false;

    	temp++;
    	temp = delete_whiteSpace(temp);

    	//Check if value name correct
    	while(*temp!=',' && *temp!='\0')
    		temp++;	

    	if(*temp==',')
    		temp++;

    }




    
    return true;
}


//Changed to accomodate the new column-value method
bool recordCheck(char *parameter)
{
	//Fix the newline character to a NULL character
    char *fix = strchr(parameter,'\n');
    if (fix)
        *fix = '\0';
    //End of fixing

   
   	//2) Deleting Process
		if (strlen(parameter)==0){
			return true;
		}
 		
    char *temp = parameter;

    bool valid = true;;

    //Check to make sure all characters are valid
    while(*temp!='\0' && valid == true)
    {
        if((*temp>='0'&&*temp<='9')||(*temp>='a'&&*temp<='z')||(*temp>='A'&&*temp<='Z')
        	||(*temp==' ') || (*temp==',') || (*temp=='-')){
            valid = true;
            temp++; 
        }
        else{
            valid = false;
            return valid;
        }
    }

    temp = parameter;
    //printf("%s\n",temp);
    temp = delete_whiteSpace(parameter);
    //printf("%s\n",temp);
    //Check to make sure correct format
    while(*temp!='\0' && valid == true)
    {
    	//Check if Column name correct
    	temp = delete_whiteSpace(temp);
    	//printf("%s\n",temp);
    	while(*temp!=' ' && *temp!='\0'){
    		//printf("%c\n",*temp);
    		temp++;
    	}

    	if(*temp == '\0'){
    		valid = false;
    		return valid;
    	}
    	else{
    		//printf("%c\n",*temp);
    		temp++;
    		temp = delete_whiteSpace(temp);
    	}

    	//Check if value name correct
    	while(*temp!=',' && *temp!='\0')
    		temp++;	
    }
    return valid;
}

char *addStringFirst (char *old_copy,char *extra_copy)
{
    char *output = (char *) malloc((strlen(old_copy)+strlen(extra_copy)+1) *  sizeof(char));
	//just need to make sure there is extra 
    strcpy(output, old_copy);
    strcat(output, extra_copy);
    return output;
}

char* addStringSecond (char *old_copy ,char *extra_copy)
{
		char* output = (char *) malloc((strlen(old_copy)+strlen(extra_copy)+1) *  sizeof(char));
		/*
		int i = 0;
		for (i = 0; i < strlen (old_copy); i++){
			output[i] = old_copy[i];	
		}*/
		strcpy(output, old_copy);
    	strcat(output, extra_copy);
    	free (old_copy);
    	return output;
}

char *myStrDup (const char *s) {
	char *d;
	int length = (strlen (s));
	d = malloc (length + 1);   // Space for length plus null
	if (d == NULL) return NULL;          // No memory
		strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}


/**
 * @brief Check if the Table exists within the hash table container
 *
 * @param table_name string that contains the table_name
 * @param params A struct that contains all the config file info
 * @return true if duplicate exists, false if otherwise
 */

char* createMessage(char *oldValue)
{
	char *copy = myStrDup(oldValue);

	copy = delete_whiteSpace(copy);
	copy = addStringSecond(copy,",");

	char *temp = copy;
	char *columnName;
	char *value;

	long int intPassed;
	char *p;

	char *newValue = myStrDup("");

	//Delete all the white space before and after
	
	while(*temp)
	{	
		//Get the column name
		temp = delete_whiteSpace(temp);
		columnName = getNextWord(&temp,' ');

		newValue = addStringSecond(newValue,columnName);
		free(columnName);

		//Get the value
		value = getNextWord(&temp,',');
		value = delete_whiteSpace(value);

		//Check whether a string or int
		intPassed = strtol(value,&p,10);

		//Nothing converted
		if(value == p)
		{
			newValue = addStringSecond(newValue,STRINGSYMBOL);
			newValue = addStringSecond(newValue,value);
			free(value);
			newValue = addStringSecond(newValue,HASHTAG);	
		}
		else //It converted correctly
		{
			newValue = addStringSecond(newValue,INTSYMBOL);
			newValue = addStringSecond(newValue,value);
			free(value);
			newValue = addStringSecond(newValue,HASHTAG);
		}
		
	}

	free(copy);


	return newValue;
}

/**
 * @brief Check if the Table exists within the hash table container
 *
 * @param table_name string that contains the table_name
 * @param params A struct that contains all the config file info
 * @return true if duplicate exists, false if otherwise
 */

int isTableNameExist (char *table_name, struct config_params *params) {

	int num_table = params->table_number;
	int i;
	for (i=0; i<num_table; i++ ) {
		//found table!
		char *table = (params->table_names)[i].tablename;
		if (strcmp(table, table_name) == 0 )
			return i;
	}

	return -1;

}

/**
 * @brief Check if the input format for "SET" Function from the user is valid. 
 *
 * @param inputString string from the user
 * @param params A struct that contains all the config file info
 * @param table_index A table index of the hashtable container
 * @return true if duplicate exists, false if otherwise
 */

bool isInputFormatCorrect(char *inputString, struct config_params *params, int table_index) {

	printf("input String %s \n", inputString);
	bool status = true;

	char *column_info = params->table_names[table_index].column_info;
	int column_num = params->table_names[table_index].columnNum;

	//a. making it into "//value!1234#dkdj!4848#" format

	char *input_new = createMessage(inputString );
	printf("input String2 %s \n", input_new);

	int i;
	for (i =0; i<column_num; i++) {

		//b. getting column's id and type
		char *column_id = getNextWord(&column_info, '#');
		char *column_type = getNextWord(&column_info, '#');
		char * column_char_size = NULL;
		char * input_column = NULL;
		char * input_name = NULL;

		//need to make another pointer copy to delete it later
		char *single_column = getNextWord(&input_new, '#');

		// 1. not enough column info
		if (single_column == NULL) {
			status = false;
		}

		// 2. still okay
		else {
			//1. checking if the input is char type
			input_column = single_column;
			input_name = getNextWord(&input_column, '/');

			//2. column_type is int && input_type is char -> wrong type
			if ( input_name != NULL && strcmp(column_type, "int") == 0)  {
				status = false;
			}

			//3. checking if the input is int type && column_type is int -> right type
			else if (input_name == NULL && strcmp(column_type, "int") == 0) {
	            // 1.a column name is not correct
	            input_column = single_column;
	            input_name = getNextWord(&input_column, '!');
	            printf("input String3 %s \n", input_column);
	            if (strcmp(column_id, input_name) != 0) {
	              status = false;
	            }

	            //checking if the input is right type
	            printf("input String4 %s \n", input_column);
	            bool status1 = isWhiteCharacter(input_column);
	            printf("input String5 %s \n", input_column);
	            printf("status1 %d", status1);
	            if (status1 == true) {
	            	status = false;
	            }	            
	            printf("input String6 %s \n", input_column);

			}


		      // column name is not correct 
		      else if (strcmp(column_id, input_name) != 0) {
		              status = false;
		      }

			//2. checking the string size 
			//confirmed that the type is char at this point
			else {
				column_char_size = getNextWord(&column_info, '#');
				int column_length = atoi(column_char_size);
				int input_length = strlen(input_column);

				if (input_length > column_length) {
					//status = false;
				}

				else 
					printf("correct size type char\n");
			}
		}

		//Deallocate all
		free(column_id);
		free(column_type);
		free(column_char_size);
		free(single_column);
		free(input_name);

	}

	return status;
}

bool isStringInt (char *testString) {
	char *p;
	long int temp = strtol(testString,&p,10);

	if 	(testString != p) 
		return true;

	return false;

}


/**
 * @brief Check if the ColumnIndexs are valid. 
 *
 * @param params A struct that contains all the config file info
 * @return true if valid, false if otherwise
 */

bool isValidColumnIndex (struct config_params *params) {
	
	bool status = true;
	int i;
	//iterate through all the tables
	for (i=0; i< params->table_number; i++) {
		
		//getting the column_index String
		//setting the column_index_num = 0;
		char *listString[MAX_STRING_SIZE];
		char* column_info = params->table_names[i].column_info;
		params->table_names[i].columnNum = 0;

		//checking how many column_index number 
		char *column_id = getNextWord(&column_info, '#');
		char *column_size = NULL;

		while (column_id != NULL) {
		
			char *column_type = getNextWord(&column_info, '#');

			if (strcmp(column_type, "char") == 0) {
				column_size = getNextWord(&column_info, '#');
        
        if (column_size[0] == '0')
          status = false;
      }

			if (column_id != NULL) {
				listString[params->table_names[i].columnNum] = (char *)malloc (sizeof (char) * MAX_STRING_SIZE);
				strcpy(listString[params->table_names[i].columnNum], column_id);
			}

			free(column_id);
			free(column_type);
			free(column_size);
			column_size = NULL;

			column_id = getNextWord(&column_info, '#');
			params->table_names[i].columnNum ++;

			
		}

		// if the column index number is greater than 10, return false
		if (params->table_names[i].columnNum > 10) {
			status = false;
		}

		//checking if there is any duplicate
		bool isDuplicateColumn = isDuplicateColumnIndex(listString,params->table_names[i].columnNum );
		if (isDuplicateColumn)
			status = false;
	}

	return status;

}
/**
 * @brief Check if there is any duplicate column index. 
 *
 * @param input string that has all the column_info
 * @param length how many column in the string
 * @return true if duplicate exists, false if otherwise
 */

bool isDuplicateColumnIndex (char** input, int length) {


	int i,j;
	for ( i=0; i<length; i++) {
		for (j=i+1; j<length; j++) {
			if (strcmp(input[i], input[j]) == 0) {
				freeAllList(input, length);
				return true;
			}
		}
	}

	//free all
	freeAllList(input,length);
	return false;
}

/**
 * @brief Deallocate all the memoires in the heap (only for the specific string type)
 *
 * @param input string that has all the column_info
 * @param length how many column in the string
 * @return void
 */

void freeAllList (char ** input, int length) {

	int i;
	for (i=0; i<length; i++) {
		free(input[i]);
	}

}


int getNumPredicates(char *predicates)
{
	    int numPredicates = 0;
	    char *findPredicates = predicates;
        while(*findPredicates){
        	if((*findPredicates=='>')||(*findPredicates=='<')||(*findPredicates=='='))
        		numPredicates++;
        		*findPredicates++;
        }

        return numPredicates;
}

Predicate* createPredicateList (int numPredicates, char* predicate){
	//Parse the predicates for bitch ass Arash

		char *copy = myStrDup(predicate);
		copy = addStringSecond(copy,",");

		char *predicates = copy;
		printf("%s\n",predicates );
     	char *temp;
        char *columnName;
        char op;
        char *value;	
       	int currentPredicate;


       	Predicate * predicateList = (Predicate *)malloc(sizeof(Predicate) * numPredicates);

        for(currentPredicate = 0; currentPredicate < numPredicates; currentPredicate++)
        {
        	//Get the column name
        	temp = getColumnName(&predicates);

        	//Strip whitespace from column name
        	columnName = delete_whiteSpace(temp);
        	strcpy(predicateList[currentPredicate].column,  columnName);

        	printf("%s",predicateList[currentPredicate].column);
        	free(temp);


        	//Get the operator
        	op = predicates[0];
        	delete_char(predicates,0);

        	predicateList[currentPredicate].op = op;
        	printf("%c",predicateList[currentPredicate].op);
        	
        	//Get the value
        	//if(currentPredicate < numPredicates){
        	temp = getNextWord(&predicates,',');
        	value = delete_whiteSpace(temp);
        	strcpy(predicateList[currentPredicate].value,  value);
        	printf("%s",predicateList[currentPredicate].value);
        	free(temp);
        	//}
        	/*else{
        		value = delete_whiteSpace(predicates);
        		printf("%s",value);	
        	}*/
        		
   			
        }


     free(copy);
    return predicateList;

} 



/**
 * @brief Check if the predicates inputs are valid. 
 *
 * @param predicates A struct that contains all the predicates info
 * @param params A struct that contains all the config file info
 * @param table_index A table index of the hashtable container
 * @param numPredicates A number of predicates
 * @return 0 on success, -1 if otherwise
 */


int isPredicateValid(Predicate* predicates, struct config_params *params, int table_index, int numPredicates) {

  int status;

  //column infos
  char *column_info = params->table_names[table_index].column_info;
  int column_num = params->table_names[table_index].columnNum;

  int i;
  int j;

  //allocating memories to save column_names and input_names
  char **column_names;
  char **input_names;
  column_names =  (char **) malloc (sizeof(char*) * column_num);
  input_names =  (char **) malloc (sizeof(char*) * column_num);

  for (i =0; i<column_num; i++) {
    column_names[i] = (char *)malloc (sizeof(char) *MAX_STRING_SIZE);
    input_names[i] = (char *)malloc (sizeof(char) *MAX_STRING_SIZE);
  }


  //saving column names
  for(i=0; i<column_num; i++) {
    char *column_id = getNextWord(&column_info, '#');
    char *column_type = getNextWord(&column_info, '#');
    char *column_size;

    if (strcmp(column_type, "char") == 0) {
      column_size = getNextWord(&column_info, '#');
      free(column_size);
    }

    strcpy(column_names[i], column_id);

    free(column_id);
    free(column_type);
  }

  //saving predicates names
  for (i=0; i<numPredicates; i++) {
    strcpy(input_names[i], predicates->column);
    predicates ++;
    printf("\n isPredicate info %s number %d \n", input_names[i], i);
  }

  //checking if there is any duplicate
  for (i=0; i<numPredicates; i++) {
    for (j=0; j<numPredicates; j++) {
      if ( i != j && strcmp(input_names[i],input_names[j]) == 0) {
        printf("duplicate predicates \n");
        status =  INVALID;
      }
    }
  }

  //checking if all the predicates are valid
  bool isThereMatch = false;
  for ( i=0; i<numPredicates; i++) {
    for (j =0; j<column_num; j++) {
        if (strcmp(input_names[i], column_names[j]) == 0)
          isThereMatch = true;
    }

    if (isThereMatch == false)
      status =  INVALID;
  }

  status =  VALID;

  //deallocate memory
  for (i =0; i<column_num; i++) {
    free (column_names[i]);
    free (input_names[i]);
  }
  free(column_names);
  free(input_names);

  return status;
}