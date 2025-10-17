# Lexical Analyzer in C

## 📚 Project Overview

This project implements a **Lexical Analyzer**, the first phase of a compiler, using the C programming language.
It reads source code from a file, breaks it into **tokens** (keywords, identifiers, literals, operators, and symbols), and detects **lexical or syntax errors** such as unmatched brackets, quotes, or missing semicolons.

The project demonstrates **compiler fundamentals**, **string parsing**, and **state-based error detection**, making it an excellent learning tool for embedded systems and software development.

---

## ⚙️ Problem Statement

A compiler must process source code efficiently and detect errors before executing or translating it.
The challenge is to identify **valid tokens** while handling **nested structures**, **string literals**, and **edge cases** without external libraries.
This project addresses that by building a **custom lexical analyzer** that performs:

* Token recognition and classification
* Line-wise syntax error detection
* Error aggregation and reporting

---

## 🧁 Features

* **Tokenization:** Classifies code into identifiers, keywords, operators, constants, and delimiters
* **Error Detection:** Detects unmatched `()[]{}`, quotes `" "`, and missing semicolons
* **Error Reporting:** Aggregates and displays all syntax issues at the end
* **Modular Design:** Clear separation of tokenizer, error handler, and main logic
* **Scalable:** Can be extended for parsing and further compiler stages

---

## 🔧 Technical Details

* **Language:** C
* **Concepts Used:** File handling, string processing, arrays, pointers, and state machines
* **Input:** Source code text file (e.g., `input.c`)
* **Output:** List of tokens and a syntax error report
* **Platform:** Linux / Ubuntu (GCC or VS Code terminal)

---

## 📊 System Workflow

1. Read source code line by line
2. Identify tokens and classify them
3. Check for unmatched brackets, quotes, and missing semicolons
4. Collect errors in a structured format
5. Display tokens and report all errors at the end

---

## 🚀 How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/ganeshsimbala/Lexical-Analyzer.git
   ```
2. Navigate to the project directory:

   ```bash
   cd Lexical-Analyzer
   ```
3. Compile the code:

   ```bash
   gcc main.c -o lexer
   ```
4. Run the program:

   ```bash
   ./lexer
   ```
5. Enter or provide a source code file for analysis.

---

## 📊 Learning Outcomes

* Understanding lexical analysis and compiler design principles
* Practicing **string parsing, file handling, and error detection** in C
* Modular and scalable coding practices for larger projects

---

## 💡 Future Improvements

* Add support for **multi-line comments**
* Handle **preprocessor directives** (`#include`, `#define`)
* Extend to **parser stage** for complete compiler simulation

---

## 📚 File Structure

Lexical-Analyzer/
├── main.c
├── functions.c
├── error.h
├── token_partion.c
└── tokens.h
|___ analysis.c
|___ error_detection.c
|__ token_partition.c

---

## ⚖️ License

This project is open-source and available under the MIT License.
