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
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class Expression;

    typedef shared_ptr<Expression> ExpressionPtr;
    typedef vector<ExpressionPtr>  ExpressionPtrVec;

    class VariableName : public AstNode {
     public:
        VariableName(TokenPtr atSign, IdentifierPtr identifier);

        explicit VariableName(MaikuroParser::VariableNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getAtSign() const;

        const IdentifierPtr& getIdentifier() const;

     private:
        TokenPtr      _atSign;
        IdentifierPtr _identifier;
    };

    typedef shared_ptr<VariableName> VariableNamePtr;
    typedef vector<VariableNamePtr>  VariableNamePtrVec;

    class VariableNameDeclaration : public AstNode {
     public:
        VariableNameDeclaration(TypeDeclarationPtr typeDeclaration, VariableNamePtr variableName);

        explicit VariableNameDeclaration(MaikuroParser::VariableDeclarationNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TypeDeclarationPtr& getTypeDeclaration() const;

        const VariableNamePtr& getVariableName() const;

     private:
        TypeDeclarationPtr _typeDeclaration;
        VariableNamePtr    _variableName;
    };

    typedef shared_ptr<VariableNameDeclaration> VariableNameDeclarationPtr;
    typedef vector<VariableNameDeclarationPtr>  VariableNameDeclarationPtrVec;

    class VariableDeclarationExpression : public AstNode {
     public:
        VariableDeclarationExpression(
            TokenPtr semicolon,
            TokenPtr assign,
            ExpressionPtrVec expressions,
            TokenPtrVec commas
        );

        explicit VariableDeclarationExpression(MaikuroParser::VariableDeclarationExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getSemicolon() const;

        const TokenPtr& getAssign() const;

        const ExpressionPtrVec& getExpressions() const;

        const TokenPtrVec& getCommas() const;

     private:
        TokenPtr         _semicolon;
        TokenPtr         _assign;
        ExpressionPtrVec _expressions;
        TokenPtrVec      _commas;
    };

    typedef shared_ptr<VariableDeclarationExpression> VariableDeclarationExpressionPtr;
    typedef vector<VariableDeclarationExpressionPtr>  VariableDeclarationExpressionPtrVec;

    class VariableDeclaration : public Statement {
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

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const AnnotationsPtrVec& getAnnotations() const;

        const TokenPtr& getVar() const;

        const VariableNameDeclarationPtrVec& getVariableNames() const;

        const TokenPtrVec& getSeparators() const;

        const VariableDeclarationExpressionPtr& getExpressions() const;

     private:
        AnnotationsPtrVec                _annotations;
        TokenPtr                         _var;
        VariableNameDeclarationPtrVec    _variableNames;
        TokenPtrVec                      _separators;
        VariableDeclarationExpressionPtr _expressions;
    };

    typedef shared_ptr<VariableDeclaration> VariableDeclarationPtr;
    typedef vector<VariableDeclarationPtr>  VariableDeclarationPtrVec;
}

