#include "myFunctionsShell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


char *inputFromUser()
{

    char ch;
    int len = 0;
    char *input = (char *)malloc(sizeof(char) * (len + 1));
    *input = '\0';
    while ((ch = getchar()) != '\n')
    {
     *(input + len) = ch;
        input = (char *)realloc(input, (++len + 1));
    }
    *(input + len) = '\0';

    return input;
}

void getLocation() {

    const char *GREEN = "\033[32m";
    const char *BLUE = "\033[34m";
    const char *RESET = "\033[0m";

    // Getting the user name
    char *userName = getenv("USER");
    if (!userName) {
        userName = "unknown_user";
    }

    // Getting the computer name
    char hostname[100] = "unknown_host"; // Default fallback
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        puts("Error getting computer name");
    }

    // Getting the current location
    char location[256];
    if (getcwd(location, sizeof(location)) == NULL) {
        puts("Error getting current location");
        return;
    }

    printf("%s%s@%s:%s%s%s$ ", 
        GREEN, userName,
        hostname,
        BLUE, location, RESET  // Location in blue
    );
}

void cd(char **arguments){
    int size = 0;
    while (arguments[size] != NULL) {
        size++;
    }
    
    if(size>2){
        perror("to manny arguments");
    }
    else if(size==1){
        chdir(getenv("HOME"));
    }else{
        chdir(arguments[1]);  
    }

}

void cp(char **arguments){

    int size = 0;
    while (arguments[size] != NULL) {
        size++;
    }
    

    if(size>3){
        perror("too manny arguments");
        return;
    }
    if(size<3){
        perror("missing arguments");
        return;
    }

    FILE *fptr1, *fptr2;
    int c;



    fptr1 = fopen(arguments[1], "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s\n", arguments[1]);
        exit(1);
    }


    fptr2 = fopen(arguments[2], "w");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s\n", arguments[2]);
        exit(1);
    }

    while ((c = fgetc(fptr1)) != EOF)
    {
        fputc(c, fptr2);
    }


    fclose(fptr1);
    fclose(fptr2);
    

}

char **splitArguments(char* arr){

    int len = strlen(arr);
    int ind = 0;

    char** words = calloc(len+1, sizeof(char*));

    int stringMode = 0;

    words[0] = arr; 

    if(arr[0] == '"'){
        arr[0] = arr[1];
        stringMode = !stringMode;
    }
        

    for (int i = 0; i < len; i++) {
        if (arr[i] == '"') {
            stringMode = !stringMode;
            arr[i] = '\0';
        }

    
        if (arr[i] == ' ' && !stringMode) {

            arr[i] = '\0';
            

            if(arr[i+1] == '"'){
                words[++ind] = &arr[i + 2];
            }
            else
                words[++ind] = &arr[i + 1];
        }
    }

    if (stringMode) {
        puts("Error: Unclosed string detected");
        return NULL;
    }

    if(arr[len-1] == '"'){
        arr[len-1] = '\0';
    }


    words = realloc(words, sizeof(char*) * (ind + 2));
    if (words == NULL) {
        perror("Error reallocating memory");
        return NULL;
    }
    
    words[ind + 1] = NULL;

    return words;
}

void logout()
{
    puts("logout");
    exit(EXIT_SUCCESS);
}

void systemCall(char **arguments)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork err");
        return;
    }

    if (pid == 0)
    {

        if (execvp(arguments[0], arguments) == -1)
        {
            exit(EXIT_FAILURE);
        }
    }
}
void myPipe(char **argv1, char **argv2)
{

    int fd[2];

    if (fork() == 0)
    {
        pipe(fd);
        if (fork() == 0)
        {

            close(STDOUT_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(argv1[0], argv1);
        }

        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
        execvp(argv2[0], argv2);
        
    }
}

