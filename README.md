# Stack-Based x86 Code Generation
#### By Michael Glushchenko for UCSB CS160 Spring 2022 (Transaltion of Programming Languages).

**README SUBMISSION**:
  - I couldn't really get the method of saving a returned value into %eax to work, so I went ahead and just pushed the result onto the stack every time.
  - The code looks slightly spaghetti-like, I believe I went about implementing parts of the program in the wrong order, so I got carried away fixing certain parts before others.
  - Did not know any x86 before this, so that was the main challenge, looking up how to do a proper division in x86, and looking up why the hell my 'not' operation isn't working.
  - 65.good.lang generates correct code, it just doesn't pass gradescope because the stack runs out of space because I didn't implement returning a value in %eax, I pushed everything onto the stack.
  - I ended up modifying the symbol table through visiting the classNode in typecheck.cpp and inserting superclass members into the variable table of a current class pre-order style.
  - helper functions at the top of code generation are used to look through the symbol table for the most part, but I deviated from using them throughout the code, which is probably what made this project that hard.
  - I did not submit a README for project 5, I emailed one to you. Letting you know here just in case you missed the email.

**Input**:
  - Program written in a small object-oriented programming language.

**Output**:
  - Translation of program to x86 assembly.
  - The assembly can be run with the following commands:
    ~~~
    ./lang < input_language > code.s
    gcc -m32 -o executable tester.c code.s
    ./executable
    ~~~

**Project aspects**:
  - Uses Flex scanner generator to consume input one token at a time and pass it on to the parser.
  - Uses Bison parser to parse the input program, bottom-up, and build an abstract syntax tree while doing so.
  - Uses typeChecker visitor pattern to build a symbol table for the input program.
  - The generated symbol table is used to typecheck the program for an extensive list of compile-time errors.
  - The symbol table is then used to generate x86 assembly code based on the input program, and store it in code.s.
  - The generated assembly code is linked to a C entry point via the tester.c driver, compiled and executed with gcc.

