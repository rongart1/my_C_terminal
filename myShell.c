#include "myShell.h"
#include "myFunctionsShell.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    
    wellcome();
    while(1){
        
        getLocation();

        char* input = inputFromUser();
        // puts(input);
        split(input);




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
