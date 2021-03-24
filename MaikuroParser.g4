parser grammar MaikuroParser;

options {
    tokenVocab=MaikuroLexer;
}

sourceFile
    : fileBody
    ;

fileBody
    : annotationList* packageClause? importDeclaration* (fileDeclarations | statementList)*
    ;

fileDeclarations
    :
    classDeclaration
    | functionDeclaration
    | aliasDeclaration
    ;

packageName
	: IDENTIFIER ('.' IDENTIFIER)* ('.' TYPE_IDENTIFIER)?
	;

packageClause
    : PACKAGE packageName ';'
    ;

importDeclaration
    : IMPORT importClouse ';'
    ;

importClouse
    : packageName importAlias?
    ;

importAlias
    : AS ('.' | IDENTIFIER)
    ;

classDeclaration
    :   annotationList* CLASS TYPE_IDENTIFIER superClass? superInterfaces? classBody
    ;

superClass
    :   EXTENDS TYPE_IDENTIFIER
    ;

superInterfaces
    :   IMPLEMENTS interfaceList
    ;

interfaceList
    :   TYPE_IDENTIFIER (',' TYPE_IDENTIFIER)*
    ;

classBody
    : '{' (propertyDeclaration | methodDeclaration | annotationList)* '}'
    ;

methodModifier
	:	PUBLIC
	|	PROTECTED
	|	PRIVATE
	|	ABSTRACT
	|	STATIC
	|	FINAL
	;

packageMemberVisibility
    : PUBLIC
    | PROTECTED
    | PRIVATE
    ;

methodDeclaration
    : annotationList* methodModifier? functionDeclaration
    ;

propertyDeclaration
    : packageMemberVisibility? type IDENTIFIER  ('=' expression)? ';'
    ;

functionStart
    : FUN IDENTIFIER formalParameters returnType?
    ;

functionHeader
    : functionStart ';'
    ;

functionDeclaration
    : annotationList* functionStart functionBody
    ;

functionBody
    : block;

returnType
    : ':' type
    ;

block
    : '{' statementList* '}'
    ;

statementList
    : statement
    | variableDeclarationList ';'
    ;

statement
    : blockLabel=block
    | IF parExpression statement (ELSE statement)?
    | UNLESS parExpression statement (ELSE statement)?
    | FOR '(' forControl ')' statement
    | FOREACH '(' foreachControl ')' statement
    | LOOP parExpression? block
    | UNTIL parExpression block
    | WHILE parExpression block
    | DO statement WHILE parExpression ';'
    | TRY block (catchClause+ finallyBlock? | finallyBlock)
    | SWITCH parExpression '{' switchBlockStatementGroup* switchLabel* '}'
    | RETURN expression? ';'
    | THROW expression ';'
    | BREAK IDENTIFIER? ';'
    | CONTINUE IDENTIFIER? ';'
    | statementExpression=expression ';'
    ;

switchBlockStatementGroup
    : switchLabel+ statementList+
    ;

switchLabel
    : CASE (constantExpression=expression | enumConstantName=IDENTIFIER) ':'
    | DEFAULT ':'
    ;

forControl
    : forInit? ';' expression? ';' forUpdate=expressionList?
    ;

forInit
    : variableDeclarationList
    | expressionList
    ;

foreachControl
    : expression 'as' IDENTIFIER ('=>' IDENTIFIER)?
    ;


catchClause
    : CATCH '(' catchType IDENTIFIER ')' block
    ;

catchType
    : TYPE_IDENTIFIER ('|' TYPE_IDENTIFIER)*
    ;

finallyBlock
    : FINALLY block
    ;

/*
Type definitions
*/

typeDeclaration
    : type
    | typeUnion
    ;

type:
    TYPE_IDENTIFIER
    | TYPE_IDENTIFIER arrayDeclaration
    | type '?'
    ;

arrayDeclaration
    : '[]'
    | '[' NUMBER_LITERAL? ']'
    ;

typeUnion
    : type ('|' typeUnion)*
    ;

aliasDeclaration
    :
    annotationList* packageMemberVisibility? 'alias' typeDeclaration '=' typeDeclaration ';'
    ;


literal
    : NULL_LITERAL
    | BOOL_LITERAL
    | CHAR_LITERAL
    | NUMBER_LITERAL
    | STRING_LITERAL
    ;

variableDeclaration
    : variableDeclarationName ((',' | '=') variableDeclaration)*

    ;

variableDeclarationList
    : annotationList* 'var' variableDeclaration ('=' expression (',' expression)*)?
    ;

variableName
    : IDENTIFIER
    | '@' IDENTIFIER
    ;

variableDeclarationName
    : type? variableName
    ;

parExpression
    : '(' expression ')'
    ;

expressionList
    : expression (',' expression)*
    ;

methodCall
    : IDENTIFIER namedArguments
    | THIS namedArguments
    | SUPER namedArguments
    ;

expression
    : primary
    | expression bop='.'
        ( IDENTIFIER
        | methodCall
        | THIS
        | SUPER
        )
    | methodCall
    | newDeclarator
    | MATCH parExpression '{' matchExpression+ '}'
    | expression postfix=('++' | '--')
    | prefix=('+'|'-'|'++'|'--') expression
    | prefix=('~'|'!') expression
    | expression bop=('*'|'/'|'%') expression
    | expression bop=('+'|'-') expression
    | expression ('<' '<' | '>' '>' '>' | '>' '>') expression
    | expression bop=('<=' | '>=' | '>' | '<') expression
    | expression bop=('==' | '!=') expression
    | expression bop='&' expression
    | expression bop='^' expression
    | expression bop='|' expression
    | expression bop='&&' expression
    | expression bop='||' expression
    | <assoc=right> expression bop='?' expression ':' expression
    | <assoc=right> expression
      bop=('=' | '+=' | '-=' | '*=' | '/=' | '&=' | '|=' | '^=' | '>>=' | '>>>=' | '<<=' | '%=')
      expression
    ;

primary
    : '(' expression ')'
    | THIS
    | SUPER
    | IDENTIFIER
    | TYPE_IDENTIFIER
    | literal
    | variableName
    ;

matchExpression
    : (expressionList | DEFAULT) '=>' expression ','
    ;

newDeclarator
    : NEW type namedArguments
    ;

arguments
    : '(' expressionList? ')'
    ;

namedArguments
    : '(' namedArgument? (',' namedArgument)* ')'
    ;

namedArgument
    : (IDENTIFIER ':')? expression
    ;

formalParameters
    : '(' formalParameterList? ')'
    ;

formalParameterList
    : formalParameter (',' formalParameter)* (',' lastFormalParameter)?
    | lastFormalParameter
    ;

formalParameter
    : type? IDENTIFIER
    ;

lastFormalParameter
    : type? '...' IDENTIFIER
    ;

annotation
    : TYPE_IDENTIFIER namedArguments?
    ;

annotationList
    : '#[' annotation (',' annotation)* ']'
    ;