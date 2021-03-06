/**
 * @file
 * @brief This file declares various utility functions that are
 * can be used by the storage server and client library.
 */

#ifndef	UTILS_H
#define UTILS_H

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include "storage.h"
#define MAX_STRING_SIZE 800
#define EXIT -1
#define NOT_EXIT 1
#define HASHTAG "#"
#define STRINGSYMBOL "/"
#define INTSYMBOL "!"

/*
	Enable Usage of Global Variables 
*/
//Setup a STRUCT for Arash Select
typedef struct listOfClients {
	int sock;
	bool authenticationStatus;
}ListOfClients;

/**
 * @brief Any lines in the config file that start with this character 
 * are treated as comments.
 */
static const char CONFIG_COMMENT_CHAR = '#';

/**
 * @brief The max length in bytes of a command from the client to the server.
 */
#define MAX_CMD_LEN (1024 * 8)

/**
 * @brief A macro to log some information.
 *
 * Use it like this:  LOG(("Hello %s", "world\n"))
 *
 * Don't forget the double parentheses, or you'll get weird errors!
 */
#define LOG(x)  {printf x; fflush(stdout);}


/**
 * @brief A macro to output debug information.
 * 
 * It is only enabled in debug builds.
 */
#ifdef NDEBUG
#define DBG(x)  {}
#else
#define DBG(x)  {printf x; fflush(stdout);}
#endif

/**
 * @brief A struct to store config parameters.
 */
 /*
struct config_params {
	/// The hostname of the server.
	char server_host[MAX_HOST_LEN];

	/// The listening port of the server.
	int server_port;

	/// The storage server's username
	char username[MAX_USERNAME_LEN];

	/// The storage server's encrypted password
	char password[MAX_ENC_PASSWORD_LEN];

	/// The storage server table name
	char tablename[MAX_CMD_LEN];
	/// The directory where tables are stored.
//	char data_directory[MAX_PATH_LEN];
	bool authorized;
};
*/

struct table {
	char tablename[MAX_STRING_SIZE];
	char column_info[MAX_STRING_SIZE];\
	char columnNum;
};
 


/**
 * @brief Encapsulate each predicate.
 *
 */
typedef struct predicate {
    char column [MAX_COLNAME_LEN];
    char op;
    char value [MAX_VALUE_LEN];
}Predicate;






struct config_params {
	/// The hostname of the server.
	char server_host[MAX_HOST_LEN];

	/// The listening port of the server.
	int server_port;

	/// The storage server's username
	char username[MAX_USERNAME_LEN];

	/// The storage server's encrypted password
	char password[MAX_ENC_PASSWORD_LEN];

	/// The storage server table name
	struct table table_names [MAX_TABLES];
	/// The directory where tables are stored.

	//store number of tables
	int table_number;
	int concurrencyMode;
//	char data_directory[MAX_PATH_LEN];
	bool authorized;
};


/**
 * @brief Exit the program because a fatal error occured.
 *
 * @param msg The error message to print.
 * @param code The program exit return value.
 */
static inline void die(char *msg, int code)
{
	printf("%s\n", msg);
	exit(code);
}

/**
 * @brief Keep sending the contents of the buffer until complete.
 * @return Return 0 on success, -1 otherwise.
 *
 * The parameters mimic the send() function.
 */
int sendall(const int sock, const char *buf, const size_t len);

/**
 * @brief Receive an entire line from a socket.
 * @return Return 0 on success, -1 otherwise.
 */
int recvline(const int sock, char *buf, const size_t buflen);

/**
 * @brief Read and load configuration parameters.
 *
 * @param config_file The name of the configuration file.
 * @param params The structure where config parameters are loaded.
 * @return Return 0 on success, -1 otherwise.
 */
int read_config(const char *config_file, struct config_params *params);

/**
 * @brief Generates a log message.
 * 
 * @param file The output stream
 * @param message Message to log.
 */
void logger(FILE *file,char* message);

/**
 * @brief Default two character salt used for password encryption.
 */
#define DEFAULT_CRYPT_SALT "xx"

/**
 * @brief Generates an encrypted password string using salt CRYPT_SALT.
 * 
 * @param passwd Password before encryption.
 * @param salt Salt used to encrypt the password. If NULL default value
 * DEFAULT_CRYPT_SALT is used.
 * @return Returns encrypted password.
 */

 //James
#define INVALID 12
#define VALID 11
char *generate_encrypted_password(const char *passwd, const char *salt);
char *getNextWord(char**word, char delimeter);
int isTableNameExist (char *table_name, struct config_params *params);
bool isInputFormatCorrect(char *input_string, struct config_params *params, int table_index);
bool isStringInt (char *testString);
bool isValidColumnIndex (struct config_params *params);
bool isDuplicateColumnIndex (char** input, int length);
void freeAllList (char ** input, int length);
int isPredicateValid(Predicate* predicates, struct config_params *params, int table_index, int numPredicates);


//Justin
bool parameterCheck(char *parameter);
bool valueCheck(char *parameter);
char* getColumnName(char **string);
bool queryCheck(char *predicates);
bool recordCheck(char *parameter);

char * addStringFirst(char *,char *);
char * addStringSecond(char *,char *);
char *myStrDup ( const char *s );

//void addString(char *s1,char *s2);
char *createMessage(char *oldValue);
int ThreadCounter;



#endif
