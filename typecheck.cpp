#include "typecheck.hpp"

// keeps track of whether we are adding a
// variable table to a class or to a method,
// which in turn determines the offset of each variable in memory.
bool FLAG = true;

// counts the number of variables in a variable table
// with a negative offset; is used to set the membersSize
// variable of a class when visiting a classNode.
int COUNTER = 0;

// defines the function used to throw type errors. The possible
// type errors are defined as an enumeration in the header file.
// missing_return_statement error is not enumerated as it was
// added to the project description at a later date.
void typeError(TypeErrorCode code) {
  switch (code) {
    case undefined_variable:
      std::cerr << "Undefined variable." << std::endl;
      break;
    case undefined_method:
      std::cerr << "Method does not exist." << std::endl;
      break;
    case undefined_class:
      std::cerr << "Class does not exist." << std::endl;
      break;
    case undefined_member:
      std::cerr << "Class member does not exist." << std::endl;
      break;
    case not_object:
      std::cerr << "Variable is not an object." << std::endl;
      break;
    case expression_type_mismatch:
      std::cerr << "Expression types do not match." << std::endl;
      break;
    case argument_number_mismatch:
      std::cerr << "Method called with incorrect number of arguments." << std::endl;
      break;
    case argument_type_mismatch:
      std::cerr << "Method called with argument of incorrect type." << std::endl;
      break;
    case while_predicate_type_mismatch:
      std::cerr << "Predicate of while loop is not boolean." << std::endl;
      break;
    case do_while_predicate_type_mismatch:
      std::cerr << "Predicate of do while loop is not boolean." << std::endl;
      break;
    case if_predicate_type_mismatch:
      std::cerr << "Predicate of if statement is not boolean." << std::endl;
      break;
    case assignment_type_mismatch:
      std::cerr << "Left and right hand sides of assignment types mismatch." << std::endl;
      break;
    case return_type_mismatch:
      std::cerr << "Return statement type does not match declared return type." << std::endl;
      break;
    case constructor_returns_type:
      std::cerr << "Class constructor returns a value." << std::endl;
      break;
    case no_main_class:
      std::cerr << "The \"Main\" class was not found." << std::endl;
      break;
    case main_class_members_present:
      std::cerr << "The \"Main\" class has members." << std::endl;
      break;
    case no_main_method:
      std::cerr << "The \"Main\" class does not have a \"main\" method." << std::endl;
      break;
    case main_method_incorrect_signature:
      std::cerr << "The \"main\" method of the \"Main\" class has an incorrect signature." << std::endl;
      break;
  }
  exit(1);
}


/* These helper functions will be used 
 * during node visits to type check the program
 * and throw typeErrors when necessary. */

// a program must have a class called "Main".
void noMainClass(TypeCheck* visitor) {
  if (!visitor->classTable->count("Main"))
    typeError(no_main_class);
}

// the Main class of a program cannot have any members.
void mainClassMembersPresent(TypeCheck* visitor) {
  if ((*(visitor->classTable))["Main"].members->size())
    typeError(main_class_members_present);
}

// the Main class of a program must have a method "main".
void noMainMethod(TypeCheck* visitor) {
  if (!(*(visitor->classTable))["Main"].methods->count("main"))
    typeError(no_main_method);
}

// the main method of a program must have the following signature:
// main() -> none { ... }
// this means there can be no arguments and the return type must be none.
void mainMethodIncorrectSignature(MethodNode* node) {
  if (node->parameter_list->size() || node->type->basetype != bt_none)
    typeError(main_method_incorrect_signature);
}

// constructors must have return type none.
// constructors and their classes have the exact
// same name, including capitalization.
void constructorReturnsType(MethodNode* node) {
  if (node->type->basetype != bt_none)
    typeError(constructor_returns_type);
}

// if a method's return type is int, bool, or object, it must have a return statement.
// not allowed to modify typecheck.hpp, thus can't include this in enumeration.
void missingReturnStatement(MethodNode* node) {
  if (!(node->methodbody->returnstatement) && node->type->basetype != bt_none) {
    std::cerr << "Missing return statement." << std::endl;
    exit(1);
  }
}

