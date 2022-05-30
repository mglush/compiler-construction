#include "codegeneration.hpp"

int TAB_COUNTER = 0;                // keeps track of tabs to use when printing assembly code.
bool INDENT_ON = true;              // set to false if no indentation is wanted.
bool COMMENTS_ON = true;           // set to false if you don't want the generated assembly to generate comments.
int COMMENT_OFFSET_TABS = 20;       // change up or down to move assembly coes closer or further from the code.

// returns the appropriate space to indent the assembly.
std::string getIndent(int num_tabs) {
    std::string result = "";
    if (INDENT_ON) {
        while (--num_tabs > 0)
            result += "    ";
        return result;
    } else {
        return "    ";
    }
}

// helper function to find proper space to allocate for a new object.
int findObjectMemberSize(CodeGenerator* visitor, std::string class_name) {
    int result = 0;
    while (visitor->classTable->at(class_name)) {
        result += visitor->classTable->at(class_name).membersSize;
        class_name = visitor->classTable->at(class_name).superClassName;
    }
    return result;
}

// helper function to find the proper offset of a current class's variable/member.
int findVariableOffset(CodeGenerator* visitor, std::string class_name, std::string name) {
    int result = 0;
    if (visitor->currentMethodInfo.variables->count(name)) {
       return visitor->currentMethodInfo.variables->at(name).offset;
    }
    else {
        if (visitor->classTable->at(class_name).members->count(name))
            return visitor->classTable->at(class_name).members->at(name).offset;
        class_name = visitor->classTable->at(class_name).superClassName;
        while (visitor->classTable->at(class_name).members->count(name) == 0) {
            result += visitor->classTable->at(class_name).membersSize;
            class_name = visitor->classTable->at(class_name).superClassName;
        }
        return result + visitor->classTable->at(class_name).members->at(name).offset;
    }
}

// helper function to find the proper offset of a given class's member.
int findMemberOffset(CodeGenerator* visitor, std::string class_name, std::string name) {
    int result = 0;
    if (visitor->classTable->at(class_name).members->count(name))
        return visitor->classTable->at(class_name).members->at(name).offset;
    class_name = visitor->classTable->at(class_name).superClassName;
    while (visitor->classTable->at(class_name).members->count(name) == 0)
        class_name = visitor->classTable->at(class_name).superClassName;
    return visitor->classTable->at(class_name).members->at(name).offset;
}

