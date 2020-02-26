#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* unsigned char */
typedef unsigned char byte;

/* structure for our unicode storage. Holds the character and the frequency */
typedef struct _uni_char
{
    int count;
    byte * uni_char;
} _uni_char;

int main(int argc, char** argv) {
    int input;
    byte inputByte;
    _uni_char charArray[128];
    int arraySize = 0;
    int flag = FALSE;


    FILE * file = fopen("test_uni.txt", "r");
    //file = fopen("test", "r");

    //main input loop, continues until EOF
    while (((input = fgetc(file)) != EOF))
    {
        //exit char
        if (input == '$')
        {
            break;
        }

        inputByte = (byte)input;

        if (arraySize == 0)
        {
            //charArray[0].uni_char = &buffer[i];
            charArray[0].uni_char = malloc(sizeof(byte));
            *charArray[0].uni_char = inputByte;
            charArray[0].count = 1;
            ++arraySize;
        } else {
            for(int i = 0; i < arraySize; ++i)
            {
                if (inputByte == *charArray[i].uni_char)
                {
                    ++charArray[i].count;
                    flag = TRUE;
                    break;
                }
            }
            if (flag != TRUE)
            {
                charArray[arraySize].uni_char = malloc(sizeof(byte));
                *charArray[arraySize].uni_char = inputByte;
                charArray[arraySize].count = 1;
                ++arraySize;
            } else {
                flag = FALSE;
            }
        }

        //if ((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z') || (input >= 0xC0))
        //{

        //}
    }
    fclose(file);
    // prints the contents of the charArray except the newline char
    for (int i = 0; i < arraySize; ++i)
    {
        if (*charArray[i].uni_char == '\n')
        {
            continue;
        } else{
            printf("Count->%d : Char->%c\n", charArray[i].count, *charArray[i].uni_char);
        }
    }
    return 0;
}