// throws error when a class is referred to as a super class,
// a type of a variable, or a constructor name
// that has not been defined above in the program.
void undefinedClass(TypeCheck* visitor, std::string name) {
  for (std::map<std::string, ClassInfo>::iterator temp = visitor->classTable->begin(); temp != visitor->classTable->end(); temp++)
    if (temp->first == name)
      return;
  typeError(undefined_class);
}

// this applies when a method is called on an object
// (or on the current object) that does not exist
// in the class of that object or any super class.
std::pair<CompoundType, int> undefinedMethod(TypeCheck* visitor, std::string class_name, std::string name) {
  if ((*(visitor->classTable))[class_name].methods->count(name))
    return std::make_pair((*(visitor->classTable))[class_name].methods->at(name).returnType, (*(visitor->classTable))[class_name].methods->at(name).parameters->size());

  std::string superclass = (*(visitor->classTable))[class_name].superClassName;
  while (superclass.length()) {
    if ((*(visitor->classTable))[superclass].methods->count(name))
      return std::make_pair((*(visitor->classTable))[superclass].methods->at(name).returnType, (*(visitor->classTable))[superclass].methods->at(name).parameters->size());
    superclass = (*(visitor->classTable))[superclass].superClassName;
  }

  typeError(undefined_method);
  CompoundType temp = {bt_none, ""};
  return std::make_pair(temp, 0); // line should never be reached
}

// throws error when a member is referred to on an object
// (as part of an expression, or the destination of an assignment)
// that does not contain a member of that name.
CompoundType undefinedMember(TypeCheck* visitor, std::string class_name, std::string name) {
  if ((*(visitor->classTable))[class_name].members->count(name))
    return (*(visitor->classTable))[class_name].members->at(name).type;

  std::string superclass = (*(visitor->classTable))[class_name].superClassName;
  while (superclass.length()) {
    if ((*(visitor->classTable))[superclass].members->count(name))
      return (*(visitor->classTable))[superclass].members->at(name).type;
    superclass = (*(visitor->classTable))[superclass].superClassName;
  }

  typeError(undefined_member);
  return {bt_none, ""}; // line is never reached but prevents a compiler warning.
}

// throws error when a variable is referred to when
// it has not been defined as a local variable, parameter, or member. 
// must also check variable tables of all
// classes that the current class inherits from.
CompoundType undefinedVariable(TypeCheck* visitor, std::string name) {
  if (visitor->currentVariableTable->count(name))
    return (*(visitor->currentVariableTable))[name].type;
  if ((*(visitor->classTable))[visitor->currentClassName].members->count(name))
    return (*(*(visitor->classTable))[visitor->currentClassName].members)[name].type;
  
  std::string superclass = (*(visitor->classTable))[visitor->currentClassName].superClassName;
  while (superclass.length()) {
    if ((*(visitor->classTable))[superclass].members->count(name))
      return (*(*(visitor->classTable))[superclass].members)[name].type;
    superclass = (*(visitor->classTable))[superclass].superClassName;
  }

  typeError(undefined_variable);
  return {bt_none, ""}; // line is never reached but prevents a compiler warning.
}

// throws error when a method is called on or a member
// is referred to on a variable that is not an object.
// returns class name if the variable named 'name' is an object.
// the returned value is used in undefinedMember() error check function.
std::string notAnObject(TypeCheck* visitor, std::string name) {
  if (visitor->currentVariableTable->count(name))
    if (visitor->currentVariableTable->at(name).type.baseType == bt_object)
      return visitor->currentVariableTable->at(name).type.objectClassName;
  if ((*(visitor->classTable))[visitor->currentClassName].members->count(name))
    if ((*(visitor->classTable))[visitor->currentClassName].members->at(name).type.baseType == bt_object)
      return (*(visitor->classTable))[visitor->currentClassName].members->at(name).type.objectClassName;
  
  std::string superclass = (*(visitor->classTable))[visitor->currentClassName].superClassName;
  while (superclass.length()) {
    if ((*(visitor->classTable))[superclass].members->count(name))
      if ((*(visitor->classTable))[superclass].members->at(name).type.baseType == bt_object)
        return (*(visitor->classTable))[superclass].members->at(name).type.objectClassName;
    superclass = (*(visitor->classTable))[superclass].superClassName;
  }

  typeError(not_object);
  return ""; // line is never reached but prevents a compiler warning.
}

