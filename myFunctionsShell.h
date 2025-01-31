#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * gets input from the user
 *
 *this function activates a loop that expects the user to enter input, the loop ends when the 'enter' key is pressed
 * 
 * @return a char array of the user input
 *
 */
char* inputFromUser();


/**
 * Prints location of this program
 *
 * Prints the user name and computer name and then the current path the program is run on 
 */
void getLocation();


/**
 * Splits a string into individual tokens based on whitespace.
 *
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 *
 * @param input A pointer to the string to be split.
 *
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 *
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 *
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char **splitArguments(char* );
void systemCall(char** arguments);
void logout();
void myPipe(char** argv1, char** argv2, char **argv3);
void cd(char **arguments);
void cp(char **arguments);
void del(char **arguments);
int getPipe(char **arguments);
void move(char **arguments);
void echoFile(char **arguments);
