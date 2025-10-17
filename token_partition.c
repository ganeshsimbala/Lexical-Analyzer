#include <stdio.h>
#include "tokens.h"

// Loading All predefined tokens into Structure
void partition_of_tokens(Tokens *token)
{

    char *keywords[] = {
        "while", "if", "else", "else if", "for", "do", "switch", "case",
        "const", "volatile", "return", "extern", "static", "auto", "struct",
        "union", "typedef", "register", "default", "break", "continue", "printf", "scanf", "main"};
    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        token->key_words[i] = keywords[i];
    }

    char *operators[] = {
        "+", "-", "*", "/", "%", "!", "~", "^", "&", "|", ">", "<","="};
    for (int i = 0; i < MAX_OPERATORS; i++)
    {
        token->operators[i] = operators[i];
    }

    char *symbols[] = {"(", ")", "{", "}", "[", "]", ",", ";", ".",":"};
    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        token->symbols[i] = symbols[i];
    }

    char *types[] = {"int", "char", "short", "long", "signed", "unsigned", "float", "double", "void"};
    for (int i = 0; i < MAX_TYPES; i++)
    {
        token->dataTypes[i] = types[i];
    }

    char *directives[] = {"#include <stdio.h>", "#define", "ifndef", "#ifdef", "#if", "#endif", "#pragma", "#include <string.h>", "#include <stdlib.h>", "#include <type.h>", "#elif", "#else", "#undef"};
    for (int i = 0; i < MAX_DIRECTIVES; i++)
    {
        token->directives[i] = directives[i];
    }
    char *multicharacter[] = {"==", "!=", ">=", "<=", "&&", "||", "++", "--", "+=", "-=", "%=", "*=","<<",">>","/="};
    for (int i = 0; i < MAX_MULTICHARACTER; i++)
    {
        token->multi_characterOperator[i] = multicharacter[i];
    }
    return;
}
