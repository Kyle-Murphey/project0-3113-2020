#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#define TRUE 1
#define FALSE 0

/* unsigned char */
typedef unsigned char byte;

/* structure for our unicode storage. Holds the character and the frequency */
typedef struct _uni_char
{
    int count;
    byte uni_char[5];
    int isUni;
} _uni_char;

void storeChar(_uni_char charArray[], int *arraySize, int *input, FILE *file, int uniSize)
{
    int isDuplicate = FALSE;
    byte inputChar[5] = {0};
    inputChar[0] = (byte)*input;

    for (int i = 1; i < uniSize; ++i)
    {
        *input = fgetc(file);
        inputChar[i] = (byte)*input;
    }

    if (*arraySize == 0)
    {
        memset(charArray[0].uni_char, 0, sizeof(charArray[0].uni_char));
        strncpy(charArray[0].uni_char, inputChar, uniSize);
        charArray[0].count = 1;
        charArray[0].isUni = TRUE;
        ++*arraySize;
    } else {
        for(int i = 0; i < *arraySize; ++i)
        {
            if (charArray[i].isUni == TRUE)
            {
                if (strcmp(inputChar, charArray[i].uni_char) == 0)
                {
                    ++charArray[i].count;
                    isDuplicate = TRUE;
                    break;
                }
            } else {
                if ((byte)*input == *charArray[i].uni_char)
                {
                    ++charArray[i].count;
                    isDuplicate = TRUE;
                    break;
                }
            }
        }
        if (isDuplicate != TRUE)
        {
            memset(charArray[*arraySize].uni_char, 0, sizeof(charArray[0].uni_char));
            strncpy(charArray[*arraySize].uni_char, inputChar, uniSize);
            charArray[*arraySize].count = 1;
            charArray[*arraySize].isUni = TRUE;
            ++*arraySize;
        }
    }
}

int main(int argc, char** argv) {
    int input;
    _uni_char charArray[128];
    int arraySize = 0;
    FILE * file = fopen("test_uni.txt", "r");

    //main input loop, continues until EOF
    while (((input = fgetc(file)) != EOF))
    {
        //1111 0xxx (4 bytes of unicode)
        if (input >= 0xF0 && input <= 0xF7)
        {
            storeChar(charArray, &arraySize, &input, file, 4);
        }
        //1110 xxxx (3 bytes of unicode)
        else if (input >= 0xE0 && input <= 0xEF)
        {
            storeChar(charArray, &arraySize, &input, file, 3);
        }
        // 110x xxxx (2 bytes of unicode)
        else if (input >= 0xC0 && input <= 0xDF)
        {
            storeChar(charArray, &arraySize, &input, file, 2);
        }
        //other bytes
        else {
            storeChar(charArray, &arraySize, &input, file, 1);
        }
    }
    fclose(file);

    // prints the contents of the charArray except the newline char
    for (int i = 0; i < arraySize; ++i)
    {
        if (charArray[i].isUni == FALSE)
        {
            if (*charArray[i].uni_char == '\n' || *charArray[i].uni_char == '\r')
            {
                continue;
            } else{
                printf("%c->%d\n", *charArray[i].uni_char, charArray[i].count);
            }
        } else {
            if (*charArray[i].uni_char == '\n' || *charArray[i].uni_char == '\r')
            {
                continue;
            } else{
                printf("%s->%d\n", charArray[i].uni_char, charArray[i].count);
            }
        }
    }
    return 0;
}
