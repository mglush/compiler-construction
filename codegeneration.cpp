#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << "\n------------------------------------\n" << "ASSEMBLY CODE:" << "\n------------------------------------\n";
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    this->currentClassName = node->identifier_1->name;
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    std::cout << "# Vistied MethodNode." << std::endl;

    // find which class the method is defined in.
    // if it's not the current class, it must be
    // one of the superclasses of the current class.
    std::string class_name = this->currentClassName;
    while (this->classTable->at(class_name).methods->count(node->identifier->name) == 0)
        class_name = this->classTable->at(class_name).superClassName;
    
    // set current method info and current method name variables.
    this->currentMethodInfo = this->classTable->at(class_name).methods->at(node->identifier->name);
    this->currentMethodName = node->identifier->name;

    // function prologue.
    std::cout << "# Starting function prologue." << std::endl;
    std::cout << "push $ebp" << "       # push old base frame pointer onto the stack." << std::endl;
    std::cout << "mov $esp $ebp" << "   # set current base frame pointer to stack pointer position." << std::endl;
    std::cout << "sub $" << this->currentMethodInfo.localsSize << ", %esp" << "     # allocate space for local variables of the method." << std::endl;

    // process the children.
    node->visit_children(this);
    
    // function epilogue.
    std::cout << "# Starting function epilogue." << std::endl;
    std::cout << "pop $eax" << "       # save the return value in $eax as per __cdecl convention." << std::endl;
    std::cout << "mov $ebp $esp" << "  # deallocate space for local variables of the method." << std::endl;
    std::cout << "pop $ebp" << "       # restore previous base frame pointer." << std::endl;
    std::cout << "ret" << "            # jump back to return address of the caller." << std::endl;
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    node->visit_children(this);
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

    std::cout << "  # Visited PlusNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited MinusNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited TimesNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited DivideNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  idiv %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited NegationNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  neg %edx" << std::endl;
    std::cout << "  push %edx" << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "  # Visited GreaterNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  cmp %edx, %eax" << std::endl;
    std::cout << "  jg label_" << temp << std::endl;
    std::cout << "  pushl $0" << std::endl;
    std::cout << "  label_" << temp << ":" << std::endl;
    std::cout << "      pushl $1" << std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    node->visit_children(this);
    
    int temp = this->nextLabel();

    std::cout << "  # Visited GreaterEqualNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  cmp %edx, %eax" << std::endl;
    std::cout << "  jge label_" << temp << std::endl;
    std::cout << "  pushl $0" << std::endl;
    std::cout << "  label_" << temp << ":" << std::endl;
    std::cout << "      pushl $1" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    node->visit_children(this);

    int temp = this->nextLabel();

    std::cout << "  # Visited EqualNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  cmp %edx, %eax" << std::endl;
    std::cout << "  je label_" << temp << std::endl;
    std::cout << "  pushl $0" << std::endl;
    std::cout << "  label_" << temp << ":" << std::endl;
    std::cout << "      pushl $1" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited AndNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  andl %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited OrNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  orl %edx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    node->visit_children(this);

    std::cout << "  # Visited NotNode." << std::endl;
    std::cout << "  pop %edx" << std::endl;
    std::cout << "  notl %edx" << std::endl;
    std::cout << "  push %edx" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    std::cout << "  # Visited Integer." << std::endl;
    std::cout << "  pushl $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    std::cout << "  # Visited Boolean." << std::endl;
    std::cout << "  pushl $" << node->integer->value << std::endl;
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
