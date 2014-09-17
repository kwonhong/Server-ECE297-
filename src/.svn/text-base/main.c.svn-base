//
//  main.c
//  Server
//
//  Created by Arash Khazaei on 2014-01-19.
//  Copyright (c) 2014 Arash Khazaei. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_SIZE 500

void menuConnect (){
    char hostname[MAX_STRING_SIZE];
    char tempPort[MAX_STRING_SIZE];
    bool isPortValid = false;

    printf("Please input the hostname: ");
    while (fgets(hostname, MAX_STRING_SIZE, stdin)==NULL || hostname[0]=='\n'){
        printf("   Invalid hostname, please try again: ");
    }
    //Code Snippet Required to remove the '/n' saved by fgets
    char* temp = strchr(hostname,'\n');
    if (temp)
        *temp = '\0';
    //End of Code Snippet
    
    long int port;
    char* p;
    printf("Please input port: ");
    while (!isPortValid){
    if (fgets(tempPort, MAX_STRING_SIZE, stdin) != NULL)
    {
        port = strtol(tempPort, &p, 10);
        
        /*
         *  If the first character of the buffer is \n, the user
         *  pressed [Enter] with entering any text at all, which
         *  is therefore invalid.
         *
         *  The pointer p has been updated by strtol() to point to
         *  the first invalid character after the number.
         *  If this character is \0 it means we reached the end of
         *    the array successfully, so we received a good number.
         *  If this character is \n it also means we reached the
         *    end of the input successfully.  This is a symptom of
         *    using fgets() to obtain the string, but does not
         *    represent a problem.
         *  If this character is anything else, it means there was
         *    some additional characters entered after the number.
         *    In this sample program, I have deemed this situation
         *    to be invalid, however, in your program it may be
         *    valid, depending on what you're expecting from the user.
         *
         */
        
        if (tempPort[0] != '\n' && (*p == '\n' || *p == '\0'))
            isPortValid = true;//flags that correct port was entered
        else  printf ("   Invalid port, please try again: ");
    }
    }
    printf("Connecting to %s:%ld...\n",hostname, port);
}


void menuAuthenticate (){
    char userName[MAX_STRING_SIZE];
    char passwd [MAX_STRING_SIZE];
    char conn [MAX_STRING_SIZE];
    
    printf("Please input the username: ");
    while (fgets(userName, MAX_STRING_SIZE, stdin)==NULL || userName[0]=='\n'){
        printf("   Invalid username, please try again: ");
    }
    
    printf("Please input the password: ");
    while (fgets(passwd, MAX_STRING_SIZE, stdin)==NULL || passwd[0]=='\n'){
        printf("   Invalid password, please try again: ");
    }
    
    printf("Please input the connection: ");
    while (fgets(conn, MAX_STRING_SIZE, stdin)==NULL || conn[0]=='\n'){
        printf("   Invalid connection, please try again: ");
    }
}

void menuGet (){
    char table[MAX_STRING_SIZE];
    char key[MAX_STRING_SIZE];
    char record[MAX_STRING_SIZE];
    char connection[MAX_STRING_SIZE];
    printf("Please enter a table: ");
    while (fgets(table, MAX_STRING_SIZE, stdin)==NULL || table[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input key: ");
    while (fgets(key, MAX_STRING_SIZE, stdin)==NULL || key[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input record: ");
    while (fgets(record, MAX_STRING_SIZE, stdin)==NULL || record[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input the connection: ");
    while (fgets(connection, MAX_STRING_SIZE, stdin)==NULL || connection[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
}

void menuSet (){
    char table[MAX_STRING_SIZE];
    char key[MAX_STRING_SIZE];
    char record[MAX_STRING_SIZE];
    char connection[MAX_STRING_SIZE];
    printf("Please enter a table: ");
    while (fgets(table, MAX_STRING_SIZE, stdin)==NULL || table[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input key: ");
    while (fgets(key, MAX_STRING_SIZE, stdin)==NULL || key[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input record: ");
    while (fgets(record, MAX_STRING_SIZE, stdin)==NULL || record[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
    printf("Please input the connection: ");
    while (fgets(connection, MAX_STRING_SIZE, stdin)==NULL || connection[0]=='\n'){
        printf("   Invalid input, please try again: ");
    }
}

void menuDisconnect (){
    char connection[MAX_STRING_SIZE];
    printf("Please input the connection: ");
    while (fgets(connection, MAX_STRING_SIZE, stdin)==NULL || connection[0]=='\n'){
        printf("   Invalid connection, please try again: ");
    }
}


int main(int argc, const char * argv[])
{
    //Exit status determines whether we should still parse commands
    bool exitStatus = false;
    printf("Starting Session...\n");
    printf("Choose from options below:\n");

    
    //The loop that requests user inputs - breaks when exitStatus is set to true
    while (!exitStatus){
        int menuChoice;
        //Menu Options
        printf ("\n-----------------\n");
        printf (" 1) Connect:\n");
        printf (" 2) Authenticate:\n");
        printf (" 3) Get:\n");
        printf (" 4) Set:\n");
        printf (" 5) Disconnect:\n");
        printf (" 6) Exit: \n");
        printf ("-----------------\n");
        
        printf("Please Enter your Selection: ");
        //If the input is more than 1 item, then it clears the buffer so it can read again
        if (scanf("%d", &menuChoice) != 1){
            while (getchar() != '\n');
        }else{
            while (getchar() != '\n');
        }
        
        //Menu Options
        if (menuChoice == 1){
            menuConnect();
        } else if (menuChoice == 2){
            menuAuthenticate();
        } else if (menuChoice == 3){
            menuGet();
        } else if (menuChoice == 4){
            menuSet();
        } else if (menuChoice == 5){
            menuDisconnect();
        } else if (menuChoice == 6){
            exitStatus = true;
        } else {
            printf("  Invalid input, enter a choice from 1-6.");
        }
    }
    
    printf("Session Exited.\n");
    return 0;
}

