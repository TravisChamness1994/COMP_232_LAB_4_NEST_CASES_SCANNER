#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    NO_TOKEN_TYPE, //when whitespace, tab, \n
    INVALID_TOKEN, // A token representing characters not in our language
    REPEAT_TOKEN, // A token that is the same as the previous
    PRINT_TOKEN, // Print token Keyword
    IDENT_TOKEN, // Identifiers token
    INT_TOKEN, // Integer token
    FLOAT_TOKEN, // Float token
    ASSIGNMENT_TOKEN, //Assignment token
    LPAREN_TOKEN, // Left parenthesis token
    RPAREN_TOKEN, // Right parenthesis token
    ADD_OP_TOKEN, // Add operator token (+|-)
    MULT_OP_TOKEN, // Multiplication token (*|/|%0)
    SEMICOLON_TOKEN, // Semicolon token
    EOF_TOKEN //End Of File token
} TOKEN_TYPE;

typedef union
{
    long integer; // Token_Value for Integer
    double floating_point; // Token_Value for floating point numbers
    char *string; // Token_value for strings
    char op; //Token_value of AddOps or MultOps
} TOKEN_VALUE;

typedef struct token
{
    TOKEN_TYPE type; //Token member Type
    TOKEN_VALUE val; //Token member Value
} TOKEN;

typedef enum
{
    START_STATE = 0,
    ID_OR_KEYWORD_STATE,
    INT_STATE,
    FLOAT_STATE
} STATE; // States are where we are in the scanning

TOKEN *scanner();

void freeToken(TOKEN **);

void printToken(TOKEN **);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

#endif