// helper function to find the classObjectName of a variable with the given name.
std::string findVariableObjectName(CodeGenerator* visitor, std::string class_name, std::string name) {
    if (visitor->currentMethodInfo.variables->count(name))
        return visitor->currentMethodInfo.variables->at(name).type.objectClassName;
    
    if ((*(visitor->classTable))[class_name].members->count(name))
        return visitor->classTable->at(class_name).members->at(name).type.objectClassName;
    
    class_name = (*(visitor->classTable))[class_name].superClassName;
    while (class_name.length()) {
        if ((*(visitor->classTable))[class_name].members->count(name))
            return visitor->classTable->at(class_name).members->at(name).type.objectClassName;
        class_name = (*(visitor->classTable))[class_name].superClassName;
    }
    std::cout << "DID THIS POINT REALLY GET FUCKING REACHED" << std::endl;
    return ""; // SHOULD NEVER BE REACHED DUE TO THE TYPECHECKER.
}

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << ".data" << "                                   # start data segment." << std::endl;
    std::cout << "printstr: .asciz \"%d\\n\"" << "                 # define printing format for ints." << std::endl << std::endl;

    std::cout << ".text" << "                                   # start code segment." << std::endl;
    std::cout << ".globl Main_main" << "                        # tell the linker Main_main is a callable function." << std::endl << std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting ClassNode" << std::endl;

    // set current method info and current method name variables.
    this->currentClassInfo = this->classTable->at(node->identifier_1->name);
    this->currentClassName = node->identifier_1->name;

    // process the children.
    node->visit_children(this);
    if (COMMENTS_ON) std::cout  << "# Processing ClassNode" << std::endl;
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    TAB_COUNTER++;
    if (COMMENTS_ON) std::cout  << "# Visiting MethodNode" << std::endl;

    std::string class_name = this->currentClassName;
    while (this->classTable->at(class_name).methods->count(node->identifier->name) == 0)
        class_name = this->classTable->at(class_name).superClassName;
    
    this->currentMethodInfo = this->classTable->at(class_name).methods->at(node->identifier->name);
    this->currentMethodName = node->identifier->name;

    std::cout << this->currentClassName << "_" << this->currentMethodName << ":" << std::endl;
    
    node->methodbody->accept(this); // we don't want to visit the parameterNodes unless we need them in the body.
    TAB_COUNTER--;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    TAB_COUNTER++;
    if (COMMENTS_ON) std::cout  << "# Visiting MethodBodyNode" << std::endl;

    // callee function prologue.
    if (COMMENTS_ON) std::cout  << "# Starting callee function prologue." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ebp" << "                          # push old base frame pointer onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov %esp, %ebp" << "                     # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub $" << this->currentMethodInfo.localsSize << ", %esp" << "                     # allocate space for local variables of the method." << std::endl << std::endl;
    
    if (this->currentMethodName != "main") {
        std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # put callee-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %esi" << "                        # put callee-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %edi" << "                        # put callee-saved register onto the stack." << std::endl << std::endl;
    }
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing MethodBodyNode" << std::endl;

    // function callee epilogue.
    if (COMMENTS_ON) std::cout  << "# Starting callee function epilogue." << std::endl;

    if (this->currentMethodName != "main") {
        std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # save the return value in %eax as per __cdecl convention." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %edi" << "                         # get callee-saved register from the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %esi" << "                         # get callee-saved register from the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                         # get callee-saved register from the stack." << std::endl << std::endl;
    }

    std::cout << getIndent(TAB_COUNTER) << "mov %ebp, %esp" << "                   # deallocate space for local variables of the method." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ebp" << "                         # restore previous base frame pointer." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "ret" << "                              # jump back to return address of the caller." << std::endl << std::endl;
    TAB_COUNTER--;
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    TAB_COUNTER++;
    // find the variables offset in memory, pass that in.
    if (this->currentMethodInfo.variables->count(node->identifier->name)) {
        std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier->name) << "(%ebp), %eax";
    } else {
        std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx" << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov " << findMemberOffset(this, this->currentClassName, node->identifier->name) << "(%ebx), %eax";
    }

    std::cout << getIndent(TAB_COUNTER) << "             # load the parameter value from the right place in memory." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put it on top of the stack." << std::endl;
    TAB_COUNTER--;
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    /* nothing needs to be done for declarations, symbol table has this information */
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    if (COMMENTS_ON) std::cout << "# Visiting ReturnStatementNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << "# Processing ReturnStatementNode." << std::endl;
}

// # ------------------------------------------------------------------------------------------------ //
// # MAKE SURE TO FILL IN THE CODE FOR MEMBER ACCESS
// # ------------------------------------------------------------------------------------------------ //
void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting AssignmentNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout  << "# Processing AssignmentNode." << std::endl;
    
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                            # get value of the expression from the top of the stack." << std::endl;
    
    if (node->identifier_2) {
        std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier_1->name) << "(%ebp), %ebx";
        std::cout << getIndent(TAB_COUNTER) << "              # get the object self pointer from the right place in memory, put it into %ebx." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov %eax, " << findMemberOffset(this, findVariableObjectName(this, this->currentClassName, node->identifier_1->name), node->identifier_2->name) << "(%ebx)";
        std::cout << getIndent(TAB_COUNTER) << "              # store value of right-hand side expression at the right offset from the object self pointer." << std::endl << std::endl;
    } else {
        if (this->currentMethodInfo.variables->count(node->identifier_1->name)) {
            std::cout << getIndent(TAB_COUNTER) << "mov %eax, " << findVariableOffset(this, this->currentClassName, node->identifier_1->name) << "(%ebp)";
        } else {
            std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx" << std::endl;
            std::cout << getIndent(TAB_COUNTER) << "mov %eax, " << findMemberOffset(this, this->currentClassName, node->identifier_1->name) << "(%ebx)";
        }
        std::cout << getIndent(TAB_COUNTER) << "              # store value of right-hand side expression at the right place in memory." << std::endl << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting CallNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout  << "# Processing CallNode." << std::endl;
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting IfElseNode." << std::endl;

    node->expression->accept(this); // visit the expression.
    int temp = this->nextLabel();

    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the result of the if expression from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %ebx" << "                       # put 0 into %ebx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %eax, %ebx" << "                     # check if result of expression was false." << std::endl;

    if (node->statement_list_2) {
        std::cout << getIndent(TAB_COUNTER) << "je else_statement_" << temp << "         # jump if expression evaluated to false" << std::endl;
                
        for (std::list<StatementNode*>::iterator it = node->statement_list_1->begin(); it != node->statement_list_1->end(); it++)
            (*(it))->accept(this);
        
        std::cout << getIndent(TAB_COUNTER) << "jmp after_if_" << temp << "                     # jump past the else statement" << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "else_statement_" << temp << ":" << std::endl;
        
        for (std::list<StatementNode*>::iterator it = node->statement_list_2->begin(); it != node->statement_list_2->end(); it++)
            (*(it))->accept(this);

        std::cout << getIndent(TAB_COUNTER) << "after_if_" << temp << ":" << std::endl;
    } else {
        std::cout << getIndent(TAB_COUNTER) << "je after_if_" << temp << "               # jump if expression evaluated to false" << std::endl;
        
        for (std::list<StatementNode*>::iterator it = node->statement_list_1->begin(); it != node->statement_list_1->end(); it++)
            (*(it))->accept(this);

        std::cout << getIndent(TAB_COUNTER) << "after_if_" << temp << ":" << std::endl << std::endl;
    }
}


