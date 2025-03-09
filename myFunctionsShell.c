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
void myPipe(char **argv1, char **argv2, char **argv3)
{

    int fd1[2], fd2[2];

    if (pipe(fd1) == -1) {
        perror("pipe1 failed");
        exit(1);
    }

    if (argv3 != NULL) {  // create second pipe if argv3 isnt null
        if (pipe(fd2) == -1) {
            perror("pipe2 failed");
            exit(1);
        }
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork1 failed");
        exit(1);
    }
    if (pid1 == 0) {
        close(fd1[0]);  //close fd1 read
        dup2(fd1[1], STDOUT_FILENO);  //redirect output to fd1[1]
        close(fd1[1]);  //close original write

        execvp(argv1[0], argv1);
        perror("execvp1 failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork2 failed");
        exit(1);
    }
    if (pid2 == 0) {
        close(fd1[1]);  //close write of fd1
        dup2(fd1[0], STDIN_FILENO);  //read from fd1 [0]
        close(fd1[0]);  // close the original read

        if (argv3 != NULL) { // if i have second pipe
            close(fd2[0]);  // close fd2[0]
            dup2(fd2[1], STDOUT_FILENO);  //redirect the output to fd2[1]
            close(fd2[1]);  //close original write
        }

        execvp(argv2[0], argv2);
        perror("execvp2 failed");
        exit(1);
    }

    //done with first pipe
    close(fd1[0]);
    close(fd1[1]);

    if (argv3 != NULL) { // if second pipe
        pid_t pid3 = fork();
        if (pid3 < 0) {
            perror("fork3 failed");
            exit(1);
        }
        if (pid3 == 0) {
            close(fd2[1]);  //close write of the pipe
            dup2(fd2[0], STDIN_FILENO);  //read from the pipe
            close(fd2[0]);  // close original read

            execvp(argv3[0], argv3);
            perror("execvp3 failed");
            exit(1);
        }
        //close the second pipe
        close(fd2[0]);
        close(fd2[1]);
    }

    
    wait(NULL);
    wait(NULL);
    if (argv3 != NULL) {
        wait(NULL);
    }
}

int getPipe(char **arguments){
    int i = 0;
    while(arguments[i]  != NULL){
        if(arguments[i][0] == '|'){
            arguments[i] = NULL;
            return i;
        }
        i = i+1;
    }
    return 0;
}


void del(char **arguments)
{
    int size = 0;
    while (arguments[size] != NULL) {
        size++;
    }

    if(size <2){
        perror("delete needs a path");
    }
    else if(size > 2){
        perror("too many arguments");
    }

    if (remove(arguments[1]) == 0) {
        printf("File deleted successfully.\n");

    } else {
        printf("Error: Unable to delete the file.\n");
    }

}

void move(char **arguments){
    int size = 0;
    while (arguments[size] != NULL) {
        size++;
    }

    if(size != 3){
        perror("move needs a file source path and destination path");
    }

    int status = rename(arguments[1], arguments[2]);

    if(status !=0 ){
        perror("coulndt move file");
    };
}

void echoFile(char **arguments) {
    int size = 0;

    while (arguments[size] != NULL) {
        size++;
    }
    if(size <= 1){
        perror("too less arguments");
        return;
    }

    if (size == 2) {
        puts(arguments[1]);
        return;
    }


    if (size != 4) {
        perror("Incorrect number of arguments echoppend needs to be used like <string> >or>> <destination to append/write to>");
        return;
    }

    FILE *destFile;
    char *input = arguments[1];

    if(strcmp(arguments[2],">") == 0){
        destFile = fopen(arguments[3], "w");
    }
    else if (strcmp(arguments[2],">>") == 0){
        destFile = fopen(arguments[3], "a");
    }
    else{
        perror("expected > or >> after string but didnt get it");
        return;
    }

    if (destFile == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(destFile, "%s", input);

    fclose(destFile);
}
