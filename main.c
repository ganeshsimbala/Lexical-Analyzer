#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "error.h"

Tokens token;
ERRORINFO errInfo;
SemicolonError semicolonerr[10000];

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    // Initialize lexer
    if (initializeLexer(argv[1], &token))
    {
        printf("Failed to open the file: %s\n", argv[1]);
        return 1;
    }

    printf("Opened the source file: %s\n", argv[1]);

    int line_no = 0, size = 0, semi_col_size = 0;

    // Initialize ideal state
    errInfo.recent = 0;
    errInfo.in_double_quote = 0;
    errInfo.in_single_quote = 0;

    // Line-by-line reading
    while ((fgets(errInfo.stream, sizeof(errInfo.stream), token.fptr_src_file)) != NULL)
    {
        line_no++;
        char *ptr = errInfo.stream;
        while (isspace(*ptr))
            ptr++;
        if (*ptr == '\0')
            continue;
        error_detection(errInfo.stream, &errInfo, line_no, &size);

        check_semicolon(errInfo.stream, semicolonerr, line_no, &semi_col_size);
    }

    // Report unmatched brackets remaining in stack
    for (int i = 0; i < errInfo.recent; i++)
    {
        errInfo.un_matchedLine[size] = errInfo.line_num[i];
        errInfo.misMatched[size] = errInfo.symbols[i];
        errInfo.expected[size] = errInfo.expected[i];
        size++;
    }

    // Report unmatched quotes
    if (errInfo.in_double_quote)
    {
        errInfo.un_matchedLine[size] = line_no;
        errInfo.misMatched[size] = '"';
        errInfo.expected[size] = '"';
        size++;
    }

    if (errInfo.in_single_quote)
    {
        errInfo.un_matchedLine[size] = line_no;
        errInfo.misMatched[size] = '\'';
        errInfo.expected[size] = '\'';
        size++;
    }

    // Final error summary output
    if (size > 0 || semi_col_size > 0)
    {
        printf("\n---------------------Error Summary:--------------------\n\n");

        if (size)
        {
            for (int i = 0; i < size; i++)
            {
                printf("%s: %d: ERROR: unmatched symbol '%c' -- expected --'%c'\n",
                       argv[1],
                       errInfo.un_matchedLine[i],
                       errInfo.misMatched[i],
                       errInfo.expected[i]);
            }
        }
        
        if (semi_col_size)
        {
            for (int i = 0; i < semi_col_size; i++)
            {
                printf("%s: %d: ERROR: ';' missing at end of statement:\n  %s",
                       argv[1],
                       semicolonerr[i].line_no,
                       semicolonerr[i].message);
            }
        }

        fclose(token.fptr_src_file);
        return 1;
    }

    // Reset for tokenization
    rewind(token.fptr_src_file);

    // Token partitioning
    partition_of_tokens(&token);

    // Token printing
    TOKENTYPE type;
    const char *typeNames[] = {
        "KEYWORDS", "OPERATORS", "SYMBOLS", "DATATYPES",
        "CONSTANTS", "IDENTIFIERS", "PREPROCESSOR", "MULTICHAROPERATOR", "STRINGLITERAL", "UNKNOWN"};

    while ((type = getNextToken(&token)) != UNKNOWN)
    {
        printf("Token: %-20s Type: %s\n", token.lexem, typeNames[type]);
    }

    fclose(token.fptr_src_file);
    return 0;
}
