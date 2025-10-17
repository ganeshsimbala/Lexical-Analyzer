#ifndef ERROR_H
#define ERROR_H

typedef enum
{
    isValid,
    notValid,
} Status;

typedef struct
{
    char stream[10000];
    int line_num[10000];
    char symbols[10000];
    char misMatched[10000];
    char expected[10000];
    int un_matchedLine[10000];
    int recent;
    int in_double_quote;
    int in_single_quote;
} ERRORINFO;

typedef struct
{
    int line_no;
    char message[10000];
} SemicolonError;

void error_detection(const char *line, ERRORINFO *errInfo, int, int *);
void check_semicolon(const char *line, SemicolonError *semicolonerr, int, int *);
#endif