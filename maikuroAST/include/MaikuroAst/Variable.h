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

    typedef std::shared_ptr<Expression> ExpressionPtr;
    typedef std::vector<ExpressionPtr>  ExpressionPtrVec;

    class VariableName : public AstNode, public EnableSharedFromThisVirtual<VariableName> {
     public:
        VariableName(TokenPtr atSign, IdentifierPtr identifier);

        explicit VariableName(MaikuroGrammar::MaikuroParser::VariableNameContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getAtSign() const;

        const IdentifierPtr& getIdentifier() const;

     private:
        TokenPtr      _atSign;
        IdentifierPtr _identifier;
    };

    typedef std::shared_ptr<VariableName> VariableNamePtr;
    typedef std::vector<VariableNamePtr>  VariableNamePtrVec;

    class VariableNameDeclaration : public AstNode, public EnableSharedFromThisVirtual<VariableNameDeclaration> {
     public:
        VariableNameDeclaration(TypeDeclarationPtr typeDeclaration, VariableNamePtr variableName);

        explicit VariableNameDeclaration(MaikuroGrammar::MaikuroParser::VariableDeclarationNameContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TypeDeclarationPtr& getTypeDeclaration() const;

        const VariableNamePtr& getVariableName() const;

     private:
        TypeDeclarationPtr _typeDeclaration;
        VariableNamePtr    _variableName;
    };

    typedef std::shared_ptr<VariableNameDeclaration> VariableNameDeclarationPtr;
    typedef std::vector<VariableNameDeclarationPtr>  VariableNameDeclarationPtrVec;

    class VariableDeclarationExpression : public AstNode, public EnableSharedFromThisVirtual<VariableDeclarationExpression> {
     public:
        VariableDeclarationExpression(
            TokenPtr semicolon,
            TokenPtr assign,
            ExpressionPtrVec expressions,
            TokenPtrVec commas
        );

        explicit VariableDeclarationExpression(MaikuroGrammar::MaikuroParser::VariableDeclarationExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

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

    typedef std::shared_ptr<VariableDeclarationExpression> VariableDeclarationExpressionPtr;
    typedef std::vector<VariableDeclarationExpressionPtr>  VariableDeclarationExpressionPtrVec;

    class VariableDeclaration : public Statement, public EnableSharedFromThisVirtual<VariableDeclaration> {
     public:
        VariableDeclaration(
            AnnotationsPtrVec annotations,
            TokenPtr var,
            VariableNameDeclarationPtrVec variableNames,
            TokenPtrVec separators,
            VariableDeclarationExpressionPtr expressions,
            TokenPtr semicolon
        );

        explicit VariableDeclaration(MaikuroGrammar::MaikuroParser::VariableDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

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

    typedef std::shared_ptr<VariableDeclaration> VariableDeclarationPtr;
    typedef std::vector<VariableDeclarationPtr>  VariableDeclarationPtrVec;
}

