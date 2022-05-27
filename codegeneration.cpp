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
    std::cout << ".data" << "                                # start data segment." << std::endl;
    std::cout << "printstr: .asciz \"%d\\n\"" << "              # define printing format for ints." << std::endl << std::endl;

    std::cout << ".text" << "                                # start code segment." << std::endl;
    std::cout << ".globl Main_main" << "                     # tell the linker Main_main is a callable function." << std::endl << std::endl;
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
    if (COMMENTS_ON) std::cout << "# Processing MethodBodyNode" << std::endl;
    TAB_COUNTER--;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MethodBodyNode" << std::endl;

    // callee function prologue.
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Starting callee function prologue." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ebp" << "                        # push old base frame pointer onto the stack." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov %esp, %ebp" << "                   # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub $" << this->currentMethodInfo.localsSize << ", %esp" << "                     # allocate space for local variables of the method." << std::endl;
    
    if (this->currentMethodName != "main") {
        std::cout << getIndent(TAB_COUNTER) << "push %ebx" << "                        # callee responsible for preserving contents of this register." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %esi" << "                        # callee responsible for preserving contents of this register." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "push %edi" << "                        # callee responsible for preserving contents of this register." << std::endl << std::endl;
    }

    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing MethodBodyNode" << std::endl;

    // function callee epilogue.
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Starting callee function epilogue." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # save the return value in %eax as per __cdecl convention." << std::endl;

    if (this->currentMethodName != "main") {
        std::cout << getIndent(TAB_COUNTER) << "pop %edi" << "                         # callee responsible for preserving contents of this register." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %esi" << "                         # callee responsible for preserving contents of this register." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                         # callee responsible for preserving contents of this register." << std::endl;
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
        std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                          # get value of the expression from the top of the stack." << std::endl;
        std::cout << getIndent(TAB_COUNTER) << "mov %eax, " << findVariableOffset(this, node->identifier_1->name) << "(%ebp)";
        std::cout << getIndent(TAB_COUNTER) << "            # store value of right-hand side expression at the right place in memory." << std::endl << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting CallNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing CallNode." << std::endl;
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting IfElseNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing IfElseNode." << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitWhileNode(WhileNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting WhileNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing WhileNode." << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting PrintNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing PrintNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push $printstr" << "                   # load format to be used for printing." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "call printf" << "                      # print value in the return expression." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # pop format used for printing off the stack into an unused register." << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting DoWhileNode." << std::endl;
    node->visit_children(this);
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing DoWhileNode." << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting PlusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing PlusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "add %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MinusNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing MinusNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "sub %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting TimesNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing TimesNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "imul %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting DivideNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing DivideNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ebx" << "                           # pop the divisor." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                           # pop the dividend." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cdq" << "                                # sign extend %eax (the dividend) into %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "idiv %ebx" << "                          # quotient is now in %eax, remainder is in %edx." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov $0, %edx" << "                       # set the remainder back to zero." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                          # save result on top of the stack." << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting NegationNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing NegationNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "neg %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting GreaterNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing GreaterNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jg label_" << temp << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "label_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting GreaterEqualNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing GreaterEqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "jge label_" << temp << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "label_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting EqualNode." << std::endl;
    node->visit_children(this);

    int temp = this->nextLabel();

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing EqualNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "cmp %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "je label_" << temp << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $0" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "label_" << temp << ":" << std::endl;
    std::cout << getIndent(TAB_COUNTER + 1) << "pushl $1" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting AndNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing AndNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "andl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting OrNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing OrNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "orl %edx, %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting NotNode." << std::endl;
    node->visit_children(this);

    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Processing NotNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "notl %eax" << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // TAB_COUNTER++;
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting MethodCallNode." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # caller responsible for preserving contents of this register." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %ecx" << "                        # caller responsible for preserving contents of this register." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %edx" << "                        # caller responsible for preserving contents of this register." << std::endl << std::endl;
    
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# making a method call here." << std::endl;
    node->visit_children(this);
    

    std::cout << getIndent(TAB_COUNTER) << "pop %edx" << "                         # caller responsible for preserving contents of this register." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %ecx" << "                         # caller responsible for preserving contents of this register." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pop %eax" << "                         # caller responsible for preserving contents of this register." << std::endl << std::endl;
    // TAB_COUNTER--;
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // TAB_COUNTER++;
    node->visit_children(this);
    // TAB_COUNTER--;
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting Variable." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "mov " << findVariableOffset(this, node->identifier->name) << "(%ebp), %eax";
    std::cout << getIndent(TAB_COUNTER) << "           # load the variable value from the right place in memory." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "push %eax" << "                        # put it on top of the stack." << std::endl << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visiting Integer." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push integer onto the stack." << std::endl << std::endl;
    // std::cout << getIndent(TAB_COUNTER) << "mov (%esp), %eax" << "                  # record integer literal in %eax." << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    if (COMMENTS_ON) std::cout << getIndent(TAB_COUNTER) << "# Visited Boolean." << std::endl;
    std::cout << getIndent(TAB_COUNTER) << "pushl $" << node->integer->value << "                         # push boolean onto the stack." << std::endl << std::endl;
    // std::cout << getIndent(TAB_COUNTER) << "mov (%esp), %eax" << "                  # record boolean literal in %eax." << std::endl;
}

void CodeGenerator::visitNewNode(NewNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // node->visit_children(this);
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // node->visit_children(this);
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // node->visit_children(this);
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // node->visit_children(this);
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    /* do nothing */
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    /* do nothing */
}
