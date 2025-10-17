#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "error.h"

#define MAX_STACK 10000

// Utility: check if quote is escaped
bool is_quote_escaped(const char *line, int index) {
    int backslashes = 0;
    index--;
    while (index >= 0 && line[index--] == '\\')
        backslashes++;
    return (backslashes % 2) == 1;
}

// Main error detection logic
void error_detection(const char *line, ERRORINFO *errInfo, int line_no, int *size)
{
    static char stack[MAX_STACK];
    static int line_stack[MAX_STACK];
    static char expected_stack[MAX_STACK];
    static int top = 0;

    int i = 0;
    char ch;

    while ((ch = line[i]) != '\0')
    {
        // Toggle quote states
        if (ch == '\"' && !errInfo->in_single_quote && !is_quote_escaped(line, i))
        {
            errInfo->in_double_quote = !errInfo->in_double_quote;
        }
        else if (ch == '\'' && !errInfo->in_double_quote && !is_quote_escaped(line, i))
        {
            errInfo->in_single_quote = !errInfo->in_single_quote;
        }

        // Bracket tracking only outside of quotes
        else if (!errInfo->in_double_quote && !errInfo->in_single_quote)
        {
            if (ch == '{' || ch == '(' || ch == '[')
            {
                stack[top] = ch;
                line_stack[top] = line_no;
                expected_stack[top] = (ch == '{') ? '}' : (ch == '(') ? ')' : ']';
                top++;
            }
            else if (ch == '}' || ch == ')' || ch == ']')
            {
                char match = (ch == '}') ? '{' : (ch == ')') ? '(' : '[';

                if (top > 0 && stack[top - 1] == match)
                {
                    // matched
                    top--; 
                }
                else
                {
                    errInfo->un_matchedLine[*size] = line_no;
                    errInfo->misMatched[*size] = ch;
                    errInfo->expected[*size] = (top > 0) ? expected_stack[top - 1] : match;
                    (*size)++;
                }
            }
        }

        i++;
    }

    errInfo->recent = top;
}

// Semicolon detection logic
void check_semicolon(const char *line, SemicolonError *semicolonerr, int line_no, int *size)
{
    int i = 0;
    char buffer[1000];
    bool key_words = false, valid_symbols = false;

    while (isspace(line[i]))
        i++;
    strcpy(buffer, &line[i]);

    int len = strlen(buffer);
    while (len > 0 && isspace(buffer[len - 1]))
        len--;
    buffer[len] = '\0';

    if (strncmp(buffer, "if", 2) != 0 &&
        strncmp(buffer, "for", 3) != 0 &&
        strncmp(buffer, "do", 2) != 0 &&
        strncmp(buffer, "while", 5) != 0 &&
        strncmp(buffer, "else", 4) != 0 &&
        strncmp(buffer, "else if", 7) != 0 &&
        strncmp(buffer, "int main", 8) != 0 &&
        strncmp(buffer, "//", 2) != 0 &&
        strncmp(buffer, "/*", 2) != 0 &&
        strncmp(buffer, "typedef enum", 12) != 0 &&
        strncmp(buffer, "struct", 6) != 0 &&
        strncmp(buffer, "typedef struct", 14) != 0 &&
        strncmp(buffer, "enum", 5) != 0)
    {
        key_words = true;
    }

    if (buffer[len - 1] != ';' &&
        buffer[len - 1] != '{' &&
        buffer[len - 1] != '}' &&
        buffer[len - 1] != ')' &&
        buffer[0] != '{' &&
        buffer[0] != '#' &&
        buffer[0] != '\n' &&
        buffer[len - 1] != '&' &&
        buffer[len - 1] != '|' &&
        buffer[len - 1] != ',')
    {
        valid_symbols = true;
    }

    if (key_words && valid_symbols)
    {
        semicolonerr[*size].line_no = line_no;
        strcpy(semicolonerr[*size].message, line);
        (*size)++;
    }
}
