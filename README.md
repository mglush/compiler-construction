# x86 Code Generation
#### By Michael Glushchenko for UCSB CS160 Spring 2022 (Transaltion of Programming Languages).

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - Results of the print statements within the main method of the Main class of the input program.

Project aspects:
  - Uses Flex scanner generator to consume input one token at a time and pass it on to the parser.
  - Uses Bison parser to parse the input program, bottom-up, and build an abstract syntax tree while doing so.
  - Uses typeChecker visitor pattern to build a symbol table for the input program.
  - The generated symbol table is used to typecheck the program for an extensive list of compile-time errors.
  - The symbol table is then used to generate x86 assembly code based on the input program, and store it in code.s.
  - The generated assembly code is linked to a C entry point via the tester.c driver, and compiled with gcc.
