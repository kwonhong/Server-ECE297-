/**
 * @file
 * @brief This file implements the hash table.
 *
 * This file contains the implementation of the hash table.
 * The code in this file is a modification of the code made available
 * online as a demo, by Tony Thompson, GIT username: (tonious).
 *
 * Additional features and modifications were made the ECE297 team.
 * 
 */
#include "hashTable.h"
/**
 * @brief Creates a copy of a given string.
 *
 * @param s The string that needs to be copied.
 * @return Returns a dynamically allocated pointer to the copy made, NULL if otherwise.
 */
 /*
char *myStrDup (const char *s) {
	char *d;
	int length = (strlen (s));
	d = malloc (length + 1);   // Space for length plus null
	if (d == NULL) return NULL;          // No memory
		strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}*/

/**
 * @brief Creates the hash table data structure.
 *
 * @param size The size of the hash table.
 * @return Returns a pointer to the created hash table if successful, NULL otherwise.
 */
HashTable *ht_create( int size ) {
	HashTable *hashtable = NULL;
	int i;
 
	if( size < 1 ) return NULL;
 
	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( HashTable ) ) ) == NULL ) {
		return NULL;
	}
 
	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( Entry * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}
	hashtable->size = size;
 
	return hashtable;	
}
 

/**
 * @brief Returns the hashing index 
 *
 * @param hashtable A pointer to the hash table.
 * @param key The key string to produce a hash index for.
 * @return Returns an integer hashing index which is used to locate a specific key.
 */
int ht_hash( HashTable *hashtable,  char *key ) {

	unsigned long int hashval;
	hashval = 0;
	int length = strlen( key );
	int i = 0;
	for (i = 0; i < length; i++)
 		hashval = hashval * 127 + key[i];
 	
	return hashval % hashtable->size;
}
 

/**
 * @brief Creates a pairing of Key and Value.
 *
 * @param key The string that saves the key.
 * @param value The string that saves the value.
 * @return Returns an Entry struct that contains a key and a value.
 */
Entry *ht_newpair( char *key, char *value ) {
	Entry *newpair;
 
 	/* Create a new Entry to store a key and value */
	if( ( newpair = malloc( sizeof( Entry ) ) ) == NULL ) {
		return NULL;
	}
 
 	/* A pointer to a new char* is returned containing a copy of the input string */
	if( ( newpair->key = myStrDup(key ) ) == NULL ) {
		return NULL;
	}
 
 	/* A pointer to a new char* is returned containing a copy of the input string */
	if( ( newpair->value = myStrDup(value ) ) == NULL ) {
		return NULL;
	}
 
 	/*When creating the new data initialize the metadata to */
 	newpair-> metadata = rand();
	newpair->next = NULL;
 
	return newpair;
}
 

/**
 * @brief Sets the Key and Value into the hashtable.
 *
 * @param hashtable A pointer to the hash table.
 * @param key The string that stores the key.
 * @param value The string that stores the value.
 * @return No return value.
 */
int ht_set( HashTable *hashtable, char *key, char *value ) {
	int bin = 0;
	Entry *newpair = NULL;
	Entry *next = NULL;
	Entry *last = NULL;
 
	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];
	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}
 
	/* There's already a pair.  Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {
 	


		free( next->value );
		next->value = myStrDup( value );
		next->metadata += 1;
		return HASH_SET_UPDATE;
	/* Nope, could't find it.  Time to grow a pair. */
	} else {

		newpair = ht_newpair( key, value );

		/* Ensure we have not run out of memory */
		if (newpair == NULL)
			return HASH_SET_FAIL;

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;
		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;
	
		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}

		/* We have successfully inserted */
		return HASH_SET_INSERT;
	}
	return 0; // success
}
 

 /**
 * @brief Retrieve a value corresponding to a given Key.
 *
 * @param hashtable A pointer to the hash table.
 * @param key The string that stores the key.
 * @param value The string that stores the value.
 * @returns an entry pointer.
 */
