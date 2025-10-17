
// --- UPDATED getNextToken ---
#include <stdio.h>
#include "tokens.h"
#include <ctype.h>

TOKENTYPE getNextToken(Tokens *token)
{
    char ch;
    int index = 0;

    while ((ch = fgetc(token->fptr_src_file)) != EOF)
    {
        if (isEscape_char(ch) || isspace(ch))
            continue;

        // Handle Comments
        if (ch == '/')
        {
            int next = fgetc(token->fptr_src_file);

            // Single-line comment
            if (next == '/')
            {
                while ((ch = fgetc(token->fptr_src_file)) != EOF && ch != '\n');
                continue;
            }
            // Multi-line comment
            else if (next == '*')
            {
                char prev = 0;
                while ((ch = fgetc(token->fptr_src_file)) != EOF)
                {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }
            else
            {
                fseek(token->fptr_src_file, -1, SEEK_CUR);
            }
        }

        // Preprocessor
        if (ch == '#')
        {
            token->lexem[index++] = ch;
            while ((ch = fgetc(token->fptr_src_file)) != EOF && ch != '\n')
            {
                if (ch != '\r')
                    token->lexem[index++] = ch;
            }
            token->lexem[index] = '\0';
            return getTokenTypeName(token->lexem, token);
        }

        // Identifiers / Keywords
        if (ch == '_' || isalpha(ch))
        {
            token->lexem[index++] = ch;
            while ((ch = fgetc(token->fptr_src_file)) != EOF && (isalnum(ch) || ch == '_'))
                token->lexem[index++] = ch;
            if (!isspace(ch))
                fseek(token->fptr_src_file, -1, SEEK_CUR);
            token->lexem[index] = '\0';
            return getTokenTypeName(token->lexem, token);
        }

        // String Literals with escape handling
        if (ch == '"')
        {
            token->lexem[index++] = ch;
            while ((ch = fgetc(token->fptr_src_file)) != EOF)
            {
                token->lexem[index++] = ch;
                if (ch == '\\')
                {
                    token->lexem[index++] = fgetc(token->fptr_src_file);
                }
                else if (ch == '"')
                {
                    break;
                }
            }
            token->lexem[index] = '\0';
            return STRINGLITERAL;
        }

        // Character Literals
        if (ch == '\'')
        {
            token->lexem[index++] = ch;
            while ((ch = fgetc(token->fptr_src_file)) != EOF)
            {
                token->lexem[index++] = ch;
                if (ch == '\\')
                {
                    token->lexem[index++] = fgetc(token->fptr_src_file);
                }
                else if (ch == '\'')
                {
                    break;
                }
            }
            token->lexem[index] = '\0';
            return CONSTANTS;
        }

        // Multi-character Operators
        if (ispunct(ch))
        {
            token->lexem[index++] = ch;
            int next = fgetc(token->fptr_src_file);
            if (ispunct(next))
            {
                token->lexem[index++] = next;
                token->lexem[index] = '\0';
                if (isMulticharOperator(token->lexem, token))
                    return MULTICHAROPERATOR;
                else
                {
                    fseek(token->fptr_src_file, -1, SEEK_CUR);
                    token->lexem[index - 1] = '\0';
                    return getTokenTypeName(token->lexem, token);
                }
            }
            else
            {
                if (!isspace(next))
                    fseek(token->fptr_src_file, -1, SEEK_CUR);
                token->lexem[index] = '\0';
                return getTokenTypeName(token->lexem, token);
            }
        }

        // Hexadecimal Constants
        if (ch == '0')
        {
            token->lexem[index++] = ch;
            int next = fgetc(token->fptr_src_file);
            if (next == 'x' || next == 'X')
            {
                token->lexem[index++] = next;
                while ((ch = fgetc(token->fptr_src_file)) != EOF && isxdigit(ch))
                    token->lexem[index++] = ch;
                fseek(token->fptr_src_file, -1, SEEK_CUR);
                token->lexem[index] = '\0';
                return CONSTANTS;
            }
            else
            {
                fseek(token->fptr_src_file, -1, SEEK_CUR);
                token->lexem[index] = '\0';
                return CONSTANTS;
            }
        }

        // Numbers (integer or float)
        if (isdigit(ch))
        {
            int isFloat = 0;
            token->lexem[index++] = ch;
            while ((ch = fgetc(token->fptr_src_file)) != EOF && (isdigit(ch) || ch == '.'))
            {
                if (ch == '.')
                {
                    if (isFloat)
                        break;
                    isFloat = 1;
                }
                token->lexem[index++] = ch;
            }
            if (!isspace(ch) && ch != ';' && ch != ',')
                fseek(token->fptr_src_file, -1, SEEK_CUR);
            token->lexem[index] = '\0';
            return CONSTANTS;
        }

        // + or - before numbers
        if (ch == '+' || ch == '-')
        {
            int next = fgetc(token->fptr_src_file);
            if (isdigit(next))
            {
                token->lexem[index++] = ch;
                ch = next;
                while (isdigit(ch) || ch == '.')
                {
                    token->lexem[index++] = ch;
                    ch = fgetc(token->fptr_src_file);
                }
                if (!isspace(ch) && ch != ';' && ch != ',')
                    fseek(token->fptr_src_file, -1, SEEK_CUR);
                token->lexem[index] = '\0';
                return CONSTANTS;
            }
            else
            {
                fseek(token->fptr_src_file, -1, SEEK_CUR);
                token->lexem[index++] = ch;
                token->lexem[index] = '\0';
                return getTokenTypeName(token->lexem, token);
            }
        }
    }

    token->lexem[0] = '\0';
    return UNKNOWN;
}
