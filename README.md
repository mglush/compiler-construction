# x86 Code Generation
#### By Michael Glushchenko.

Project aspects:
  - Generates x86 assembly code based on an input program in a simplified programming language.
  - The generated assembly code is stored in code.s and linked to a C entry point via the tester.c driver.
  - After linking, gcc is used to compile the generated assembly code.
  - The result of compilation should be the output of the main method of the Main class within the input program.
