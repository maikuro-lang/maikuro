parser grammar MaikuroParser;

options {
    tokenVocab=MaikuroLexer;
}

sourceFile
    :
    annotations*
    packageDeclaration?
    importDeclaration*
    statement*
    ;

packageName
	: IDENTIFIER ('.' IDENTIFIER)* ('.' TYPE_IDENTIFIER)?
	;

packageDeclaration
    : PACKAGE packageName ';'
    ;

importDeclaration
    : IMPORT packageName (AS ('.' | TYPE_IDENTIFIER))? ';'
    ;

classDeclaration
    :   annotations* CLASS TYPE_IDENTIFIER (superClass)? superInterfaces? classBody
    ;

superClass
    :   EXTENDS TYPE_IDENTIFIER
    ;

superInterfaces
    :   IMPLEMENTS TYPE_IDENTIFIER (',' TYPE_IDENTIFIER)*
    ;

classBody
    : '{' classMember* '}'
    ;

classMember
    : propertyDeclaration
    | methodDeclaration
    | annotations
    ;

visibilityModifier
	:	PUBLIC
	|	PROTECTED
	|	PRIVATE
	|	ABSTRACT
	|	STATIC
	|	FINAL
	;

methodDeclaration
    : annotations* visibilityModifier? functionHeader block
    ;

propertyDeclaration
    : annotations* visibilityModifier? typeDeclaration IDENTIFIER  ('=' expression)? ';'
    ;

functionHeader
    : FUN IDENTIFIER formalParameters (':' type)?
    ;

functionDeclaration
    : annotations* functionHeader block
    ;

block
    : '{' statement* '}'
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
    | DO block WHILE parExpression ';'
    | TRY block (catchClause+ finallyBlock? | finallyBlock)
    | SWITCH parExpression '{' switchBlockStatementGroup* switchLabel* '}'
    | RETURN expression? ';'
    | THROW expression ';'
    | BREAK NUMBER_LITERAL? ';'
    | CONTINUE NUMBER_LITERAL? ';'
    | statementExpression=expression ';'
    | variableDeclaration
    | classDeclaration
    | functionDeclaration
    | aliasDeclaration
    ;

switchBlockStatementGroup
    : switchLabel+ statement+
    ;

switchLabel
    : CASE (constantExpression=expression | enumConstantName=IDENTIFIER) ':'
    | DEFAULT ':'
    ;

forControl
    : (variableDeclaration | expressionList)? ';' expression? ';' forUpdate=expressionList?
    ;

foreachControl
    : expression 'as' IDENTIFIER ('=>' IDENTIFIER)?
    ;

catchClause
    : CATCH '(' TYPE_IDENTIFIER ('|' TYPE_IDENTIFIER)* IDENTIFIER? ')' block
    ;

finallyBlock
    : FINALLY block
    ;

/*
Type definitions
*/

typeDeclaration
    : type ('|' type)*
    ;

type
    : TYPE_IDENTIFIER ('[' NUMBER_LITERAL? ']')?  '?'?
    ;

aliasDeclaration
    :
    annotations* visibilityModifier? 'alias' type '=' typeDeclaration ';'
    ;

variableDeclaration
    : annotations* 'var' variableDeclarationName (var_sep+=('='|',') variableDeclarationName)* variableDeclarationExpression
    ;

variableDeclarationExpression
    :  (';' | ('=' expression (',' expression)*) ';')
    ;

variableName
    : '@'? IDENTIFIER
    ;

variableDeclarationName
    : typeDeclaration? variableName
    ;

parExpression
    : '(' expression ')'
    ;

expressionList
    : expression (',' expression)*
    ;

methodCall
    : IDENTIFIER arguments
    | THIS arguments
    | SUPER arguments
    ;

expression
    : primary
    | variableName
    | parExpression
    | expression bop='.' dotExpression
    | methodCall
    | newDeclarator
    | MATCH parExpression '{' (matchExpressionCase ',')* (matchExpressionCase ','?) '}'
    | expression suffix=('++' | '--')
    | prefix=('+'|'-'|'++'|'--') expression
    | prefix=('~'|'!') expression
    | expression bop=('*'|'/'|'%') expression
    | expression bop=('+'|'-') expression
    | expression bop=('<<' | '>>>' | '>>') expression
    | expression bop=('<=' | '>=' | '>' | '<') expression
    | expression bop=('==' | '!=') expression
    | expression bop='&' expression
    | expression bop='^' expression
    | expression bop='|' expression
    | expression bop='&&' expression
    | expression bop='||' expression
    | <assoc=right> expression bop='?' expression? ':' expression
    | <assoc=right> expression
      bop=('=' | '+=' | '-=' | '*=' | '/=' | '&=' | '|=' | '^=' | '>>=' | '>>>=' | '<<=' | '%=')
      expression
    ;

dotExpression
    : IDENTIFIER
    | methodCall
    | THIS
    | SUPER
    ;

primary
    : THIS
    | SUPER
    | IDENTIFIER
    | TYPE_IDENTIFIER
    | NULL_LITERAL
    | BOOL_LITERAL
    | CHAR_LITERAL
    | NUMBER_LITERAL
    | STRING_LITERAL
    ;

matchExpressionCase
    : (expressionList | DEFAULT) '=>' expression
    ;

newDeclarator
    : NEW type arguments
    ;

arguments
    : '(' argument? (',' argument)* ')'
    ;

argument
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
    : TYPE_IDENTIFIER arguments?
    ;

annotations
    : '#[' annotation (',' annotation)* ']'
    ;