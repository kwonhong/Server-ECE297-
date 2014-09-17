/**
 * @file
 * @brief This file implements a "very" simple sample client.
 * 
 * The client connects to the server, running at SERVERHOST:SERVERPORT
 * and performs a number of storage_* operations. If there are errors,
 * the client exists.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "storage.h"
#include "utils.h"
#include <time.h>
#include <sys/time.h>

#define SERVERHOST "localhost"
#define SERVERPORT 1111
#define SERVERUSERNAME "admin"
#define SERVERPASSWORD "dog4sale"
#define TABLE "marks"
#define KEY "ece297"
#define MAX_STRING_SIZE 300
#define EXIT -1
#define NOT_EXIT 1
#define FAILED_AUTH 0
/*
	LOGGING CONTROL CAPABILITY FOR CLIENT REQUESTS
	0 - NO OUTPUT
	1 - PRINTED OUTPUT
	2 - PRINTED TO FILE OUTPUT
*/
#define LOGGING 0


/*
	Global Variable File Names for Server Access & Session Access
*/
//Outputting error Messages using a global array of strings
const char *errorMessage[] = {"","Invalid Parameter", "Connection Failed", "Not Authenticated", "Authentication Failed","Table Not Found","Key Not Found","Unknown","Transaction Aborted"};

//Total client Workload time
double total_client_process_time;

extern FILE *ClientFileLog;


