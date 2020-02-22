#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* separators for tokens/inputs */
const char SEPARATORS[] = " \t\n";

/* renaming unsigned char to byte */
typedef unsigned char byte;


int main() {
    byte buffer[128] = {0}; //buffer to store values in
    byte input[50]; //stores input from cl
    byte * args[4]; //stores arguments from input
    byte ** arg; //pointer to arguments

    //main input loop, continues until EOF
    while (fgets(input, 50, stdin))
    {
        //tokenizes input and stores in args array
        arg = args;
        *arg++ = strtok(input, SEPARATORS);
        while((*arg++ = strtok(NULL, SEPARATORS)));

        if(*args[0] == 'i')
        {
            printf("Yeet\n");
        } else
        {
            break;
        }
    }

    return 0;
}