Entry *ht_get( HashTable *hashtable, char *key ) {
	int bin = 0;
	Entry *pair;
 
	bin = ht_hash( hashtable, key );
	/* Step through the bin, looking for our value. */
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}
 
	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;
 
	} else {
		return pair;
	}
	
}

 /**
 * @brief Iterates through entire hashtable and removes everything
 *
 * @param hashtable A pointer to the hash table.
 * @return VOID.
 */
void ht_removeAll (HashTable *hashtable){
		Entry *Head = NULL;
		Entry *temp = NULL;
		int x = 0;
		for (x = 0; x < hashtable->size; x++){ 	
			Head = hashtable->table[ x ];
			while (Head != NULL) {
			    temp = Head;
			    Head = temp->next;
			  		free (temp ->key);
			  		free (temp->value);
			    free(temp);
			    temp = NULL;
			}
			hashtable->table[x] = NULL;
		}
		hashtable->size = 0;
		free (hashtable->table);
}



char whatDataType (char* startIndex){
	int i = 0;
	while (startIndex[i] != '#'){
		if (startIndex[i] == INTEGER_SYMBOL)
			return INTEGER_SYMBOL;
		if (startIndex[i] == STRING_SYMBOL)
			return STRING_SYMBOL;
		i++;
	}
	return '\0';
}


//May be problematic! requires testing
bool bootlegEqualTo (char * predValue, char *hashTableValue){
	int i = 0;
	while (predValue[i] != NULL || hashTableValue[i] != '#'){
		if ( hashTableValue[i] != predValue[i] )
			return false;
		i++;
	}
	return true;
}

bool bootlegGreaterThan ( char * predValue, char * hashTableValue){

	printf ("fails Here \n");

	char * temp = myStrDup (hashTableValue);
	temp = strtok (temp, "#");

	//	int i = 0;
	//char * theHashTableValue =  strtok(hashTableValue, '#');
	//	char *theHashTableValue = "1234999999";
	char *p;

	int pred_number = strtol( predValue, &p, 10 );
	int ht_number = strtol(  temp, &p, 10 );

	free (temp);
	if (ht_number > pred_number){

		return true;
	}

	return false;

}

bool bootlegLessThan (char * predValue, char * hashTableValue){

	char * temp = myStrDup (hashTableValue);
	temp = strtok (temp, "#");

	//char * theHashTableValue =  strtok(hashTableValue, '#');
	//char *theHashTableValue = "1234999999";
	char *p;

	long int pred_number = strtol( predValue, &p , 10 );
	long int ht_number = strtol(  temp, &p , 10 );
	free (temp);
	if ( ht_number < pred_number )
		return true;
	return false;
}



//This will segfault if the formatting isn't correct
bool entry_query (Entry * entry, Predicate * predicates, int numPredicates ){
		int i = 0;

		char *newValue;
		newValue = createMessage( entry->value );
		//*temp ="'";
		for (i = 0; i < numPredicates; i++){
			//printf ("Entry Query: %s - %s \n", entry->value, predicates[i].value);
			//We are looking for a matching string

			if ( predicates[i].op == '='){
				char * temp = strstr(newValue, predicates[i].column);
				char operatorSymbol = whatDataType(temp);

				if (operatorSymbol != STRING_SYMBOL && operatorSymbol != INTEGER_SYMBOL){
					free (newValue);
					return false;	//Wrong Data Type - Big NoNo!
				}
					
				//Now lets find the starting position for the value of the predicate
				
				temp = strchr (temp, operatorSymbol);
				//Now move to where the item should be!

				temp++;


				//Compare to see if the value is the same as the keyValue(return false if not!)
				if (bootlegEqualTo (predicates[i].value, temp)== false){
					free (newValue);
					return false;	
				}
				//It didnt' get returned; lets iterate through predicate and see if the other conditions meet

			//We ae looking for a < integer
			} else if (predicates[i].op == '<'){

				char * temp = strstr(newValue, predicates[i].column);
				if (whatDataType(temp) != INTEGER_SYMBOL){
					free (newValue);
					return false;	//Wrong Data Type - Big NoNo!
				}

				//Now lets find the starting position for the value of the predicate
				temp = strchr (temp, INTEGER_SYMBOL);
				//Now move to where the item should be!
				temp++;
				//Compare to see if the value is actually less than predicate value
				if (bootlegLessThan (predicates[i].value, temp)== false){
					free (newValue);
					return false;
				}

				//It didnt' get returned; lets iterate through predicate and see if the other conditions meet


			//We are looking for a > integer
			} else {

				char * temp = strstr(newValue, predicates[i].column);
				if (whatDataType(temp) != INTEGER_SYMBOL){
					free (newValue);
					return false;	//Wrong Data Type - Big NoNo!					
				}

				//Now lets find the starting position for the value of the predicate
				temp = strchr (temp, INTEGER_SYMBOL);
				//Now move to where the item should be!
				temp++;

				//Compare to see if the value is actually less than predicate value
				if (bootlegGreaterThan (predicates[i].value, temp)== false){
					free (newValue);
					return false;
				}
			}
		}
	//iterated through entire key and all predicates matched
	free (newValue);
	return true;
}