// This applies when the expression in the return
// statement for a method does not match its
// declared return type, or when a return statement
// is present in a method with a none return type.
void returnTypeMismatch(MethodNode* node) {
  if (node->type->basetype == bt_none && node->methodbody->returnstatement == NULL)
    return;
  if (node->type->basetype == node->methodbody->returnstatement->basetype)
    return;
  typeError(return_type_mismatch);
}

// throws error when a method or constructor is called with an incorrect
// number of arguments (not including self in any way).
std::list<CompoundType>* methodArgumentNumberMismatch(TypeCheck* visitor, std::string class_name, std::string method_name, int size) {
  if ((*(visitor->classTable))[class_name].methods->count(method_name))
    if ((*(*(visitor->classTable))[class_name].methods)[method_name].parameters->size() == size)
      return (*(*(visitor->classTable))[class_name].methods)[method_name].parameters;
  
  std::string superclass = (*(visitor->classTable))[class_name].superClassName;
  while (superclass.length()) {
    if ((*(visitor->classTable))[superclass].methods->count(method_name))
      if ((*(*(visitor->classTable))[superclass].methods)[method_name].parameters->size() == size)
        return (*(*(visitor->classTable))[superclass].methods)[method_name].parameters;

    superclass = (*(visitor->classTable))[superclass].superClassName;
  }

  typeError(argument_number_mismatch);
  return NULL; // line is never reached but prevents a compiler warning.
}

// throws error when a method or a constructor is called
// with the correct number of arguments, but one or more of the
// arguments does not have the type declared for the corresponding parameter.
void methodArgumentTypeMismatch(TypeCheck* visitor, std::list<ExpressionNode*>* expressions, std::list<CompoundType>* parameters) {
  std::list<CompoundType>::iterator iter1 = parameters->begin();
  for (ExpressionNode* expression : *(expressions)) {
    if (expression->basetype == bt_object) {
      if (expression->objectClassName != iter1->objectClassName)
        typeError(argument_type_mismatch);
    } else {
      if (expression->basetype != iter1->baseType)
        typeError(argument_type_mismatch);
    }
    iter1++;
  }
}

// helper function to insert to superclass member variables
// into the child class variable tables.
void modifySymbolTable(TypeCheck* visitor) {
    std::string superclass;
    int counter;
    for (std::map<std::string, ClassInfo>::iterator it = visitor->classTable->begin(); it != visitor->classTable->end(); it++) {
        superclass = it->second.superClassName;
        while (superclass.length()) {
          // go throough every member variable, and increase its offset.
          counter = 0;
          for (std::map<std::string, VariableInfo>::reverse_iterator iter = visitor->classTable->at(superclass).members->rbegin(); iter != visitor->classTable->at(superclass).members->rend(); iter++) {  
            VariableInfo newVariableInfo = {{iter->second.type.baseType, iter->second.type.objectClassName}, iter->second.offset + it->second.membersSize, iter->second.size};
            it->second.members->insert(std::make_pair(iter->first, newVariableInfo));
            counter++;
          }
          ClassInfo newClassInfo = {superclass, it->second.methods, it->second.members, it->second.membersSize + 4 * counter};
          visitor->classTable->erase(it);
          std::cout << "ERASED ERASED ERASED" << std::endl;
          visitor->classTable->insert(std::make_pair(it->first, newClassInfo));
          std::cout << "YOMP YOMPICURICUS YOMP" << std::endl;
          superclass = visitor->classTable->at(superclass).superClassName;
        }
    }
}

/* These node visitor functions will be used 
 * to build the symbol table for the program,
 * using helper functions to type-check it along the way. */

void TypeCheck::visitProgramNode(ProgramNode* node) {
  // each program has one class table.
  this->classTable = new ClassTable();
  
  node->visit_children(this);

  noMainClass(this);
  mainClassMembersPresent(this);
  noMainMethod(this);

  modifySymbolTable(this);
}

