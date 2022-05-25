%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "ast.hpp"
    
    #define YYDEBUG 1
    #define YYINITDEPTH 10000

    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
    
%}


%define parse.error verbose

%token t_print
%token t_return
%token t_if
%token t_else
%token t_while
%token t_new
%token t_equals
%token t_and
%token t_or
%token t_not
%token t_extends
%token t_do
%token t_true
%token t_false
%token ';'
%token ','
%token t_arrow
%token '{'
%token '}'
%token '('
%token ')'
%token '+'
%token '-'
%token '*'
%token '/'
%token t_geq
%token '>'
%token '='
%token unary_minus
%token t_id
%token t_int_type
%token t_bool_type
%token t_none_type
%token t_number

%left t_or
%left t_and
%left '>' t_geq t_equals
%left '+' '-'
%left '*' '/'
%precedence t_not unary_minus

%type <type_ptr> Type
%type <expression_ptr> Expression
%type <expression_ptr> MethodCallInput
%type <statement_list_ptr> Block
%type <statement_list_ptr> MethodBodyList
%type <expression_list_ptr> MethodCallInputs
%type <expression_list_ptr> MethodCallInputsRest
%type <methodcall_ptr> MethodCall
%type <statement_ptr> Statement
%type <returnstatement_ptr> MethodBodyReturn
%type <parameter_ptr> Parameter
%type <parameter_list_ptr> ParametersRest
%type <parameter_list_ptr> Parameters
%type <identifier_ptr> MethodName
%type <identifier_list_ptr> NesMethodName
%type <identifier_ptr> MemberName
%type <identifier_ptr> ClassName
%type <identifier_list_ptr> MemberNames
%type <method_list_ptr> MethodList
%type <declaration_list_ptr> DeclarationList
%type <class_ptr> Class
%type <class_list_ptr> ClassList
%type <program_ptr> Start
%type <identifier_ptr> first_id
%type <integerliteral_ptr> t_number

%%
Start                 : ClassList Class
                          { $1->push_back($2); $$ = new ProgramNode($1); astRoot = $$; }
                      ;


ClassList             : ClassList Class
                          { $$ = $1; $$->push_back($2); }
                      | %empty
                          { $$ = new std::list<ClassNode*>(); }
                      ;

Class                 : ClassName t_extends ClassName '{' DeclarationList MethodList '}'
                          { $$ = new ClassNode($1, $3, $5, $6); }
                      | ClassName '{' DeclarationList MethodList '}'
                          { $$ = new ClassNode($1, NULL, $3, $4); }
                      | ClassName t_extends ClassName '{' DeclarationList'}'
                          { $$ = new ClassNode($1, $3, $5, NULL); }
                      | ClassName '{' DeclarationList'}'
                          { $$ = new ClassNode($1, NULL, $3, NULL); }
                      | ClassName t_extends ClassName '{' MethodList '}'
                          { $$ = new ClassNode($1, $3, NULL, $5); }
                      | ClassName '{' MethodList '}'
                          { $$ = new ClassNode($1, NULL, NULL, $3); }
                      | ClassName t_extends ClassName '{' '}'    
                          { $$ = new ClassNode($1, $3, NULL, NULL); }
                      | ClassName '{'  '}'
                          { $$ = new ClassNode($1, NULL, NULL, NULL); }
                      ;

DeclarationList       : DeclarationList Type MemberName MemberNames ';'
                          { $$ = $1; $4->push_front($3); $$->push_back(new DeclarationNode($2, $4)); }
                      | Type MemberName MemberNames ';'
                          { $$ = new std::list<DeclarationNode*>(); $3->push_front($2); $$->push_back(new DeclarationNode($1, $3)); }
                      ;

MethodList            : MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList MethodBodyReturn '}' 
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode($9, $10, $11))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList MethodBodyReturn '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode($8, $9, $10))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList MethodBodyReturn '}' 
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode(NULL, $9, $10))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList MethodBodyReturn '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode(NULL, $8, $9))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyReturn '}'
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode($9, NULL, $10))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyReturn '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode($8, NULL, $9))); }                      
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList '}' 
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode($9, $10, NULL))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode($8, $9, NULL))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList '}' 
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode($9, NULL, NULL))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode($8, NULL, NULL))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList '}' 
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode(NULL, $9, NULL))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode(NULL, $8, NULL))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyReturn '}'
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode(NULL, NULL, $9))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyReturn '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode(NULL, NULL, $8))); }
                      | MethodList MethodName '(' Parameters ')' t_arrow Type '{'  '}'
                          { $$ = $1; $$->push_back(new MethodNode($2, $4, $7, new MethodBodyNode(NULL, NULL, NULL))); }
                      | MethodName '(' Parameters ')' t_arrow Type '{' '}'
                          { $$ = new std::list<MethodNode*>(); $$->push_back(new MethodNode($1, $3, $6, new MethodBodyNode(NULL, NULL, NULL))); }
                      ;

MemberNames           : ',' first_id MemberNames
                          { $$ = $3; $$->push_front($2); }
                      | %empty
                          { $$ = new std::list<IdentifierNode*>(); }
                      ;

NesMethodName         : first_id '.' first_id
                          { $$ = new std::list<IdentifierNode*>(); $$->push_back($1); $$->push_back($3); }
                      | first_id t_arrow first_id
                          { $$ = new std::list<IdentifierNode*>(); $$->push_back($1); $$->push_back($3); }
                      ;

