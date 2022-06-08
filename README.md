# Compiler Implementation in C++.
#### By Michael Glushchenko for UCSB CS160 Spring 2022 (Transaltion of Programming Languages).

## Table of Contents
* [Purpose](https://github.com/mglush/compiler-construction/blob/main/README.md#purpose)
* [How To Run](https://github.com/mglush/compiler-construction/blob/main/README.md#how-to-run)
* [Programming Language Description](https://github.com/mglush/compiler-construction/blob/main/README.md#programming-language-description)
* [Project 1: Bottom-up Parser Generator](https://github.com/mglush/compiler-construction/blob/main/README.md#project-1-bottom-up-parser-generator)
* [Project 2: Abstract Syntax Tree Builder](https://github.com/mglush/compiler-construction/blob/main/README.md#project-2-abstract-syntax-tree-builder)
* [Project 3: Symbol Table & Type Checker](https://github.com/mglush/compiler-construction/blob/main/README.md#project-3-symbol-table-type-checker)
* [Project 4: Stack-Based x86 Code Generation](https://github.com/mglush/compiler-construction/blob/main/README.md#project-4-stack-based-x86-code-generation)

## Purpose
The [compiler construction repository](https://github.com/mglush/compiler-construction/blob/main/README.md) contains all projects that aided me in learning about the compiler-building process and in actually implementing a compiler that works on a small, object-oriented prorgamming language.

## How To Run
~~~
make clean && make                        # create the lang executable.
./lang < input_language_file > code.s     # run the executable on an input language,
                                          # and save the generated assembly to a file called code.s.
gcc -m32 -o executable tester.c code.s    # link the generated assembly to the tester.c driver.
./executable                              # execute the generated assembly.
~~~

## Programming Language Description
  - Language specification is in the *lang.def* file.
  - This language only supports integer, boolean, and object types.
  - Expressions within the language support the following operations:
    - +, -, *, /, and, or, not.
  - Function overloading is not allowed, but virtual functions are supported.
  - Inheritance is supported with the *extends* keyword.
  - Every program must have a "Main" class, and every "Main" class must have a "main" method.

## Project 1: Bottom-up Parser Generator
- Uses Flex scanner generator to consume input one token at a time and pass it on to the parser.
- Uses Bison parser to parse the input program, bottom-up.
- Performs no action during parsing (to be implemented in the next project).

**New Files Implemented**:
  - lexer.l
  - parser.y

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - If input is a valid program in our language, there is no output.
  - Otherwise, outputs the line number on which an scan/parse error occurs.

## Project 2: Abstract Syntax Tree Builder
- Chose AST as our Intermediate Code (IC) representation.
- Wrote rules for each action in the context-free grammar in parser.y to build the AST during the parsing process.

**Existing Files Modified**:
  - parser.y

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - Given no scanner/parser errors:
    - Outputs an abstract syntax tree of the input program.

## Project 3: Symbol Table & Type Checker
- Part 1: build a symbol table based on the AST generated during parsing.
  - Each program has one class table.
  - Each class table has a variable table for its members, and a method table for its methods.
  - Each method table contains a variable table for the parameters and local variables.
  - Each variable table contains name, type, and offset information of a given variable (to be used in code generation).
- Part 2: use the symbol table to typecheck the input program for the following errors:
  - Undefined Variable
  - Undefined Method
  - Undefined Class
  - Undefined Member
  - Not An Object
  - Expression Type Mismatch
  - Argument Number Mismatch
  - Argument Type Mismatch
  - While Predicate Type Mismatch - while_predicate_type_mismatch
  - Do While Predicate Type Mismatch
  - If-Else Predicate Type Mismatch
  - Assignment Type Mismatch
  - Return Type Mismatch
  - Constructor Returns Type (shouldn't return anything).
  - No "Main" Class
  - Main Class Has Members
  - No "main" Method in the Main Class
  - "main" Method has Incorrect Signature

**New Files Implenented**:
  - typecheck.cpp

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - Given no scanner or parser errors:
    - If input is a valid program in the language, outputs the symbol table of the input program.
    - Otherwise, outputs one of the type errors listed below.

## Project 4: Stack-Based x86 Code Generation
- Uses the symbol table to generate x86 assembly code by doing a walk on the abstract syntax tree.
- Runs on Linux, needs minor tweaks to work on Mac OS.
- Completes the compiler-building process; the last project in this repository.

**Existing Files Modified**:
  - typecheck.cpp
    - Modified to have every class include its superclass' member variables in its own variable table.

**New Files Implemented**:
  - codegeneration.cpp

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - Given no scanner/parser/type errors:
    - Translation of program to x86 assembly.
    - The assembly can be run with the following commands:
      ~~~
      ./lang < input_language > code.s          # save the generated assembly to a file called code.s.
      gcc -m32 -o executable tester.c code.s    # link the generated assembly to the tester.c driver.
      ./executable                              # execute the generated assembly.
      ~~~