void TypeCheck::visitClassNode(ClassNode* node) {
  std::string superclass_name = "";
  VariableTable* members = new VariableTable();
  MethodTable* methods = new MethodTable();
  
  // record superclass information if it's available.
  if (node->identifier_2) {
    superclass_name = node->identifier_2->name;
    undefinedClass(this, superclass_name);
  }

  // set current-info trackers.
  this->currentClassName = node->identifier_1->name;
  this->currentMethodTable = methods;
  this->currentVariableTable = members;
  this->currentLocalOffset = -4;        // -4, -8, -12, ...
  this->currentMemberOffset = 0;        // 0, 4, 8, ...
  this->currentParameterOffset = 12;    // 12, 16, 20, ...

  // create and insert the entry of this class into the classTable.
  ClassInfo cur_class_info = {superclass_name, methods, members, 0};
  std::pair<std::string, ClassInfo> cur_class = std::make_pair(this->currentClassName, cur_class_info);
  this->classTable->insert(cur_class);
  
  // process the class.
  node->visit_children(this);

  // get the member size information into this class's ClassInfo.
  (*(this->classTable))[this->currentClassName].membersSize = 4 * members->size();
}

void TypeCheck::visitMethodNode(MethodNode* node) {
  // visit return type node to get the basetype information from it.
  node->type->accept(this);

  if (node->identifier->name == "main") 
    mainMethodIncorrectSignature(node);
  
  if (node->identifier->name == this->currentClassName)
    constructorReturnsType(node);

  // create variable table for this method.
  VariableTable* variables = new VariableTable();
  std::list<CompoundType>* params = new std::list<CompoundType>();
  
  // reset the offsets.
  this->currentLocalOffset = -4;        // -4, -8, -12, ...
  this->currentMemberOffset = 0;        // 0, 4, 8, ...
  this->currentParameterOffset = 12;    // 12, 16, 20, ...
  this->currentVariableTable = variables;
  
  node->visit_children(this);

  (*(this->classTable))[this->currentClassName].membersSize = this->currentMemberOffset;

  // keep track of the number & types of parameters for every method.
  for (ParameterNode* param : *(node->parameter_list))
    params->push_back({param->type->basetype, param->type->objectClassName});

  // insert the collected method information into the current method table.
  CompoundType return_type = {node->type->basetype, node->type->objectClassName};
  MethodInfo cur_method_info = {return_type, variables, params, 4 * COUNTER};
  (*currentMethodTable)[node->identifier->name] = cur_method_info;

  missingReturnStatement(node);
  returnTypeMismatch(node);
}

void TypeCheck::visitMethodBodyNode(MethodBodyNode* node) {
  COUNTER = 0; // set the counter for the next class' members.
  FLAG = false; // all members should have been declared before this point.

  node->visit_children(this);

  FLAG = true; // set the flag back to true for the next class' members.
}

void TypeCheck::visitParameterNode(ParameterNode* node) {
  node->visit_children(this);

  VariableInfo cur_var_info = {{node->type->basetype, node->type->objectClassName}, this->currentParameterOffset, 4};
  std::pair<std::string, VariableInfo> new_variable = std::make_pair(node->identifier->name, cur_var_info);
  this->currentVariableTable->insert(new_variable);

  this->currentParameterOffset += 4;
}

void TypeCheck::visitDeclarationNode(DeclarationNode* node) {
  node->visit_children(this);

  VariableInfo cur_var_info;

  // insert every part of the declaration into the current variable table.
  for (std::list<IdentifierNode*>::iterator temp = node->identifier_list->begin(); temp != node->identifier_list->end(); temp++) {
    if (!FLAG) {
      cur_var_info = {{node->type->basetype, node->type->objectClassName}, this->currentLocalOffset, 4};
      this->currentLocalOffset -= 4;
    } else {
      cur_var_info = {{node->type->basetype, node->type->objectClassName}, this->currentMemberOffset, 4};
      this->currentMemberOffset += 4;
    }
    std::pair<std::string, VariableInfo> new_variable = std::make_pair((*temp)->name, cur_var_info);
    this->currentVariableTable->insert(new_variable);
    COUNTER++;
  }
}

void TypeCheck::visitReturnStatementNode(ReturnStatementNode* node) {
  if (node) {
    node->visit_children(this);
    if (node->expression) {
      node->basetype = node->expression->basetype;
      node->objectClassName = node->expression->objectClassName;
    }
  }
}

