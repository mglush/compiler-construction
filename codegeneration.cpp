#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    std::cout << "\n------------------------------------\n" << "ASSEMBLY CODE:" << "\n------------------------------------\n";
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    node->visit_children(this);
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

    std::cout << "# Visited PlusNode" << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "add %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);

    std::cout << "# Visited MinusNode" << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "sub %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);

    std::cout << "# Visited TimesNode" << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "imul %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);

    std::cout << "# Visited DivideNode" << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "pop %eax" << std::endl;
    std::cout << "idiv %edx, %eax" << std::endl;
    std::cout << "push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);

    std::cout << "# Visited NegationNode" << std::endl;
    std::cout << "pop %edx" << std::endl;
    std::cout << "neg %edx" << std::endl;
    std::cout << "push %edx" << std::endl;
}

void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitAndNode(AndNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitOrNode(OrNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitNotNode(NotNode* node) {
    node->visit_children(this);
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
    std::cout << "# Visited Integer" << std::endl;
    std::cout << "pushl $" << node->integer->value << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitNewNode(NewNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    /* do nothing */
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    /* do nothing */
}
