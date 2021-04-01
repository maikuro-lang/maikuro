#pragma once

#include "common.h"
#include "Statement.h"
#include "Type.h"
#include "Annotation.h"
#include "Argument.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"


namespace MaikuroAst {
    class Expression;
    typedef shared_ptr<MaikuroAst::Expression>        ExpressionPtr;
    typedef vector<MaikuroAst::ExpressionPtr>         ExpressionPtrVec;

    class VariableName : public MaikuroAst::AstNode {
     public:
        VariableName(TokenPtr atSign, IdentifierPtr identifier);

        explicit VariableName(MaikuroParser::VariableNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr      _atSign;
        IdentifierPtr _identifier;
    };

    typedef shared_ptr<VariableName>                  VariableNamePtr;
    typedef vector<VariableNamePtr>                   VariableNamePtrVec;

    class VariableNameDeclaration : public MaikuroAst::AstNode {
     public:
        VariableNameDeclaration(TypeDeclarationPtr typeDeclaration, VariableNamePtr variableName);

        explicit VariableNameDeclaration(MaikuroParser::VariableDeclarationNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TypeDeclarationPtr _typeDeclaration;
        VariableNamePtr                _variableName;
    };

    typedef shared_ptr<VariableNameDeclaration>       VariableNameDeclarationPtr;
    typedef vector<VariableNameDeclarationPtr>        VariableNameDeclarationPtrVec;

    class VariableDeclarationExpression : public MaikuroAst::AstNode {
     public:
        VariableDeclarationExpression(TokenPtr semicolon, TokenPtr assign, ExpressionPtrVec expressions, TokenPtrVec commas);

        explicit VariableDeclarationExpression(MaikuroParser::VariableDeclarationExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr         _semicolon;
        TokenPtr         _assign;
        ExpressionPtrVec _expressions;
        TokenPtrVec      _commas;
    };

    typedef shared_ptr<VariableDeclarationExpression> VariableDeclarationExpressionPtr;
    typedef vector<VariableDeclarationExpressionPtr>  VariableDeclarationExpressionPtrVec;

    class VariableDeclaration : public MaikuroAst::Statement {
     public:
        VariableDeclaration(
            AnnotationsPtrVec annotations,
            TokenPtr var,
            VariableNameDeclarationPtrVec variableNames,
            TokenPtrVec separators,
            VariableDeclarationExpressionPtr expressions,
            TokenPtr semicolon
        );

        explicit VariableDeclaration(MaikuroParser::VariableDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        AnnotationsPtrVec    _annotations;
        TokenPtr             _var;
        VariableNameDeclarationPtrVec    _variableNames;
        TokenPtrVec          _separators;
        VariableDeclarationExpressionPtr _expressions;
    };

    typedef shared_ptr<VariableDeclaration>           VariableDeclarationPtr;
    typedef vector<VariableDeclarationPtr>            VariableDeclarationPtrVec;
}