void TypeCheck::visitAssignmentNode(AssignmentNode* node) {
  CompoundType temp;
  temp = undefinedVariable(this, node->identifier_1->name);
  if (node)
    node->visit_children(this);
  if (node->identifier_2)
      temp = undefinedMember(this, notAnObject(this, node->identifier_1->name), node->identifier_2->name);
  if (node->expression->basetype != temp.baseType)
    typeError(assignment_type_mismatch);
}

void TypeCheck::visitIfElseNode(IfElseNode* node) {
  if (node) {
    node->visit_children(this);
    if (node->expression->basetype != bt_boolean)
      typeError(if_predicate_type_mismatch);
  }
}

void TypeCheck::visitWhileNode(WhileNode* node) {
  if (node) {
    node->visit_children(this);
    if (node->expression->basetype != bt_boolean)
      typeError(while_predicate_type_mismatch);
  }
}

void TypeCheck::visitDoWhileNode(DoWhileNode* node) {
  if (node) {
    node->visit_children(this);
    if (node->expression->basetype != bt_boolean)
      typeError(do_while_predicate_type_mismatch);
  }
}

void TypeCheck::visitPrintNode(PrintNode* node) {
  if (node)
    node->visit_children(this);
}

void TypeCheck::visitCallNode(CallNode* node) {
  if (node) { 
    node->visit_children(this);
    node->basetype = node->methodcall->basetype;
    node->objectClassName = node->methodcall->objectClassName;
  }
}

