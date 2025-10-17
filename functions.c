#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"


//OPen the File
int initializeLexer(const char *filename, Tokens *token)
{
    token->fptr_src_file = fopen(filename, "r");
    if (token->fptr_src_file == NULL)
        return 1;
    else
        return 0;
}

//check for Escape characters
int isEscape_char(char ch)
{
    if (ch == '\n' || ch == '\t')
        return 1;
    else
        return 0;
}

//To know which type of token is produced 
TOKENTYPE getTokenTypeName(const char *lexem, Tokens *token)
{
    if (isKeyword(lexem, token))
        return KEYWORDS;
    else if (isDatatype(lexem, token))
        return DATATYPES;
    else if (isPreprocessor(lexem, token))
        return PREPROCESSOR;
    else if (isOperator(lexem, token))
        return OPERATORS;
    else if (isSymbols(lexem, token))
        return SYMBOLS;
    else if (isdigit(lexem[0]) || (lexem[0] == '.' && isdigit(lexem[1])))
        return CONSTANTS;
    else if(isMulticharOperator(lexem,token))
        return MULTICHAROPERATOR;
    else
        return IDENTIFIERS;
}

//Check for keyword
int isKeyword(const char *str, Tokens *token)
{
    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        if (strcmp(str, token->key_words[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check for Operator
int isOperator(const char *str, Tokens *token)
{
    for (int i = 0; i < MAX_OPERATORS; i++)
    {
        if (strcmp(str, token->operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check for symbols
int isSymbols(const char *str, Tokens *token)
{
    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (strcmp(str, token->symbols[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check for is a dataype
int isDatatype(const char *str, Tokens *token)
{
    for (int i = 0; i < MAX_TYPES; i++)
    {
        if (strcmp(str, token->dataTypes[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

//check for preprocessor direcivees
int isPreprocessor(const char *str, Tokens *token)
{
    for (int i = 0; i < MAX_DIRECTIVES; i++)
    {
        if (strcmp(str, token->directives[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int isMulticharOperator(const char *str,Tokens *token)
{
    for(int i=0;i<MAX_MULTICHARACTER;i++)
    {
        if(strcmp(str,token->multi_characterOperator[i])==0)
            return 1;
    }
    return 0;
}