void CodeGenerator::visitWhileNode(WhileNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting WhileNode." << std::endl;

    int temp = this->nextLabel();
    std::cout << getIndent(TAB_COUNTER) << "while_condition_" << temp << ":" << std::endl;

    node->expression->accept(this);
    
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the result of the if expression from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %ebx" << "                       # put 0 into %ebx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %eax, %ebx" << "                     # check if result of expression was false." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "je after_while_" << temp << "               # jump if expression evaluated to false" << std::endl;

    for (std::list<StatementNode*>::iterator it = node->statement_list->begin(); it != node->statement_list->end(); it++)
        (*(it))->accept(this);
    std::cout << getIndent(TAB_COUNTER) << "jmp while_condition_" << temp << "               # jump if expression evaluated to false" << std::endl;

    std::cout << getIndent(TAB_COUNTER) << "after_while_" << temp << ":" << std::endl << std::endl;
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting PrintNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout  << "# Processing PrintNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push $printstr" << "                   # load format to be used for printing." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "call printf" << "                      # print value in the return expression." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop format used for printing off the stack into an unused register." << std::endl << std::endl;   
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting DoWhileNode." << std::endl;

    int temp = this->nextLabel();
    std::cout << getIndent(TAB_COUNTER) << "do_while_" << temp << ":" << std::endl;

    for (std::list<StatementNode*>::iterator it = node->statement_list->begin(); it != node->statement_list->end(); it++)
        (*(it))->accept(this);

    node->expression->accept(this);

    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the result of the if expression from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %ebx" << "                       # put 0 into %ebx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %eax, %ebx" << "                     # check if result of expression was false." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jne do_while_" << temp << "              # jump if expression evaluated to false" << std::endl << std::endl;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting PlusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing PlusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "add %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting MinusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing MinusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting TimesNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing TimesNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "imul %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting DivideNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing DivideNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                           # pop the divisor." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # pop the dividend." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cdq" << "                                # sign extend %eax (the dividend) into %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "idiv %ebx" << "                          # quotient is now in %eax, remainder is in %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %edx" << "                       # set the remainder back to zero." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                          # save result on top of the stack." << std::endl << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting NegationNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing NegationNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "neg %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting GreaterNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout  << "# Processing GreaterNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jg is_greater_" << temp << "             # jump if %edx > %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_greater_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl << std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting GreaterEqualNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout  << "# Processing GreaterEqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jge is_greater_or_equal_" << temp << "   # jump if %edx >= %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_greater_or_equal_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting EqualNode." << std::endl;
    node->visit_children(this);

    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout  << "# Processing EqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "je is_equal_" << temp << "               # jump if %edx == %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_equal_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting AndNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing AndNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "andl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting OrNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing OrNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "orl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting NotNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout  << "# Processing NotNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "popl %eax" << "                         # pop the operand from stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "notl %eax" << "                        # perform logical not." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "andl $0x00000001, %eax" << "           # set all bits but the last one to 0." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl %eax" << "                        # push result onto the stack." << std::endl << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting MethodCallNode." << std::endl;

    // THIS IS A PRE-CALL HERE (ASSEMBLE THE ACTIVATION RECORD OF THE METHOD WE ARE CALLING).

    // push the caller-saved registers onto the stack.
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put caller-saved register onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ecx" << "                        # put caller-saved register onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %edx" << "                        # put caller-saved register onto the stack." << std::endl << std::endl;

    // push parameters onto the stack (in reverse order as per __cedcl convention).
    for (std::list<ExpressionNode*>::reverse_iterator it = node->expression_list->rbegin(); it != node->expression_list->rend(); ++it)
        (*(it))->accept(this);
    
    if (node->identifier_2) {
        std::cout << getIndent(TAB_COUNTER) << "mov ";
        std::string object_name = findVariableObjectName(this, this->currentClassName, node->identifier_1->name);

        while (!(this->classTable->at(object_name).methods->count(node->identifier_2->name)))
            object_name = this->classTable->at(object_name).superClassName;
        
        std::cout << findVariableOffset(this, object_name, node->identifier_1->name) << "(%ebp), %ebx";

        std::cout << getIndent(TAB_COUNTER) << "              # get the object self pointer from the right place in memory, put it into %ebx." << std::endl << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # push the receiver object self pointer." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "call " << object_name << "_" << node->identifier_2->name;
        std::cout << "                     # perform the appropriate method call." << std::endl;
    } else {
        if (this->currentClassName == "Main") {
            std::cout << getIndent(TAB_COUNTER) << "push %ebp" << "                        # push the base frame for the Main class onto the stack." << std::endl;
        } else {
            std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx" << std::endl;
            std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # push the object self pointer onto the stack as argument 1." << std::endl;
        }

        if (this->classTable->at(this->currentClassName).methods->count(node->identifier_1->name)) {
            std::cout << getIndent(TAB_COUNTER) << "call " << this->currentClassName << "_" << node->identifier_1->name;
            std::cout << "                     # method is in the current class. perform method call." << std::endl;
        } else {
            std::string superclass = this->classTable->at(this->currentClassName).superClassName;
            while (!(this->classTable->at(superclass).methods->count(node->identifier_1->name)))
                superclass = this->classTable->at(superclass).superClassName;
            
            std::cout << getIndent(TAB_COUNTER) << "call " << superclass << "_" << node->identifier_1->name;
            std::cout << "                     # this is an inherited method. perform method call." << std::endl;
        }
    }

    // THIS IS A POST-RETURN HERE (DISASSEMBLE THE ACTIVATION RECORD AFTER METHOD IS DONE EXECUTING).

    // pop the object self pointer from stack.
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop the receiver object self pointer off the stack." << std::endl;
    
    // pop all parameters from stack.
    for (int i = 0; i < node->expression_list->size(); i++)
        std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop argument off the stack after method has been called." << std::endl;

    // save results of the method.
    std::cout << getIndent(TAB_COUNTER) << "mov %eax, %ebx" << "                   # save the value returned by the method." << std::endl;
    
    // pop the caller-saved registers from stack.
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                         # get value of caller-saved register from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # get value of caller-saved register from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # get value of caller-saved register from the stack." << std::endl << std::endl;

    // put method call result on top of the stack.
    std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # push the result returned by method call on top of the stack.." << std::endl;
}

