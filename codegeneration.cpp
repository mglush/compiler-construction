#include "codegeneration.hpp"


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
    std::cout << ".data" << "                     # start data segment." << std::endl;
    std::cout << "printstr: .asciz \"%d\\n\"" << "          # define printing format for ints." << std::endl << std::endl;

    std::cout << ".text" << "                     # start code segment." << std::endl;
    std::cout << ".globl Main_main" << "          # tell the linker Main_main is a callable function." << std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    std::cout << "# Visiting ClassNode" << std::endl;
    // uncomment the following line to have the output display when a class definition is entered.
    // std::cout << "---------------------------\n" << "Visiting " << node->identifier_1->name << " class" << "\n---------------------------" << std::endl;

    // set current method info and current method name variables.
    this->currentClassInfo = this->classTable->at(node->identifier_1->name);
    this->currentClassName = node->identifier_1->name;

    // process the children.
    node->visit_children(this);
    std::cout << "# Processing ClassNode" << std::endl;
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    std::cout << "# Visiting MethodNode" << std::endl;
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
    std::cout << "# Processing MethodBodyNode" << std::endl;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    std::cout << "# Visiting MethodBodyNode" << std::endl;

    // callee function prologue.
    std::cout << "# Starting callee function prologue." << std::endl;
    std::cout << "push %ebp" << "           # push old base frame pointer onto the stack." << std::endl;
    std::cout << "mov %esp, %ebp" << "      # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << "sub $" << this->currentMethodInfo.localsSize << ", %esp" << "         # allocate space for local variables of the method." << std::endl;
    
    std::cout << "push %ebx" << "         # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "push %esi" << "         # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "push %edi" << "         # callee responsible for preserving contents of this register." << std::endl;

    node->visit_children(this);
    std::cout << "# Processing MethodBodyNode" << std::endl;

    // function callee epilogue.
    std::cout << "# Starting callee function epilogue." << std::endl;
    std::cout << "pop %eax" << "    # save the return value in %eax as per __cdecl convention." << std::endl;

    std::cout << "pop %edi" << "          # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "pop %esi" << "          # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "pop %ebx" << "          # callee responsible for preserving contents of this register." << std::endl;

    std::cout << "mov %ebp, %esp" << "      # deallocate space for local variables of the method." << std::endl;
    std::cout << "pop %ebp" << "          # restore previous base frame pointer." << std::endl;
    std::cout << "ret" << "               # jump back to return address of the caller." << std::endl;
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    std::cout << "# Visiting DeclarationNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing DeclarationNode." << std::endl;
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    std::cout << "# Visiting ReturnStatementNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing ReturnStatementNode." << std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    std::cout << "# Visiting AssignmentNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing AssignmentNode." << std::endl;
    if (node->identifier_2) {
        
    } else {
        std::cout << "pop %edx" << "          # get value of the expression from the top of the stack." << std::endl;
        std::cout << "mov %edx, " << findVariableOffset(this, node->identifier_1->name) << "(%ebp)";
        std::cout << "      # store value of right-hand side expression at the right place in memory." << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    std::cout << "# Visiting CallNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing CallNode." << std::endl;
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    std::cout << "# Visiting IfElseNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing IfElseNode." << std::endl;
}

void CodeGenerator::visitWhileNode(WhileNode* node) {
    std::cout << "# Visiting WhileNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing WhileNode." << std::endl;
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    std::cout << "# Visiting PrintNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing PrintNode." << std::endl;
    std::cout << "push $printstr" << "          # load format to be used for printing." << std::endl;
    std::cout << "call printf" << "             # print value in the return expression." << std::endl;
    std::cout << "pop %eax" << "                # load format to be used for printing." << std::endl;
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    std::cout << "# Visiting DoWhileNode." << std::endl;
    node->visit_children(this);
    std::cout << "# Processing DoWhileNode." << std::endl;
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    std::cout << "# Visiting PlusNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing PlusNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "add %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    std::cout << "# Visiting MinusNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing MinusNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "sub %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    std::cout << "# Visiting TimesNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing TimesNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "imul %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    std::cout << "# Visiting DivideNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing DivideNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "idiv %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    std::cout << "# Visiting NegationNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing NegationNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "neg %edx" << std::endl;
    std::cout << "push %edx" << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    std::cout << "# Visiting GreaterNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "# Processing GreaterNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %edx, %eax" << std::endl;
    std::cout << "jg label_" << temp << std::endl;
    std::cout << "pushl $0" << std::endl;
    std::cout << "label_" << temp << ":" << std::endl;
    std::cout << "    pushl $1" << std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    std::cout << "# Visiting GreaterEqualNode." << std::endl;
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "# Processing GreaterEqualNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %edx, %eax" << std::endl;
    std::cout << "jge label_" << temp << std::endl;
    std::cout << "pushl $0" << std::endl;
    std::cout << "label_" << temp << ":" << std::endl;
    std::cout << "    pushl $1" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    std::cout << "# Visiting EqualNode." << std::endl;
    node->visit_children(this);

    int temp = this->nextLabel();

    std::cout << "# Processing EqualNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "cmp %edx, %eax" << std::endl;
    std::cout << "je label_" << temp << std::endl;
    std::cout << "pushl $0" << std::endl;
    std::cout << "label_" << temp << ":" << std::endl;
    std::cout << "    pushl $1" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    std::cout << "# Visiting AndNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing AndNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "andl %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    std::cout << "# Visiting OrNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing OrNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "orl %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    std::cout << "# Visiting NotNode." << std::endl;
    node->visit_children(this);

    std::cout << "# Processing NotNode." << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "notl %edx" << std::endl;
    std::cout << "push %edx" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    std::cout << "# Visiting MethodCallNode."
    std::cout << "push %eax" << "   # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "push %ecx" << "   # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "push %edx" << "   # caller responsible for preserving contents of this register." << std::endl;
    
    std::cout << "# making a method call here." << std::endl;
    node->visit_children(this);
    

    std::cout << "pop %edx" << "    # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "pop %ecx" << "    # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "pop %eax" << "    # caller responsible for preserving contents of this register." << std::endl;
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    std::cout << "# Visiting Variable." << std::endl;
    std::cout << "mov " << findVariableOffset(this, node->identifier->name) << "(%ebp)" << ", %eax";
    std::cout << "      # load the variable value from the right place in memory." << std::endl;
    std::cout << "push %eax" << "           # put it on top of the stack." << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    std::cout << "# Visiting Integer." << std::endl;
    std::cout << "pushl $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    std::cout << "# Visited Boolean." << std::endl;
    std::cout << "pushl $" << node->integer->value << std::endl;
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
