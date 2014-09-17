/**
 * @file
 * @brief This file implements the storage server.
 *
 * The storage server should be named "server" and should take a single
 * command line argument that refers to the configuration file.
 * 
 * The storage server should be able to communicate with the client
 * library functions declared in storage.h and implemented in storage.c.
 */
#ifndef HASH_TABLE
#define HASH_TABLE
#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */
//#include "storage.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define KEY_NOT_FOUND -127
#define HASH_SET_INSERT 147
#define HASH_SET_DELETE 157
#define HASH_SET_UPDATE 167
#define HASH_SET_FAIL 177
#define QUERY_FAIL	187
#define QUERY_SUCCESS 197
#define STRING_SYMBOL '/'
#define INTEGER_SYMBOL '!'

/**
 * @brief Encapsulate each entry to the hash table.
 *
 */
typedef struct entry {
    char* key;
    char* value;

    uintptr_t metadata;

    struct entry *next;
}Entry;

/**
 * @brief Encapsulate the hash table
 *
 */
typedef struct hashtable{
	int size;
	struct entry **table;	
}HashTable;
 

 //char *myStrDup ( const char *s );

 HashTable *ht_create( int size );

 int ht_hash( HashTable *hashtable, char *key );

 Entry *ht_newpair( char *key, char *value );

 int ht_set( HashTable *hashtable, char *key, char *value );

 Entry *ht_get( HashTable *hashtable, char *key );

 void ht_removeAll ( HashTable *hashtable );
 
 int ht_removeItem ( HashTable *hashtable, char *key  );

 int ht_query (HashTable *hashtable, Predicate * predicates, int numPredicates, char ** keysFound, int maxKeysFound);

 bool entry_query (Entry * entry, Predicate * predicates, int numPredicates );

 char whatDataType (char* startIndex);

 bool bootlegEqualTo (char * predValue, char *hashTableValue);

 bool bootlegGreaterThan ( char * predValue, char * hashTableValue);

 bool bootlegLessThan (char * predValue, char * hashTableValue);

#endif
