#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 32

//
// clean up the referenced token (if it isn't NULL).
//
void freeToken(TOKEN **token)
{
    /*
     * TODO
     * free the referenced TOKEN *, and any contained data
     * which requires freeing.
     *
     * Then, set the referenced TOKEN * to NULL
     */
}

bool updateKeywordOrId(TOKEN *token, char *str)
{
    /*
     * TODO
     * Check if the collected token is a keyword by comparing its string
     * value to the string values of the print and repeat keywords.
     *
     * If the token is a keyword, change its type to the corresponding
     * TOKEN_TYPE and return true.
     *
     * If the token is not a keyword, change its type to the token type
     * for identifiers, allocate space for its string value and copy the
     * string value into the token, then return false.
     */
}

void printToken (TOKEN **token)
{
    /*
     * TODO
     * EX: <IDENT, firstvar>
     * EX: <INT, 123>
     * EX: <SEMICOLON>
     * Looks like a switch statement may be needed for the printToken Method
     * Print the referenced token in a readable format.
     * Displayed information should include the TOKEN_TYPE,
     * and also the token's value if applicable.
     */
}
//MAKE SURE TO HAVE ALL BREAK STATEMENTS TO CLOSE A SWITCH STATEMENT
TOKEN *scanner()
{
    // buffer to store a token's contained characters while it is being tokenized
    size_t bufferSize = BUFFER_SIZE;
    char *stringValue = calloc(sizeof(char), bufferSize);
    int stringValueIndex = 0;

    // allocate space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));

    // initialize the token type to invalid
    token->type = NO_TOKEN_TYPE;

    // set state machine to starting state
    STATE state = START_STATE;

    char currentChar = '\0';

    while (currentChar != EOF && token->type == NO_TOKEN_TYPE)
    {
        currentChar = (char) getchar();
        /*
         * TODO
         * Given the current state of the state machine
         * and the next character, update the state machine
         * (and the string value of the token being built,
         * if applicable).
         */

        // if the buffer is full, double its size
        if (stringValueIndex >= bufferSize-1)
        {
            bufferSize *= 2;
            char *temp = calloc(sizeof(char), bufferSize);
            strcpy(temp, stringValue);
            free(stringValue);
            stringValue = temp;
        }
    }

    free(stringValue);
    return token;
}

