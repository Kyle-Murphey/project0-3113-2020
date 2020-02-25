#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* unsigned char */
typedef unsigned char byte;

typedef struct _uni_char
{
    int count;
    const byte * uni_char;
} _uni_char;

int main(int argc, char** argv) {
    int input;
    byte buffer[128];
    _uni_char charArray[128];
    int i = 0;
    int arraySize = 0;

    //main input loop, continues until EOF
    while ((input = fgetc(stdin)) != EOF)
    {
        buffer[i] = (byte)input;

        charArray[i].uni_char = (byte*)input;
        ++charArray[i].count;
        ++arraySize;

        if ((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z') || (input >= 0xC0))
        {
            printf("Char->%c\n", buffer[i++]);
        }

    }

    printf("%d\n", input);
    for (int x = 0; x < arraySize; ++x)
    {
        printf("Count->%d\nChar->%c\n", charArray[x].count, *charArray[x].uni_char);
    }
    return 0;
}
