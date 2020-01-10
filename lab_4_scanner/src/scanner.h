#ifndef __SCANNER_H
#define __SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    NO_TOKEN_TYPE,
    INVALID_TOKEN,
    REPEAT_TOKEN,
    PRINT_TOKEN,
    IDENT_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    ASSIGNMENT_TOKEN,
    LPAREN_TOKEN,
    RPAREN_TOKEN,
    ADD_OP_TOKEN,
    MULT_OP_TOKEN,
    SEMICOLON_TOKEN,
    EOF_TOKEN
} TOKEN_TYPE;

typedef union
{
    long integer;
    double floating_point;
    char *string;
    char op;
} TOKEN_VALUE;

typedef struct token
{
    TOKEN_TYPE type;
    TOKEN_VALUE val;
} TOKEN;

typedef enum
{
    START_STATE = 0,
    ID_OR_KEYWORD_STATE,
    INT_STATE,
    FLOAT_STATE
} STATE;

TOKEN *scanner();

void freeToken(TOKEN **);

void printToken(TOKEN **);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

#endif