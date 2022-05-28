#include "codegeneration.hpp"

int TAB_COUNTER = 0;        // keeps track of tabs to use when printing assembly code.
bool INDENT_ON = true;      // set to false if no indentation is wanted.
bool COMMENTS_ON = false;   // set to false if you don't want the generated assembly to generate comments.

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

// helper function to find the proper offset of a variable/member.
int findVariableOffset(CodeGenerator* visitor, std::string name) {
    int result = 8;
    if (visitor->currentMethodInfo.variables->count(name)) {
        result = visitor->currentMethodInfo.variables->at(name).offset;
    }
    else {
        std::string class_name = visitor->currentClassName;
        while (visitor->classTable->at(class_name).members->count(name) == 0) {
            result += visitor->classTable->at(class_name).membersSize;
            class_name = visitor->classTable->at(class_name).superClassName;
        }
        result += visitor->classTable->at(class_name).members->at(name).offset;
    }
    return result;
}

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << ".data" << "                                   # start data segment." << std::endl;
    std::cout << "printstr: .asciz \"%d\\n\"" << "                 # define printing format for ints." << std::endl << std::endl;

    std::cout << ".text" << "                                   # start code segment." << std::endl;
    std::cout << ".globl Main_main" << "                        # tell the linker Main_main is a callable function." << std::endl << std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting ClassNode" << std::endl;

    // set current method info and current method name variables.
    this->currentClassInfo = this->classTable->at(node->identifier_1->name);
    this->currentClassName = node->identifier_1->name;

    // process the children.
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing ClassNode" << std::endl;
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MethodNode" << std::endl;
    // find which class the method is defined in.
    // if it's not the current class, it must be
    // one of the superclasses of the current class.
    std::string class_name = this->currentClassName;
    while (this->classTable->at(class_name).methods->count(node->identifier->name) == 0)
        class_name = this->classTable->at(class_name).superClassName;
    
    // set current method info and current method name variables.
    this->currentMethodInfo = this->classTable->at(class_name).methods->at(node->identifier->name);
    this->currentMethodName = node->identifier->name;

    // give the method a label so it can be referred to later.
    std::cout << this->currentClassName << "_" << this->currentMethodName << ":" << std::endl;
    node->visit_children(this);
    TAB_COUNTER--;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MethodBodyNode" << std::endl;

    // callee function prologue.
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Starting callee function prologue." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ebp" << "                          # push old base frame pointer onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov %esp, %ebp" << "                     # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub $" << this->currentMethodInfo.localsSize << ", %esp" << "                     # allocate space for local variables of the method." << std::endl << std::endl;
    
    if (this->currentMethodName != "main") {
        std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # put callee-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %esi" << "                        # put callee-saved register onto the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %edi" << "                        # put callee-saved register onto the stack." << std::endl << std::endl;
    }

    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing MethodBodyNode" << std::endl;

    // function callee epilogue.
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Starting callee function epilogue." << std::endl;
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
    // node->visit_children(this);
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // std::cout << "# Visiting DeclarationNode." << std::endl;
    // node->visit_children(this);
    // std::cout << "# Processing DeclarationNode." << std::endl;
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    if (COMMENTS_ON) std::cout << "# Visiting ReturnStatementNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << "# Processing ReturnStatementNode." << std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting AssignmentNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing AssignmentNode." << std::endl;
    if (node->identifier_2) {
        
    } else {
        std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                            # get value of the expression from the top of the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov %eax, " << findVariableOffset(this, node->identifier_1->name) << "(%ebp)";
        std::cout << getIndent(TAB_COUNTER) << "              # store value of right-hand side expression at the right place in memory." << std::endl << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting CallNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing CallNode." << std::endl;
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting IfElseNode." << std::endl;

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
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting WhileNode." << std::endl;

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
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting PrintNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing PrintNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push $printstr" << "                   # load format to be used for printing." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "call printf" << "                      # print value in the return expression." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop format used for printing off the stack into an unused register." << std::endl << std::endl;   
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting DoWhileNode." << std::endl;

    int temp = this->nextLabel();

    std::cout << getIndent(TAB_COUNTER) << "do_while_" << temp << ":" << std::endl;

    for (std::list<StatementNode*>::iterator it = node->statement_list->begin(); it != node->statement_list->end(); it++)
        (*(it))->accept(this);

    node->expression->accept(this);

    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the result of the if expression from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %ebx" << "                       # put 0 into %ebx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %eax, %ebx" << "                     # check if result of expression was false." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jne do_while_" << temp << "              # jump if expression evaluated to false" << std::endl;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting PlusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing PlusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "add %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MinusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing MinusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting TimesNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing TimesNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "imul %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting DivideNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing DivideNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                           # pop the divisor." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # pop the dividend." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cdq" << "                                # sign extend %eax (the dividend) into %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "idiv %ebx" << "                          # quotient is now in %eax, remainder is in %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %edx" << "                       # set the remainder back to zero." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                          # save result on top of the stack." << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting NegationNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing NegationNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "neg %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting GreaterNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing GreaterNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jg is_greater_" << temp << "             # jump if %edx > %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_greater_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting GreaterEqualNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing GreaterEqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jge is_greater_or_equal_" << temp << "   # jump if %edx >= %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_greater_or_equal_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting EqualNode." << std::endl;
    node->visit_children(this);

    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing EqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                           # get the first operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # get the second operand." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << "                     # compare the operands." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "je is_equal_" << temp << "               # jump if %edx == %eax." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0"  << "                          # if not, push 0, or \"false\"." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jmp after_comparison_" << temp << "      # jump to the code that follows." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "is_equal_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << "                   # if yes, push 1, or \"true\"" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "after_comparison_" << temp << ":" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting AndNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing AndNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "andl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting OrNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing OrNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "orl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting NotNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing NotNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # pop the operand from stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "notl %eax" << "                        # perform logical not." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "andl $0x00000001, %eax" << "           # set all bits but the last to 0." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # push result onto the stack." << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MethodCallNode." << std::endl;

    // THIS IS A PRE-CALL HERE (ASSEMBLE THE ACTIVATION RECORD OF THE METHOD WE ARE CALLING).

    // push the caller-saved registers onto the stack.
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put caller-saved register onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ecx" << "                        # put caller-saved register onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %edx" << "                        # put caller-saved register onto the stack." << std::endl << std::endl;

    // push parameters onto the stack (in reverse order as per __cedcl convention).
    for (std::list<ExpressionNode*>::reverse_iterator it = node->expression_list->rbegin(); it != node->expression_list->rend(); ++it)
        (*(it))->accept(this);
    
    if (node->identifier_2) {
        /* FILL THIS BABY IN WITH CODE WHEN IMPLEMENTING OBJECTS */
    } else {
        // push object self pointer to the stack if caller is any function other than main.
        std::cout << getIndent(TAB_COUNTER) << "push %ebp" << "                        # push the current object self pointer onto the stack." << std::endl;
        
        // push return address onto the stack.
        std::cout << getIndent(TAB_COUNTER) << "push %esp" << "             `          # push the return address onto the stack" << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "call " << this->currentClassName << "_" << node->identifier_1 << std::endl;
    }
    
    // THIS IS A POST-RETURN HERE (DISASSEMBLE THE ACTIVATION RECORD AFTER METHOD IS DONE EXECUTING).

    // pop the return address from stack
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop return address off the stack" << std::endl;
    
    // pop the object self pointer and all parameters from stack.
    for (int i = 0; i <= node->expression_list->size(); i++)
        std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                            # pop argument off the stack after method has been called." << std::endl;

    // pop the caller-saved registers from stack.
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                         # get value of caller-saved register from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # get value of caller-saved register from the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # get value of caller-saved register from the stack." << std::endl << std::endl;
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting Variable." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, node->identifier->name) << "(%ebp), %eax";
    std::cout << getIndent(TAB_COUNTER) << "             # load the variable value from the right place in memory." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put it on top of the stack." << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting Integer." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push integer onto the stack." << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visited Boolean." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push boolean onto the stack." << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) {
    node->visit_children(this);
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