Parameters            : Parameter ParametersRest
                          { $$ = $2; $$->push_front($1); }
                      | %empty
                          { $$ = new std::list<ParameterNode*>(); }
                      ;

ParametersRest        : ',' Parameter ParametersRest
                          { $$ = $3; $$->push_front($2); }
                      | %empty
                          { $$ = new std::list<ParameterNode*>(); }
                      ;

Parameter             : Type first_id
                          { $$ = new ParameterNode($1, $2); }
                      ;

Type                  : t_int_type
                          { $$ = new IntegerTypeNode(); }
                      | t_bool_type                              
                          { $$ = new BooleanTypeNode(); }
                      | t_none_type                              
                          { $$ = new NoneNode(); }
                      | first_id                                 
                          { $$ = new ObjectTypeNode($1); }
                      ;

MethodBodyList        : MethodBodyList Statement                 
                          { $$ = $1; $$->push_back($2); }
                      | Statement                                
                          { $$ = new std::list<StatementNode*>(); $$->push_back($1); }
                      ;

MethodBodyReturn      : t_return Expression ';'                  
                          { $$ = new ReturnStatementNode($2); }
                      ;

Statement             : first_id '=' Expression ';'
                          { $$ = new AssignmentNode($1, NULL, $3); }
                      | first_id '.' first_id '=' Expression ';'
                          { $$ = new AssignmentNode($1, $3, $5); }
                      | first_id t_arrow first_id '=' Expression ';'
                          { $$ = new AssignmentNode($1, $3, $5); }
                      | MethodCall ';'                           
                          { $$ = new CallNode($1); }
                      | t_if Expression '{' Statement Block '}'  
                          { $5->push_front($4); $$ = new IfElseNode($2, $5, NULL); }
                      | t_if Expression '{' Statement Block '}' t_else '{' Statement Block '}'
                          { $5->push_front($4); $10->push_front($9); $$ = new IfElseNode($2, $5, $10); }
                      | t_while Expression '{' Statement Block '}'
                          { $5->push_front($4); $$ = new WhileNode($2, $5); }
                      | t_do '{' Statement Block '}' t_while '(' Expression ')' ';'
                          { $4->push_front($3); $$ = new DoWhileNode($4, $8); }
                      | t_print Expression ';'
                          { $$ = new PrintNode($2); }
                      ;

MethodCallInputs      : MethodCallInput MethodCallInputsRest     
                          { $$ = $2; $$->push_front($1); }
                      | %empty                                   
                          { $$ = new std::list<ExpressionNode*>(); }
                      ;

MethodCallInputsRest  : ',' MethodCallInput MethodCallInputsRest 
                          { $$ = $3; $$->push_front($2); }
                      | %empty                                   
                          { $$ = new std::list<ExpressionNode*>(); }
                      ;

MethodCallInput       : Expression        { $$ = $1; }
                      ;

Block                 : Statement Block                          
                            { $$ = $2; $$->push_front($1); }
                      | %empty                                   
                            { $$ = new std::list<StatementNode*>(); }
                      ;

Expression            : Expression '+' Expression                
                          { $$ = new PlusNode($1, $3); }
                      | Expression '-' Expression                
                          { $$ = new MinusNode($1, $3); }
                      | Expression '*' Expression                
                          { $$ = new TimesNode($1, $3); }
                      | Expression '/' Expression                
                          { $$ = new DivideNode($1, $3); }
                      | Expression '>' Expression                
                          { $$ = new GreaterNode($1, $3); }
                      | Expression t_geq Expression              
                          { $$ = new GreaterEqualNode($1, $3); }
                      | Expression t_equals Expression           
                          { $$ = new EqualNode($1, $3); }
                      | Expression t_and Expression
                          { $$ = new AndNode($1, $3); }
                      | Expression t_or Expression
                          { $$ = new OrNode($1, $3); }
                      | t_not Expression
                          { $$ = new NotNode($2); }
                      | '-' Expression %prec unary_minus
                          { $$ = new NegationNode($2); }
                      | first_id
                          { $$ = new VariableNode($1); }
                      | first_id '.' first_id
                          { $$ = new MemberAccessNode($1, $3); }
                      | first_id t_arrow first_id
                          { $$ = new MemberAccessNode($1, $3); }
                      | MethodCall
                          { $$ = $1; }
                      | '(' Expression ')'
                          { $$ = $2; }
                      | t_number
                          { $$ = new IntegerLiteralNode(new IntegerNode(yylval.base_int)); }
                      | t_true
                          { $$ = new BooleanLiteralNode(new IntegerNode(1)); }
                      | t_false
                          { $$ = new BooleanLiteralNode(new IntegerNode(0)); }
                      | t_new ClassName
                          { $$ = new NewNode($2, NULL); }
                      | t_new ClassName '(' MethodCallInputs ')'
                          { $$ = new NewNode($2, $4); }
                      ;

MethodCall            : MethodName '(' MethodCallInputs ')'
                          { $$ = new MethodCallNode($1, NULL, $3); }
                      | NesMethodName '(' MethodCallInputs ')'
                          { $$ = new MethodCallNode($1->front(), $1->back(), $3); }
                      ;

ClassName             : first_id      { $$ = $1; }
                      ;

MemberName            : first_id      { $$ = $1; }
                      ;

MethodName            : first_id      { $$ = $1; }
                      ;

first_id              : t_id
                          { $$ = new IdentifierNode(yylval.base_char_ptr); }
                      ;
%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(1);
}