// if (this->currentMethodInfo.variables->count(node->identifier->name)) {
//     std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier->name) << "(%ebp), %eax";
// } else {
//     std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx" << std::endl;
//     std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier->name) << "(%ebx), %eax";
// }

// std::cout << getIndent(TAB_COUNTER) << "             # load the variable value from the right place in memory." << std::endl;
// std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put it on top of the stack." << std::endl;

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    if (this->currentMethodInfo.variables->count(node->identifier_1->name)) {
        std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier_1->name) << "(%ebp), %ebx";
        std::cout << getIndent(TAB_COUNTER) << "              # get the object self pointer from the right place in memory, put it into %ebx." << std::endl;
    } else {
        std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx";
        std::cout << getIndent(TAB_COUNTER) << "              # get the object self pointer from the right place in memory, put it into %ebx." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov " << findMemberOffset(this, this->currentClassName, node->identifier_1->name) << "(%ebx), %ebx";
        std::cout << getIndent(TAB_COUNTER) << "              # get the object self pointer from the right place in memory, put it into %ebx." << std::endl;
    }
    std::cout << getIndent(TAB_COUNTER) << "push " << findMemberOffset(this, findVariableObjectName(this, this->currentClassName, node->identifier_1->name), node->identifier_2->name) << "(%ebx)";
    std::cout << getIndent(TAB_COUNTER) << "              # store value of right-hand side expression at the right offset from the object self pointer." << std::endl << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) {
    if (this->classTable->at(node->identifier->name).methods->count(node->identifier->name) == 0) {
        // no constructor exists, allocate space and das it.
        std::cout << getIndent(TAB_COUNTER) << "pushl $" << findObjectMemberSize(this, node->identifier->name);
        std::cout <<  "                      # PUSHED MEMBERSIZE ONTO THE STACK." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "call malloc" << "                      # allocate space for object on the heap." << std::endl;
        std::cout << genIndent(TAB_COUNTER) << "add $4, %esp" << "                     # move stack pointer past the malloc argument." << std::endl;
        std::cout << genIndent(TAB_COUNTER) << "push %eax" << "                        # push pointer to the allocated space onto the stack." << std::endl << std::endl;
    } else {
        // constructor exists. do the pre-call, then allocate the space and slap the allocated object pointer in with da parameters then do a mf post return.
        
        // THIS IS A PRE-CALL HERE (ASSEMBLE THE ACTIVATION RECORD OF THE METHOD WE ARE CALLING).
        // push the caller-saved registers onto the stack.
        std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put caller-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %ecx" << "                        # put caller-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %edx" << "                        # put caller-saved register onto the stack." << std::endl << std::endl;
        
        // push parameters onto the stack (in reverse order as per __cedcl convention).
        if (node->expression_list)
            for (std::list<ExpressionNode*>::reverse_iterator it = node->expression_list->rbegin(); it != node->expression_list->rend(); ++it)
                (*(it))->accept(this);

        std::cout << getIndent(TAB_COUNTER) << "pushl $" << findObjectMemberSize(this, node->identifier->name);
        std::cout <<  "                                         # PUSHED MEMBERSIZE ONTO THE STACK BOUTTA CALL CONSTRUCTOR." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "call malloc" << "                                             # allocate space for object on the heap." << std::endl;
        std::cout << genIndent(TAB_COUNTER) << "add $4, %esp" << "                                            # move stack pointer past the malloc argument." << std::endl;

        std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # push the receiver (fresh-created) object self pointer onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "call " << node->identifier->name << "_" << node->identifier->name;
        std::cout << "                     # call the constructor of the newly created object." << std::endl << std::endl;
        
        // THIS IS A POST-RETURN HERE (DISASSEMBLE THE ACTIVATION RECORD AFTER METHOD IS DONE EXECUTING).
        // pop the object self pointer from stack.
        std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                         # pop the receiver object self pointer off the stack." << std::endl;
        
        // pop all parameters from stack.
        if (node->expression_list)
            for (int i = 0; i < node->expression_list->size(); i++)
                std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop argument off the stack after method has been called." << std::endl;
        
        // pop the caller-saved registers from stack.
        std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                         # get value of caller-saved register from the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # get value of caller-saved register from the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # get value of caller-saved register from the stack." << std::endl << std::endl;

        // put method call result on top of the stack.
        std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # push the receiver object self pointer onto the stack as a returned value." << std::endl;            
    }

}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting Variable." << std::endl;
    if (this->currentMethodInfo.variables->count(node->identifier->name)) {
        std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, this->currentClassName, node->identifier->name) << "(%ebp), %eax";
    } else {
        std::cout << getIndent(TAB_COUNTER) << "mov 8(%ebp), %ebx" << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov " << findMemberOffset(this, this->currentClassName, node->identifier->name) << "(%ebx), %eax";
    }

    std::cout << getIndent(TAB_COUNTER) << "             # load the variable value from the right place in memory." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put it on top of the stack." << std::endl;
}


void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visiting Integer." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push integer onto the stack." << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    if (COMMENTS_ON) std::cout  << "# Visited Boolean." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push boolean onto the stack." << std::endl;
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    /* information from this node has already been obtained. */
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    /* information from this node has already been obtained. */
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    /* information from this node has already been obtained. */
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    /* information from this node has already been obtained. */
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    /* information from this node has already been obtained. */
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    /* information from this node has already been obtained. */
}
