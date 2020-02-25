#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* unsigned char */
typedef unsigned char byte;


int main(int argc, char** argv) {
    int input;
    byte buffer[128];
    int i = 0;

    //main input loop, continues until EOF
    while ((input = fgetc(stdin)) != EOF)
    {
        buffer[i] = (byte)input;
        if ((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z') || (input >= 0xC0))
        {
            printf("Char->%c\n", buffer[i]);
        }

    }

    printf("%d\n", input);
    return 0;
}
