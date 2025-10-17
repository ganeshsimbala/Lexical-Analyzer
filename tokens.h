#ifndef TOKENS_H
#define TOKENS_H

#include <stdio.h>

#define MAX_KEYWORDS 24
#define MAX_OPERATORS 13
#define MAX_SYMBOLS 10
#define MAX_TYPES 9
#define MAX_DIRECTIVES 13
#define MAX_MULTICHARACTER 15
#define LEXEM_MAX_SIZE 100

typedef enum
{
    KEYWORDS,
    OPERATORS,
    SYMBOLS,
    DATATYPES,
    CONSTANTS,
    IDENTIFIERS,
    PREPROCESSOR,
    MULTICHAROPERATOR,
    STRINGLITERAL,
    UNKNOWN 
} TOKENTYPE;

typedef struct _Tokens
{
    char *key_words[MAX_KEYWORDS];
    char *operators[MAX_OPERATORS];
    char *symbols[MAX_SYMBOLS];
    char *dataTypes[MAX_TYPES];
    char *directives[MAX_DIRECTIVES];
    char *multi_characterOperator[MAX_MULTICHARACTER];

    FILE *fptr_src_file;
    char *src_file_name; 

    char lexem[LEXEM_MAX_SIZE];
    int semicolon_count;
    int single_quotes;  

    TOKENTYPE tokentype;
} Tokens;

// Function declarations
void partition_of_tokens(Tokens *token);
int initializeLexer(const char *filename, Tokens *token);

TOKENTYPE getNextToken(Tokens *token);
TOKENTYPE getTokenTypeName(const char *lexem, Tokens *token);

int isEscape_char(char ch);
int isKeyword(const char *str, Tokens *token);
int isOperator(const char *str, Tokens *token);
int isConstant(const char *str);
int isIdentifier(const char *str, Tokens *token);
int isDatatype(const char *str, Tokens *token);
int isPreprocessor(const char *str, Tokens *token);
int isSymbols(const char *str, Tokens *token);
int isMulticharOperator(const char *str,Tokens *token);
#endif