/**
 * @brief Queries the hashtable and updates the array of strings called keysFound
 *
 * @param hashtable A pointer to the hash table.
 * @param operator The operator to determine what component to query.
 * @param predicate	The criteria to search for using the operator.
 * @param keysFound	The array of strings that contains all the keys that match the predicate and operation.
 * @return Returns the number of items found if successful, -1 if otherwise.
 */
int ht_query (HashTable *hashtable, Predicate * predicates, int numPredicates, char ** keysFound, int maxKeysFound){
	int numKeysFound = 0;
	Entry *temp = NULL;
	int x;
	int length = hashtable->size;
	for (x = 0; x < length; x++){ 	
		//fprintf(stderr, "X- ENTER: %d\n", x);
		temp = hashtable->table[ x ];
		while (temp != NULL) {
		    if (entry_query(temp, predicates, numPredicates)){
		    	if (numKeysFound < maxKeysFound){
		    		keysFound[numKeysFound] = myStrDup(temp->key);
		    	}
		    	numKeysFound++;
		    }
		    temp = temp->next;
		}
	}
	//if (numKeysFound == 0)
	//	return ;

	return numKeysFound;
}


/**
 * @brief Removes an item given a specific key
 *
 * @param hashtable A pointer to the hash table.
 * @param Key A pointer to the key to delete.
 * @return Returns the status of the removal, whether it was successful or not.
 */
int ht_removeItem ( HashTable *hashtable, char *key  ){
	Entry *curr = NULL;
	Entry *last = NULL;
 
	int bin = ht_hash( hashtable, key );
	curr = hashtable->table[ bin ];
	
	/* Key does not exist */
	if (curr == NULL)
		return KEY_NOT_FOUND;

 	/* Iterate through until we hit the end or find the key */
	while( curr->next != NULL && strcmp( key, curr->key ) != 0 ) {
		last = curr;
		curr = curr->next;
	}

	/* We hit the end and yet no key was found */
	if (strcmp (key, curr->key) != 0)
		return KEY_NOT_FOUND;

	/* Item was found! */
	/* We're at the start of the linked list in this bin. */
	if (curr == hashtable->table[bin]){
		Entry * temp = curr;
		curr = curr -> next;
			free (temp->key);
			free (temp->value);
			temp->next = NULL;
			free (temp);
			hashtable->table[bin] = curr;
			
		return HASH_SET_DELETE;
	/* We are at the end of the list in this bin */
	} else if ( curr->next == NULL ){
		free (curr->key);
		free (curr->value);
		free (curr);
		last->next = NULL;
		return HASH_SET_DELETE;
	/* We're in the middle of the list. */
	} else {
		last->next = curr-> next;
		free (curr->key);
		free (curr->value);
		free (curr);
		return HASH_SET_DELETE;
	}
}