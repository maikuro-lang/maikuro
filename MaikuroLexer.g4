lexer grammar MaikuroLexer;

// Keywords
PACKAGE : 'package';
IMPORT : 'import';
AS : 'as';
CLASS : 'class';
INTERFACE : 'interface';
EXTENDS : 'extends';
IMPLEMENTS : 'implements';
FUN : 'fun';
VAR : 'var';
CONST : 'const';
IF : 'if';
UNLESS : 'unless';
ELSE : 'else';
ELSEIF : 'elseif';
ENUM : 'enum';
NEW : 'new';
FOR : 'for';
FOREACH : 'foreach';
LOOP : 'loop';
UNTIL : 'until';
WHILE : 'while';
SWITCH : 'switch';
MATCH : 'match';
CASE : 'case';
DEFAULT : 'default';
DO : 'do';
PUBLIC : 'public';
PROTECTED : 'protected';
PRIVATE : 'private';
ABSTRACT : 'abstract';
STATIC : 'static';
FINAL : 'final';
ALIAS : 'alias';
THIS : 'this';
SUPER : 'super';
RETURN : 'return';
THROW : 'throw';
BREAK : 'break';
CONTINUE : 'continue';
TRY: 'try';
CATCH: 'catch';
FINALLY: 'finally';


// Literals

NULL_LITERAL : 'null';
BOOL_LITERAL
    : 'true'
    | 'false'
    ;

NUMBER_LITERAL: (
        ('+' | '-')?
        ('0b' [01][01_]* | '0o' [0-7][0-7_]* | '0x' [a-fA-F0-9][a-fA-F0-9_]* | [0-9][0-9_]*)
        ('.'? [0-9][0-9_]*)?
        ('e' ('+' | '-')? [0-9][0-9_]*)?
        ('_' ('i' | 'u' | 'f')('8' | '16' | '32' | '64'))?
    )
    ;

CHAR_LITERAL: '\'' (. | ESCAPE_SEQUENCE_CHAR) '\'';
STRING_LITERAL: '"' (~[\\"] | ESCAPE_SEQUENCE_STRING)*'"';

ESCAPE_SEQUENCE_CHAR
    : '\\\''
    | ESCAPE_SEQUENCE
    ;

ESCAPE_SEQUENCE_STRING
    : '\\"'
    | ESCAPE_SEQUENCE
    | ('\\' (('0' .. '9') ('0' .. '9')? ('0' .. '9')?))
    | ('\\x' (HEX_LITERAL HEX_LITERAL?))
    ;

ESCAPE_SEQUENCE
    : '\\\\'         // backslash
    | '\\a'         // alert
    | '\\b'         // backspace
    | '\\e'         // escape
    | '\\f'         // form feed
    | '\\n'         // newline
    | '\\r'         // carriage return
    | '\\t'         // tab
    | '\\v'         // veritical tab
    | '\\u' HEX_LITERAL HEX_LITERAL HEX_LITERAL HEX_LITERAL
    | '\\u{' (HEX_LITERAL HEX_LITERAL? HEX_LITERAL? HEX_LITERAL? HEX_LITERAL? HEX_LITERAL?) '}'
    ;

ARRAY_TYPE : '[]';
ATTRIBUTE_PREFIX : '#[';

// Separators

LPAREN:             '(';
RPAREN:             ')';
LBRACE:             '{';
RBRACE:             '}';
LBRACK:             '[';
RBRACK:             ']';
SEMI:               ';';
COMMA:              ',';
DOT:                '.';

// Operators

ASSIGN:             '=';
GT:                 '>';
LT:                 '<';
BANG:               '!';
TILDE:              '~';
QUESTION:           '?';
COLON:              ':';
EQUAL:              '==';
LE:                 '<=';
GE:                 '>=';
NOTEQUAL:           '!=';
AND:                '&&';
OR:                 '||';
INC:                '++';
DEC:                '--';
ADD:                '+';
SUB:                '-';
MUL:                '*';
DIV:                '/';
BITAND:             '&';
BITOR:              '|';
CARET:              '^';
MOD:                '%';

ADD_ASSIGN:         '+=';
SUB_ASSIGN:         '-=';
MUL_ASSIGN:         '*=';
DIV_ASSIGN:         '/=';
AND_ASSIGN:         '&=';
OR_ASSIGN:          '|=';
XOR_ASSIGN:         '^=';
MOD_ASSIGN:         '%=';
LSHIFT_ASSIGN:      '<<=';
RSHIFT_ASSIGN:      '>>=';
URSHIFT_ASSIGN:     '>>>=';

DOUBLE_ARROW:       '=>';
ARROW:              '->';
COLONCOLON:         '::';

// Additional symbols not defined in the lexical specification

AT:                 '@';
ELLIPSIS:           '...';

// Whitespace and comments

WS:                 [ \t\r\n\u000C]+ -> channel(HIDDEN);
COMMENT:            '/*' .*? '*/'    -> channel(HIDDEN);
LINE_COMMENT:       '//' ~[\r\n]*    -> channel(HIDDEN);


TYPE_IDENTIFIER : UPPERCASE_LETTER IDENTIFIER*;
IDENTIFIER      : LETTER LETTER_OR_DIGIT*;

fragment LETTER_OR_DIGIT
    : LETTER
    | [0-9]
    ;

fragment UPPERCASE_LETTER
   : [A-Z$]
    | ~[\u0000-\u007F\uD800-\uDBFF]
    | [\uD800-\uDBFF] [\uDC00-\uDFFF]
    ;

fragment LETTER
    : [a-zA-Z$_]
    | ~[\u0000-\u007F\uD800-\uDBFF]
    | [\uD800-\uDBFF] [\uDC00-\uDFFF]
    ;

fragment HEX_LITERAL: [a-fA-F0-9];