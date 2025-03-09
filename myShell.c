#include "myShell.h"
#include "myFunctionsShell.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{

    wellcome();
    while (1)
    {
        int isPipe1 = 0;
        int isPipe2 = 0;
        getLocation();

        char *input = inputFromUser();

        char **arguments = splitArguments(input);

        isPipe1 = getPipe(arguments);

        if(isPipe1)
            isPipe2 = getPipe(arguments+isPipe1+1);

        if(isPipe2)
            isPipe2 = isPipe2 + isPipe1+1;




        if (strcmp(input, "exit") == 0)
        {
            logout();
        }
        else if (strcmp(input, "cd") == 0)
        {
            cd(arguments);
        }
        else if (strcmp(input, "cp") == 0)
        {
            cp(arguments);
        }
        else if (strcmp(input, "delete") == 0)
        {
            del(arguments);
        }
        else if (strcmp(input, "dir") == 0)
        {
            puts("Impl");
        }
        else if (strcmp(input, "move") == 0)
        {
            move(arguments);
        }
        else if (strcmp(input, "echo") == 0)
        {
            echoFile(arguments);
        }
        else if (isPipe1)
        {
            if(!isPipe2)
                myPipe(arguments,arguments+isPipe1+1,NULL);
            else
                myPipe(arguments,arguments+isPipe1+1,arguments+isPipe2+1);
        }
        else
        {
            systemCall(arguments);
            wait(NULL);
        }

        free(arguments);
        free(input);
    }

    return 0;
}


void wellcome() {
    const char *BRIGHT_RED = "\033[91m";
    const char *RESET = "\033[0m";

    FILE *file = fopen("ascii-art.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("%s", BRIGHT_RED);

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("%s", RESET);

    fclose(file);
}