/**
 * @brief Process the connection command from the client
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10
 */

 int menuConnect (void **conn){
    char hostname[MAX_STRING_SIZE];
    char tempPort[MAX_STRING_SIZE];

    if(*conn!=NULL)
    {
        printf("Already Connected");
        return NOT_EXIT;
    }

    printf("Please input the hostname: ");  
    fgets(hostname, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(hostname,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
    
    long int port;
    char* p;
    printf("Please input port: ");
    fgets(tempPort, MAX_STRING_SIZE, stdin);
    
    port = strtol(tempPort, &p, 10);

    // Connect to server
    printf ("Attempting to connect to %s...\n", hostname);
    *conn = storage_connect(hostname, (int)port);
    if(!(*conn)) {
        
      printf("Cannot connect to server @ %s:%ld.\n Error code: %d. %s\n",
             hostname, port, errno, errorMessage[errno]);
      //return EXIT;
    }
    else{
    printf ("Successfully connected to %s!\n", hostname);    
    }
   
    return NOT_EXIT;
}

/**
 * @brief Process the authentication provided from the client
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10 if successful, 0 othersiwe
 */
//Function Required for Menu Authentication
int menuAuthenticate (void **conn){
    char username[MAX_STRING_SIZE];
    char password[MAX_STRING_SIZE];

    //Parse the Input
    printf("Please input the username: ");
    fgets(username, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(username,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    printf("Please input the password: ");
    fgets(password, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    temp = strchr(password,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    // Authenticate the client.
    printf("Attempting to authenticate...\n");
    int status = storage_auth(username, password, *conn);
    if(status != 0) 
    {
        printf("storage_auth failed with username '%s' and password '%s'. " \
         "\nError code: %d. %s\n", username, password, errno,errorMessage[errno]);
        return FAILED_AUTH;
    }
    else
    {
         printf("storage_auth: successful.\n");  
    } 

    return NOT_EXIT;
}


/**
 * @brief Process the client's request for an entry stored in the database
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10 
 **/

int menuGet (void **conn){
    char tempString[MAX_STRING_SIZE];
    char table[MAX_STRING_SIZE];
    char key[MAX_STRING_SIZE];
    struct storage_record r;

    printf("Please enter a table: ");
    fgets(table, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(table,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    printf("Please input key: ");
    fgets(key, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    temp = strchr(key,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    // Issue storage_get
    int status = storage_get(table, key, &r, *conn);

    if(status != 0) {
      printf("storage_get failed.\nError code: %d. %s\n", errno,errorMessage[errno]);
      //storage_disconnect(*conn);
      //return status;
    }
    else{
        printf("storage_get: the value returned for key '%s' is '%s'.\n",
        key, r.value);
    }
    gettimeofday(&end_time, NULL);
    double tempEvaluationTime = (end_time.tv_usec) - (start_time.tv_usec);
    total_client_process_time += tempEvaluationTime;
    sprintf(tempString, "[PERFORMANCE] Client GET Processing Time: %lf microseconds.\n", tempEvaluationTime);
    logger(ClientFileLog, tempString);
    sprintf(tempString, "[PERFORMANCE] Current Accumulated Processing Time: %lf microseconds.\n", total_client_process_time);
    logger(ClientFileLog, tempString);

    return NOT_EXIT;

}

/**
 * @brief Process the clients request to insert/remove an entry in the database
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10 if successful, 0 othersiwe
 */
int menuSet (void **conn){
    char tempString[MAX_STRING_SIZE];
    char table[MAX_STRING_SIZE];
    char key[MAX_STRING_SIZE];
    char record[MAX_STRING_SIZE];
    struct storage_record r;

    printf("Please enter a table: ");
    fgets(table, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(table,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
    
    printf("Please input key: ");
    fgets(key, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    temp = strchr(key,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
   
    printf("Please input value: ");
    fgets(record, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets


    temp = strchr(record,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    // Issue storage_set
    strncpy(r.value, record, sizeof r.value);
    int status = storage_set(table, key, &r, *conn);
    if(status != 0) {
      if(status==EXIT){
        printf("storage_set failed.\nError code: %d. %s\n", errno,errorMessage[errno]);
        return NOT_EXIT;
      } 
      printf("storage_set failed.\nError code: %d. %s\n", errno,errorMessage[errno]);
      //storage_disconnect(*conn);
      //return status;
    }
    else
    {
        printf("Key Set Successful\n");
    }

    gettimeofday(&end_time, NULL);
    double tempEvaluationTime = (end_time.tv_usec) - (start_time.tv_usec);
    total_client_process_time += tempEvaluationTime;
    sprintf(tempString, "[PERFORMANCE] Client SET Processing Time: %lf microseconds.\n", tempEvaluationTime);
    logger(ClientFileLog, tempString);
    sprintf(tempString, "[PERFORMANCE] Current Accumulated Processing Time: %lf microseconds.\n", total_client_process_time);
    logger(ClientFileLog, tempString);
    return NOT_EXIT;
}
/**
 * @brief Process to query the database from the client's command
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10 if successful, 0 othersiwe
 */
int menuQuery (void **conn){
    char tempString[MAX_STRING_SIZE];
    char table[MAX_STRING_SIZE];
    char predicates[MAX_STRING_SIZE];
    char tempMax_keys[MAX_STRING_SIZE];

    struct storage_record r;

    printf("Please enter a table: ");
    fgets(table, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(table,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet

    printf("Please enter your predicates:");
    fgets(predicates, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    temp = strchr(predicates,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
    
    long int max_keys;
    char* p;

    printf("Please enter the amount of keys you would like:");
    fgets(tempMax_keys, MAX_STRING_SIZE, stdin);
    //Code Snippet Required to remove the '/n' saved by fgets
    temp = strchr(tempMax_keys,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
    max_keys = strtol(tempMax_keys, &p, 10);

    //Allocate memory for the 2D array of keys
        int i = 0;
    char **keys = (char **) malloc (sizeof(char*) * max_keys);

    for (i = 0; i < max_keys; i++){
        keys[i] = (char *) malloc (sizeof(char*) * max_keys);
    }
    
    int status = storage_query(table,predicates,keys,max_keys,*conn);
    for (i = 0; i < max_keys; i++)
            free(keys[i]);
    free(keys);
    if(status == -1) {
        printf("storage_query failed.\nError code: %d. %s\n", errno,errorMessage[errno]);
        return NOT_EXIT;
    }

     printf("Key Query Successful. Keys Found: %d\n",status);


    return NOT_EXIT;

}

/**
 * @brief Process the disconnection command from the client
 *
 * @param conn The connection established between the client and the server
 * @return Returns 10 if successful, 0 othersiwe
 */
int menuDisconnect (void **conn){
    // Disconnect from server
    int status = storage_disconnect(*conn);
    if(status != 0) {
      printf("storage_disconnect failed.\nError code: %d. %s\n", errno, errorMessage[errno]);
      return NOT_EXIT;
    }
    printf("Successfully disconnected!\n");
    *conn = NULL;
    return 0;
}

/**
 * @brief Start a client to interact with the storage server.
 *
 * If connect is successful, the client performs a storage_set/get() on
 * TABLE and KEY and outputs the results on stdout. Finally, it exists
 * after disconnecting from the server.
 */
int main(int argc, char *argv[]) {
    total_client_process_time = 0;
    /*Arash Khazaei - Parsing */
    char tempString[MAX_STRING_SIZE];
	
    time_t rawtime;
    struct tm *tm_struct;
    time (&rawtime);
    tm_struct = localtime (&rawtime);
	sprintf(tempString, "Client-%d-%d-%d-%d-%d-%d.log",1900+ tm_struct->tm_year, 1+ tm_struct->tm_mon, tm_struct->tm_mday, tm_struct->tm_hour,  tm_struct->tm_min, tm_struct->tm_sec);
	
	if (LOGGING == 2){
   		ClientFileLog = fopen(tempString, "a");
   	}else if (LOGGING == 1){
   		ClientFileLog = stdout;
   	}else{
   		ClientFileLog = NULL;
   	}

    //exitStatus determines whether we should still parse commands
    void **conn = NULL;
    int exitStatus = NOT_EXIT;         //MACRO CALLED NOT_EXIT use it


    //The loop that requests user inputs - breaks when exitStatus is set to true
    while (exitStatus != EXIT){
        int menuChoice =0;
        //Menu Options List
        printf("\nECE297 Command-Line Shell:\n");
        printf ("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        printf (" 1) Connect:\n");
        printf (" 2) Authenticate:\n");
        printf (" 3) Get:\n");
        printf (" 4) Set:\n");
        printf (" 5) Query:\n");
        printf (" 6) Disconnect:\n");
        printf (" 7) Exit: \n");
        printf ("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
        
        printf("Please Enter your Selection: ");
        //If the input is more than 1 item, then it clears the buffer so it can read again

        if (scanf("%d", &menuChoice) != 1){
            while (getchar() != '\n');
        }else{
            while (getchar() != '\n');
        }

        //Menu Options
        if (menuChoice == 1){
            exitStatus = menuConnect(&conn);
        } else if (menuChoice == 2){
            exitStatus = menuAuthenticate(&conn);
        } else if (menuChoice == 3){
            exitStatus = menuGet(&conn);
        } else if (menuChoice == 4){
            exitStatus = menuSet(&conn);
        } else if (menuChoice == 5){
            exitStatus = menuQuery(&conn);
        } else if (menuChoice == 6){
            exitStatus = menuDisconnect(&conn);
        } else if (menuChoice == 7){
            exitStatus = EXIT;
        } else {
            printf("  Invalid input, enter a choice from 1-7.\n");
        }

    }

    sprintf(tempString, "[PERFORMANCE] TOTAL END-TO-END PROCESSING TIME: %lf microseconds.\n", total_client_process_time);
    logger(ClientFileLog, tempString);
    if (ClientFileLog != NULL)
    	fclose(ClientFileLog);
  // Exit
  return 0;
}
