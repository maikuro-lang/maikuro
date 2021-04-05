#pragma once

#include "common.h"
#include "AstNode.h"
#include "Literals.h"
#include "Annotation.h"
#include "Token.h"

namespace MaikuroAst {

    class Expression;
    typedef std::shared_ptr<Expression> ExpressionPtr;

    class Argument : public AstNode {
     public:
        Argument(IdentifierPtr identifier, TokenPtr color, ExpressionPtr expression);

        explicit Argument(MaikuroGrammar::MaikuroParser::ArgumentContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const IdentifierPtr& getIdentifier() const;

        const TokenPtr& getColon() const;

        const ExpressionPtr& getExpression() const;

     private:
        IdentifierPtr _identifier;
        TokenPtr      _colon;
        ExpressionPtr _expression;
    };

    typedef std::shared_ptr<Argument> ArgumentPtr;
    typedef std::vector<ArgumentPtr>  ArgumentPtrVec;

    class Arguments : public AstNode {
     public:
        Arguments(TokenPtr openBrace, ArgumentPtrVec arguments, TokenPtrVec commas, TokenPtr closeBrace);

        explicit Arguments(MaikuroGrammar::MaikuroParser::ArgumentsContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getOpenBrace() const;

        const ArgumentPtrVec& getArguments() const;

        const TokenPtrVec& getCommas() const;

        const TokenPtr& getCloseBrace() const;

     private:
        TokenPtr       _openBrace;
        ArgumentPtrVec _arguments;
        TokenPtrVec    _commas;
        TokenPtr       _closeBrace;
    };

    typedef std::shared_ptr<Arguments> ArgumentsPtr;
}

