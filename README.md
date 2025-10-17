# C Lexical Analyzer with Error Detection

A simple and robust lexical analyzer built in C that performs tokenization and syntax error detection for C source files.  
It supports detection of:
- Keywords, operators, data types, and symbols
- Unmatched brackets `{}`, `[]`, `()`
- Unmatched string and character quotes
- Missing semicolons at the end of statements

## Features

-  Line-by-line parsing of C source files
-  Stateful quote tracking with escape character support
-  Bracket matching using a custom stack
-  Semicolon detection for structural correctness
-  Comment-safe (skips over `//` and `/* */`)
-  Robust against formatted or aligned code


## Project Structure

plaintext
.
├── main.c                  # Entry point: loads file, runs error + token logic
├── analysis.c             # Tokenization logic (getNextToken)
├── functions.c            # Helper functions (isKeyword, isOperator, etc.)
├── token_partition.c      # Initializes token tables (keywords, symbols, etc.)
├── Error_detection.c      # Bracket, quote, and semicolon error logic
├── tokens.h               # Token type definitions and token structure
├── error.h                # Error tracking structure
└── README.md              # You're reading it!
