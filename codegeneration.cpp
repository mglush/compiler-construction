#include "codegeneration.hpp"


// helper function to find the proper offset of a variable/member.
int findVariableOffset(CodeGenerator* visitor, std::string name) {
    int result = 0;
    if (visitor->currentMethodInfo.variables->count(name)) {
        result = visitor->currentMethodInfo.variables->at(name).offset;
    }
    else {
        std::string class_name = visitor->currentClassName;
        while (visitor->classTable->at(class_name).members->count(name) == 0) {
            result -= visitor->classTable->at(class_name).membersSize;
            class_name = visitor->classTable->at(class_name).superClassName;
        }
        result -= visitor->classTable->at(class_name).members->at(name).offset;
    }
    return result;
}

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << "\n------------------------------------\n" << "ASSEMBLY CODE:" << "\n------------------------------------\n";
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    std::cout << "---------------------------\n" << "Visiting " << node->identifier_1->name << " class" << "\n---------------------------" << std::endl;

    // set current method info and current method name variables.
    this->currentClassInfo = this->classTable->at(node->identifier_1->name);
    this->currentClassName = node->identifier_1->name;

    // process the children.
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
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
    std::cout << "  " << this->currentClassName << "_" << this->currentMethodName << ":" << std::endl;
    
    // callee function prologue.
    std::cout << "      # Starting callee function prologue." << std::endl;
    std::cout << "          push $ebp" << "       # push old base frame pointer onto the stack." << std::endl;
    std::cout << "          mov $esp $ebp" << "   # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << "          sub $" << this->currentMethodInfo.localsSize << ", %esp" << "    # allocate space for local variables of the method." << std::endl;

    // process the children.
    std::cout << "      # processing the method body." << std::endl;
    node->visit_children(this);
    
    // function callee epilogue.
    std::cout << "      # Starting callee function epilogue." << std::endl;
    std::cout << "          pop $eax" << "        # save the return value in $eax as per __cdecl convention." << std::endl;
    std::cout << "          mov $ebp $esp" << "   # deallocate space for local variables of the method." << std::endl;
    std::cout << "          pop $ebp" << "        # restore previous base frame pointer." << std::endl;
    std::cout << "          ret" << "             # jump back to return address of the caller." << std::endl;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    std::cout << "          Visiting MethodBodyNode" << std::endl;
    std::cout << "              push $ebx" << "       # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "              push $esi" << "       # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "              push $edi" << "       # callee responsible for preserving contents of this register." << std::endl;

    node->visit_children(this);

    std::cout << "              pop $edi" << "        # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "              pop $esi" << "        # callee responsible for preserving contents of this register." << std::endl;
    std::cout << "              pop $ebx" << "        # callee responsible for preserving contents of this register." << std::endl;
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    node->visit_children(this);

    if (node->identifier_2) {
        
    } else {
        std::cout << "          pop %edx" << "            # get value of the expression from the top of the stack." << std::endl;
        std::cout << "          mov %edx, " << findVariableOffset(this, node->identifier_1->name) << "(%ebp)";
        std::cout << "   # store value of right-hand side expression at the right place in memory." << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitWhileNode(WhileNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting PlusNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          add %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting MinusNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          sub %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting TimesNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          imul %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting DivideNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          idiv %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting NegationNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          neg %edx" << std::endl;
    std::cout << "          push %edx" << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "      # Visiting GreaterNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          cmp %edx, %eax" << std::endl;
    std::cout << "          jg label_" << temp << std::endl;
    std::cout << "          pushl $0" << std::endl;
    std::cout << "          label_" << temp << ":" << std::endl;
    std::cout << "              pushl $1" << std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "      # Visiting GreaterEqualNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          cmp %edx, %eax" << std::endl;
    std::cout << "          jge label_" << temp << std::endl;
    std::cout << "          pushl $0" << std::endl;
    std::cout << "          label_" << temp << ":" << std::endl;
    std::cout << "              pushl $1" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    node->visit_children(this);

    int temp = this->nextLabel();

    std::cout << "      # Visiting EqualNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          cmp %edx, %eax" << std::endl;
    std::cout << "          je label_" << temp << std::endl;
    std::cout << "          pushl $0" << std::endl;
    std::cout << "          label_" << temp << ":" << std::endl;
    std::cout << "              pushl $1" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting AndNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          andl %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting OrNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          pop %eax" << std::endl;
    std::cout << "          orl %edx, %eax" << std::endl;
    std::cout << "          push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    node->visit_children(this);

    std::cout << "      # Visiting NotNode." << std::endl;
    std::cout << "          pop %edx" << std::endl;
    std::cout << "          notl %edx" << std::endl;
    std::cout << "          push %edx" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    std::cout << "          push $eax" << "       # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "          push $ecx" << "       # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "          push $edx" << "       # caller responsible for preserving contents of this register." << std::endl;
    
    std::cout << "      # making a method call here." << std::endl;
    node->visit_children(this);

    std::cout << "          pop $edx" << "        # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "          pop $ecx" << "        # caller responsible for preserving contents of this register." << std::endl;
    std::cout << "          pop $eax" << "        # caller responsible for preserving contents of this register." << std::endl;
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    std::cout << "      # Visiting Variable." << std::endl;
    std::cout << "          mov " << findVariableOffset(this, node->identifier->name) << "(%ebp)" << ", %edx";
    std::cout << "   # store value of right-hand side expression at the right place in memory." << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    std::cout << "      # Visiting Integer." << std::endl;
    std::cout << "          pushl $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    std::cout << "      # Visited Boolean." << std::endl;
    std::cout << "          pushl $" << node->integer->value << std::endl;
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
