#pragma once

#include "common.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;

    class Token;
    typedef vector<shared_ptr<Token>> TokenPtrVec;

    class AstNode {
     public:
        enum NodeType {
            ANNOTATION,
            ANNOTATIONS,
            ARGUMENT,
            ARGUMENTS,
            CATCH_CLAUSE,
            CLASS_BODY,
            CLASS_MEMBER,
            ANNOTATION_MEMBER,
            METHOD_DECLARATION,
            PROPERTY_DECLARATION,
            EXPRESSION_LIST,
            FINALLY_BLOCK,
            FOR_CONTROL,
            FOREACH_CONTROL,
            FORMAL_PARAMETER,
            FORMAL_PARAMETER_LIST,
            FORMAL_PARAMETERS,
            FUNCTION_HEADER,
            LITERAL,
            BOOL_LITERAL,
            CHAR_LITERAL,
            IDENTIFIER,
            NULL_LITERAL,
            NUMBER_LITERAL,
            STRING_LITERAL,
            TYPE_IDENTIFIER,
            VISIBILITY_MODIFIER,
            MATCH_EXPRESSION_CASE,
            METHOD_CALL,
            PACKAGE_NAME,
            SOURCE_FILE,
            STATEMENT,
            ALIAS_DECLARATION,
            BLOCK,
            CLASS_DECLARATION,
            EXPRESSION,
            EXPRESSION_STATEMENT,
            BOP_EXPRESSION,
            DOT_EXPRESSION,
            MATCH_EXPRESSION,
            METHOD_CALL_EXPRESSION,
            NEW_DECLARATOR_EXPRESSION,
            PAR_EXPRESION,
            PREFIX_EXPRESSION,
            PRIMARY_EXPRESSION,
            SUFFIX_EXPRESSION,
            TERNARY_EXPRESSION,
            VARIABLE_NAME_EXPRESSION,
            FOREACH_STATEMENT,
            FOR_STATEMENT,
            FUNCTION_DECLARATION,
            IF_STATEMENT,
            UNLESS_STATEMENT,
            IMPORT_DECLARATION,
            PACKAGE_DECLARATION,
            SWITCH_STATEMENT,
            TOKEN_EXPRESSION_STATEMENT,
            RETURN_STATEMENT,
            THROW_STATEMENT,
            TOKEN_NUMBER_LITERAL_STATEMENT,
            BREAK_STATEMENT,
            CONTINUE_STATEMENT,
            TRY_STATEMENT,
            VARIABLE_DECLARATION,
            WHILE_STATEMENT,
            DO_WHILE_STATEMENT,
            LOOP_STATEMENT,
            UNTIL_STATEMENT,
            SUPER_CLASS,
            SUPER_INTERFACES,
            SWITCH_BLOCK_STATEMENT_GROUP,
            SWITCH_LABEL,
            TOKEN,
            TYPE,
            TYPE_DECLARATION,
            VARIABLE_DECLARATION_EXPRESSION,
            VARIABLE_NAME,
            VARIABLE_NAME_DECLARATION,
        };

        virtual NodeType getNodeType() = 0;

        virtual string getNodeName() {
            switch (getNodeType()) {
                case NodeType::ANNOTATION:
                    return "ANNOTATION";
                case NodeType::ANNOTATIONS:
                    return "ANNOTATIONS";
                case NodeType::ARGUMENT:
                    return "ARGUMENT";
                case NodeType::ARGUMENTS:
                    return "ARGUMENTS";
                case NodeType::CATCH_CLAUSE:
                    return "CATCH_CLAUSE";
                case NodeType::CLASS_BODY:
                    return "CLASS_BODY";
                case NodeType::CLASS_MEMBER:
                    return "CLASS_MEMBER";
                case NodeType::ANNOTATION_MEMBER:
                    return "ANNOTATION_MEMBER";
                case NodeType::METHOD_DECLARATION:
                    return "METHOD_DECLARATION";
                case NodeType::PROPERTY_DECLARATION:
                    return "PROPERTY_DECLARATION";
                case NodeType::EXPRESSION_LIST:
                    return "EXPRESSION_LIST";
                case NodeType::FINALLY_BLOCK:
                    return "FINALLY_BLOCK";
                case NodeType::FOR_CONTROL:
                    return "FOR_CONTROL";
                case NodeType::FOREACH_CONTROL:
                    return "FOREACH_CONTROL";
                case NodeType::FORMAL_PARAMETER:
                    return "FORMAL_PARAMETER";
                case NodeType::FORMAL_PARAMETER_LIST:
                    return "FORMAL_PARAMETER_LIST";
                case NodeType::FORMAL_PARAMETERS:
                    return "FORMAL_PARAMETERS";
                case NodeType::FUNCTION_HEADER:
                    return "FUNCTION_HEADER";
                case NodeType::LITERAL:
                    return "LITERAL";
                case NodeType::BOOL_LITERAL:
                    return "BOOL_LITERAL";
                case NodeType::CHAR_LITERAL:
                    return "CHAR_LITERAL";
                case NodeType::IDENTIFIER:
                    return "IDENTIFIER";
                case NodeType::NULL_LITERAL:
                    return "NULL_LITERAL";
                case NodeType::NUMBER_LITERAL:
                    return "NUMBER_LITERAL";
                case NodeType::STRING_LITERAL:
                    return "STRING_LITERAL";
                case NodeType::TYPE_IDENTIFIER:
                    return "TYPE_IDENTIFIER";
                case NodeType::VISIBILITY_MODIFIER:
                    return "VISIBILITY_MODIFIER";
                case NodeType::MATCH_EXPRESSION_CASE:
                    return "MATCH_EXPRESSION_CASE";
                case NodeType::METHOD_CALL:
                    return "METHOD_CALL";
                case NodeType::PACKAGE_NAME:
                    return "PACKAGE_NAME";
                case NodeType::SOURCE_FILE:
                    return "SOURCE_FILE";
                case NodeType::STATEMENT:
                    return "STATEMENT";
                case NodeType::ALIAS_DECLARATION:
                    return "ALIAS_DECLARATION";
                case NodeType::BLOCK:
                    return "BLOCK";
                case NodeType::CLASS_DECLARATION:
                    return "CLASS_DECLARATION";
                case NodeType::EXPRESSION:
                    return "EXPRESSION";
                case NodeType::EXPRESSION_STATEMENT:
                    return "EXPRESSION_STATEMENT";
                case NodeType::BOP_EXPRESSION:
                    return "BOP_EXPRESSION";
                case NodeType::DOT_EXPRESSION:
                    return "DOT_EXPRESSION";
                case NodeType::MATCH_EXPRESSION:
                    return "MATCH_EXPRESSION";
                case NodeType::METHOD_CALL_EXPRESSION:
                    return "METHOD_CALL_EXPRESSION";
                case NodeType::NEW_DECLARATOR_EXPRESSION:
                    return "NEW_DECLARATOR_EXPRESSION";
                case NodeType::PAR_EXPRESION:
                    return "PAR_EXPRESION";
                case NodeType::PREFIX_EXPRESSION:
                    return "PREFIX_EXPRESSION";
                case NodeType::PRIMARY_EXPRESSION:
                    return "PRIMARY_EXPRESSION";
                case NodeType::SUFFIX_EXPRESSION:
                    return "SUFFIX_EXPRESSION";
                case NodeType::TERNARY_EXPRESSION:
                    return "TERNARY_EXPRESSION";
                case NodeType::VARIABLE_NAME_EXPRESSION:
                    return "VARIABLE_NAME_EXPRESSION";
                case NodeType::FOREACH_STATEMENT:
                    return "FOREACH_STATEMENT";
                case NodeType::FOR_STATEMENT:
                    return "FOR_STATEMENT";
                case NodeType::FUNCTION_DECLARATION:
                    return "FUNCTION_DECLARATION";
                case NodeType::IF_STATEMENT:
                    return "IF_STATEMENT";
                case NodeType::UNLESS_STATEMENT:
                    return "UNLESS_STATEMENT";
                case NodeType::IMPORT_DECLARATION:
                    return "IMPORT_DECLARATION";
                case NodeType::PACKAGE_DECLARATION:
                    return "PACKAGE_DECLARATION";
                case NodeType::SWITCH_STATEMENT:
                    return "SWITCH_STATEMENT";
                case NodeType::TOKEN_EXPRESSION_STATEMENT:
                    return "TOKEN_EXPRESSION_STATEMENT";
                case NodeType::RETURN_STATEMENT:
                    return "RETURN_STATEMENT";
                case NodeType::THROW_STATEMENT:
                    return "THROW_STATEMENT";
                case NodeType::TOKEN_NUMBER_LITERAL_STATEMENT:
                    return "TOKEN_NUMBER_LITERAL_STATEMENT";
                case NodeType::BREAK_STATEMENT:
                    return "BREAK_STATEMENT";
                case NodeType::CONTINUE_STATEMENT:
                    return "CONTINUE_STATEMENT";
                case NodeType::TRY_STATEMENT:
                    return "TRY_STATEMENT";
                case NodeType::VARIABLE_DECLARATION:
                    return "VARIABLE_DECLARATION";
                case NodeType::WHILE_STATEMENT:
                    return "WHILE_STATEMENT";
                case NodeType::DO_WHILE_STATEMENT:
                    return "DO_WHILE_STATEMENT";
                case NodeType::LOOP_STATEMENT:
                    return "LOOP_STATEMENT";
                case NodeType::UNTIL_STATEMENT:
                    return "UNTIL_STATEMENT";
                case NodeType::SUPER_CLASS:
                    return "SUPER_CLASS";
                case NodeType::SUPER_INTERFACES:
                    return "SUPER_INTERFACES";
                case NodeType::SWITCH_BLOCK_STATEMENT_GROUP:
                    return "SWITCH_BLOCK_STATEMENT_GROUP";
                case NodeType::SWITCH_LABEL:
                    return "SWITCH_LABEL";
                case NodeType::TOKEN:
                    return "TOKEN";
                case NodeType::TYPE:
                    return "TYPE";
                case NodeType::TYPE_DECLARATION:
                    return "TYPE_DECLARATION";
                case NodeType::VARIABLE_DECLARATION_EXPRESSION:
                    return "VARIABLE_DECLARATION_EXPRESSION";
                case NodeType::VARIABLE_NAME:
                    return "VARIABLE_NAME";
                case NodeType::VARIABLE_NAME_DECLARATION:
                    return "VARIABLE_NAME_DECLARATION";
                default:
                    return "UNKNOWN";
            }
        }

        virtual int getLine() = 0;

        virtual string toString() = 0;

        virtual TokenPtrVec getTokens() = 0;
    };

    typedef shared_ptr<AstNode> AstNodePtr;
    typedef vector<AstNodePtr>  AstNodePtrVec;
}

