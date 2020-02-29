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
    int count; // frequency
    byte uni_char[5]; // character
    int isUni; // flag whether or not character is unicode
} _uni_char;

/*
 * compare function for qsort
 * @param:left = left comparator
 * @param:right = right comparator
 * @return = value in which qsort will use to sort
 */
int compare(const void *left, const void *right)
{
    const _uni_char *a = (const _uni_char *) left;
    const _uni_char *b = (const _uni_char *) right;

    if (a->count > b->count)
        return -1;
    else if (a->count < b->count)
        return 1;
    else
        return &right - &left;
}

/*
 * determines if the character is unicode or ascii, and how long the unicode character is. It then stores the values into charArray
 * @param:charArray = array for storing characters
 * @param:uniqueChars = amount of unique characters in the charArray
 * @param:input = input bit from fgetc
 * @param:file = file read from
 * @param:uniSize = size of the charater in bytes
 */
void storeChar(_uni_char *charArray, int *uniqueChars, int *input, /*FILE *file,*/ int uniSize)
{
    int isDuplicate = FALSE; // flag for duplication
    byte inputChar[5] = {0}; // array to hold a full length unicode char
    inputChar[0] = (byte)*input; // storing first byte

    //stores each byte into the array
    for (int i = 1; i < uniSize; ++i)
    {
        *input = fgetc(stdin);
        inputChar[i] = (byte)*input;
    }

    //no characters stored yet
    if (*uniqueChars == 0)
    {
        memset(charArray[0].uni_char, 0, sizeof(charArray[0].uni_char));
        strncpy(charArray[0].uni_char, inputChar, uniSize); //store the contents of the inputChar into the charArray
        charArray[0].count = 1;

        //unicode character
        if (uniSize > 1)
            charArray[0].isUni = TRUE;
        else
            charArray[0].isUni = FALSE;

        ++*uniqueChars;
    }
    else
    {
        //loop to compare character to find duplicates
        for (int i = 0; i < *uniqueChars; ++i)
        {
            //unicode character
            if (charArray[i].isUni == TRUE)
            {
                if (strcmp(inputChar, charArray[i].uni_char) == 0)
                {
                    ++charArray[i].count;
                    isDuplicate = TRUE;
                    break;
                }
            }
            //ascii
            else
            {
                if ((byte)*input == *charArray[i].uni_char)
                {
                    ++charArray[i].count;
                    isDuplicate = TRUE;
                    break;
                }
            }
        }
        // new character
        if (isDuplicate != TRUE)
        {
            memset(charArray[*uniqueChars].uni_char, 0, sizeof(charArray[0].uni_char));
            strncpy(charArray[*uniqueChars].uni_char, inputChar, uniSize);
            charArray[*uniqueChars].count = 1;

            if (uniSize > 1)
                charArray[*uniqueChars].isUni = TRUE;
            else
                charArray[*uniqueChars].isUni = FALSE;

            ++*uniqueChars;
        }
    }
}

/*
 * reads in a file of unicode/ascii and displays the frequency of the characters in descending order
 */
int main(int argc, char** argv) {
    int input; // var used for reading and storing byte
    int arraySize = 50; // base size of the array
    _uni_char *charArray; // array of characters
    int uniqueChars = 0; // amount of unique characters
    //FILE * file = fopen("test_uni.txt", "r"); // file for testing

    charArray = malloc(arraySize * sizeof(_uni_char)); // allocating room for the characters

    //main input loop, continues until EOF
    while (((input = fgetc(stdin)) != EOF))
    {
        //increases the size of the mem allocated by 50% if it gets close to filling up
        if (arraySize - uniqueChars == 1)
        {
            arraySize += (int)(arraySize*0.5);
            charArray = realloc(charArray, (arraySize * sizeof(_uni_char)));
        }
        //1111 0xxx (4 bytes of unicode)
        if (input >= 0xF0 && input <= 0xF7)
        {
            storeChar(charArray, &uniqueChars, &input, /*file,*/ 4);
        }
        //1110 xxxx (3 bytes of unicode)
        else if (input >= 0xE0 && input <= 0xEF)
        {
            storeChar(charArray, &uniqueChars, &input, /*file,*/ 3);
        }
        // 110x xxxx (2 bytes of unicode)
        else if (input >= 0xC0 && input <= 0xDF)
        {
            storeChar(charArray, &uniqueChars, &input, /*file,*/ 2);
        }
        //other bytes
        else
        {
            storeChar(charArray, &uniqueChars, &input, /*file,*/ 1);
        }
    }
    //fclose(file); // close the file

    qsort(charArray, uniqueChars, sizeof(_uni_char), compare); // sort the characters

    //prints the contents of the charArray
    for (int i = 0; i < uniqueChars; ++i)
    {
        //not unicode
        if (charArray[i].isUni == FALSE)
        {
            if (*charArray[i].uni_char == '\n' || *charArray[i].uni_char == '\r')
            {
                continue;
            }
            else
            {
                printf("%c->%d\n", *charArray[i].uni_char, charArray[i].count);
            }
        }
        //unicode
        else
        {
            if (*charArray[i].uni_char == '\n' || *charArray[i].uni_char == '\r')
            {
                continue;
            }
            else
            {
                printf("%s->%d\n", charArray[i].uni_char, charArray[i].count);
            }
        }
    }
    return 0;
}
