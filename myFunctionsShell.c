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
    *(input + len + 1) = '\0';

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

void split(char* arr){

    int len = strlen(arr);
    int ind = 0;

    char** words = calloc(len+1, sizeof(char*));

    int stringMode = 0;

    words[0] = arr; 
    words[len] = NULL;
        

    for (int i = 0; i < len; i++) {
        if (arr[i] == '"') {
            stringMode = !stringMode;
        }

        if (arr[i] == ' ' && !stringMode) {
            arr[i] = '\0';
            words[++ind] = &arr[i + 1];
        }
    }

    if (stringMode) {
        puts("Error: Unclosed string detected");
    }
    else{
        for (int i = 0; i <= ind; i++) {
            puts(words[i]);
        }
    }

   
    
    free(words);
}