void TypeCheck::visitPlusNode(PlusNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitMinusNode(MinusNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitTimesNode(TimesNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitDivideNode(DivideNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitGreaterNode(GreaterNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitGreaterEqualNode(GreaterEqualNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_integer || node->expression_2->basetype != bt_integer)
      typeError(expression_type_mismatch);
    
  }
}

void TypeCheck::visitEqualNode(EqualNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression_1->basetype != node->expression_2->basetype || node->expression_1->basetype == bt_object || node->expression_1->basetype == bt_none)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitAndNode(AndNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_boolean || node->expression_2->basetype != bt_boolean)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitOrNode(OrNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression_1->basetype != bt_boolean || node->expression_2->basetype != bt_boolean)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitNotNode(NotNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->visit_children(this);
    if (node->expression->basetype != bt_boolean)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitNegationNode(NegationNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->visit_children(this);
    if (node->expression->basetype != bt_integer)
      typeError(expression_type_mismatch);
  }
}

void TypeCheck::visitMethodCallNode(MethodCallNode* node) {
  if (node) {
    std::pair<CompoundType, int> temp;
    if (node->identifier_2) {
      std::string class_name = notAnObject(this, node->identifier_1->name);
      temp = undefinedMethod(this, class_name, node->identifier_2->name);

      node->basetype = temp.first.baseType;
      node->objectClassName = temp.first.objectClassName;
      node->visit_children(this);

      if (node->expression_list)
        methodArgumentTypeMismatch(this, node->expression_list, methodArgumentNumberMismatch(this, class_name, node->identifier_2->name, node->expression_list->size()));
      else
        methodArgumentNumberMismatch(this, class_name, node->identifier_2->name, 0);
    } else {
      temp = undefinedMethod(this, this->currentClassName, node->identifier_1->name);

      node->basetype = temp.first.baseType;
      node->objectClassName = temp.first.objectClassName;
      node->visit_children(this);

      if (node->expression_list)
        methodArgumentTypeMismatch(this, node->expression_list, methodArgumentNumberMismatch(this, this->currentClassName, node->identifier_1->name, node->expression_list->size()));
      else
        methodArgumentNumberMismatch(this, this->currentClassName, node->identifier_1->name, 0);
    }
  }
}

void TypeCheck::visitMemberAccessNode(MemberAccessNode* node) {
  if (node) {
    CompoundType temp;
    if (node->identifier_2) {
      temp = undefinedMember(this, notAnObject(this, node->identifier_1->name), node->identifier_2->name);

      node->basetype = temp.baseType;
      node->objectClassName = temp.objectClassName;
    } else {
      temp = undefinedMember(this, this->currentClassName, node->identifier_1->name);

      node->basetype = temp.baseType;
      node->objectClassName = temp.objectClassName;
    }
    node->visit_children(this);
  }
}

void TypeCheck::visitVariableNode(VariableNode* node) {
  if (node) {
    CompoundType temp = undefinedVariable(this, node->identifier->name);

    node->basetype = temp.baseType;
    node->objectClassName = temp.objectClassName;
    node->visit_children(this);
  }
}

void TypeCheck::visitNewNode(NewNode* node) {
  if (node) {
    undefinedClass(this, node->identifier->name);

    node->basetype = bt_object;
    node->objectClassName = node->identifier->name;
    node->visit_children(this);

    if (node->expression_list)
      methodArgumentTypeMismatch(this, node->expression_list, methodArgumentNumberMismatch(this, node->identifier->name, node->identifier->name, node->expression_list->size()));
    else
      if (this->classTable->at(node->identifier->name).methods->count(node->identifier->name))
        methodArgumentNumberMismatch(this, node->identifier->name, node->identifier->name, 0);
  }
}

void TypeCheck::visitIntegerTypeNode(IntegerTypeNode* node) {
  if (node) {
    node->basetype = bt_integer;
    node->objectClassName = "";
  }
}

void TypeCheck::visitBooleanTypeNode(BooleanTypeNode* node) {
  if (node) {
    node->basetype = bt_boolean;
    node->objectClassName = "";
  }
}

void TypeCheck::visitObjectTypeNode(ObjectTypeNode* node) {
  if (node) {
    undefinedClass(this, node->identifier->name);

    node->basetype = bt_object;
    node->objectClassName = node->identifier->name;
  }
}

void TypeCheck::visitNoneNode(NoneNode* node) {
  if (node) {
    node->basetype = bt_none;
    node->objectClassName = "";
  }
}

void TypeCheck::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    node->basetype = bt_integer;
    node->objectClassName = "";
}

void TypeCheck::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    node->basetype = bt_boolean;
    node->objectClassName = "";
}

void TypeCheck::visitIdentifierNode(IdentifierNode* node) {
  // do nothing, info from here has already been taken.
}

void TypeCheck::visitIntegerNode(IntegerNode* node) {
  // do nothing, info from here has already been taken.
}


/* The following functions are used to print the Symbol Table,
 * given that no typeErrors were thrown while building said table. */

std::string genIndent(int indent) {
  std::string string = std::string("");
  for (int i = 0; i < indent; i++)
    string += std::string(" ");
  return string;
}

std::string string(CompoundType type) {
  switch (type.baseType) {
    case bt_integer:
      return std::string("Integer");
    case bt_boolean:
      return std::string("Boolean");
    case bt_none:
      return std::string("None");
    case bt_object:
      return std::string("Object(") + type.objectClassName + std::string(")");
    default:
      return std::string("");
  }
}


void print(VariableTable variableTable, int indent) {
  std::cout << genIndent(indent) << "VariableTable {";
  if (variableTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (VariableTable::iterator it = variableTable.begin(); it != variableTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << string(it->second.type);
    std::cout << ", " << it->second.offset << ", " << it->second.size << "}";
    if (it != --variableTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(MethodTable methodTable, int indent) {
  std::cout << genIndent(indent) << "MethodTable {";
  if (methodTable.size() == 0) {
    std::cout << "}";
    return;
  }
  std::cout << std::endl;
  for (MethodTable::iterator it = methodTable.begin(); it != methodTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    std::cout << genIndent(indent + 4) << string(it->second.returnType) << "," << std::endl;
    std::cout << genIndent(indent + 4) << it->second.localsSize << "," << std::endl;
    print(*it->second.variables, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --methodTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}";
}

void print(ClassTable classTable, int indent) {
  std::cout << genIndent(indent) << "ClassTable {" << std::endl;
  for (ClassTable::iterator it = classTable.begin(); it != classTable.end(); it++) {
    std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
    if (it->second.superClassName != "")
      std::cout << genIndent(indent + 4) << it->second.superClassName << "," << std::endl;
    print(*it->second.members, indent + 4);
    std::cout << "," << std::endl;
    print(*it->second.methods, indent + 4);
    std::cout <<std::endl;
    std::cout << genIndent(indent + 2) << "}";
    if (it != --classTable.end())
      std::cout << ",";
    std::cout << std::endl;
  }
  std::cout << genIndent(indent) << "}" << std::endl;
}

void print(ClassTable classTable) {
  print(classTable, 0);
}