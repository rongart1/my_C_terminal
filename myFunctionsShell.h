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


/**
 * Executs a system call
 *
 * This function takes an array of strings as input as arguments and makes a system call to execute
 * a program with the name of arguments at index 0 with the rest of the strings being params
 *
 * @param input A pointer to the array of strings.
 *
 * @note the input of array of strings must and with a NULL terminator
 *
 * @warning the program might fail exeuting the command or open a new thread
 *          
 */
void systemCall(char** arguments);


/**
 * Stops the program
 *
 * @warning the funtion doesnt free any alocated memory so u must do so manually
 */
void logout();


/**
 * Executes three system calls and pipes there input in order
 *
 * This function takes 3 string arrays where each one of them must end with a NULL
 * the function then executes each program with the argv[0] being the program name and the rest of the argv being paramaters to the call
 * then the funcion passes the ressult as an input to the next call
 * 
 *
 * @param input 3 pointers to the each of the string arrays
 *
 *
 * @note if the third argv is null it will pipe the first two only
 *
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
void myPipe(char** argv1, char** argv2, char **argv3);

/**
 * Changes working directory
 *
 * This function takes an arguments array as inputs and changes the working directory to the second one
 *
 * @param input A pointer to arguments array
 *
 * @note passing a blank string as the second prameter will take u to the root of the computer
 */
void cd(char **arguments);


/**
 * copies a file contents to another file
 *
 * This function takes an arguments array string as inputs and where the first is dosenst matter
 * the second param is the is the file who's the content you want to copy
 * the third is the path of the file you want to copy the content to
 *
 * @param input A pointer to the string array of the arguments
 *
 * @note if the file you want to copy to does not exist it will create it and the copy
 */
void cp(char **arguments);

/**
 * Deletes a file
 *
 * This function takes an arguments string as input and deletes the file with the path of the second argument
 *
 * @param input A pointer arguments array *
 */
void del(char **arguments);

/**
 * iterates over the a string array and replaces the first '|' with a NULL
 *
 * 
 * the function takes an array of strings and makes the first '|' a NULL then returns the postion if the pipe
 *
 * @param input A pointer to the string array.
 *
 * @return the position of the first '|' or 0
 *
 * @note the funtion will only itarate on the string array until it finds a '|' or NULL
 */
int getPipe(char **arguments);

/**
 * moves a file to another directory
 *
 * This function takes an arguments array string as inputs and where the first is dosenst matter
 * the second param is the is the file who's directory you want to change
 * the third is the exact path you want to place the file into inluding the new file name
 *
 * @param input A pointer to the string array of the arguments
 *
 */
void move(char **arguments);


/**
 * either prints the input, place it in a file or append it to a file
 *
 * This function takes an arguments array string as inputs and where the first is dosenst matter
 * if the arguments length is only two it will print out the second argument
 * otherwise the function expects the 3 arguments after the first one to be:
 * <string> '>' path of file - this will overide the file's content found on the path with the string
 * or
 * <string> '>>' path of file - this will append the string to the file's content found on the path
 * any other third param will not be accepted
 * 
 *
 * @param input A pointer to the string array of the arguments
 *
 */
void echoFile(char **arguments);
