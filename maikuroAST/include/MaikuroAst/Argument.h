#pragma once

#include "common.h"
#include "AstNode.h"
#include "Literals.h"
#include "Annotation.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class Expression;

    typedef shared_ptr<Expression> ExpressionPtr;

    class Argument : public AstNode {
     public:
        Argument(IdentifierPtr identifier, TokenPtr color, ExpressionPtr expression);

        explicit Argument(MaikuroParser::ArgumentContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const IdentifierPtr& getIdentifier() const;

        const TokenPtr& getColon() const;

        const ExpressionPtr& getExpression() const;

     private:
        IdentifierPtr _identifier;
        TokenPtr      _colon;
        ExpressionPtr _expression;
    };

    typedef shared_ptr<Argument> ArgumentPtr;
    typedef vector<ArgumentPtr>  ArgumentPtrVec;

    class Arguments : public AstNode {
     public:
        Arguments(TokenPtr openBrace, ArgumentPtrVec arguments, TokenPtrVec commas, TokenPtr closeBrace);

        explicit Arguments(MaikuroParser::ArgumentsContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

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

    typedef shared_ptr<Arguments> ArgumentsPtr;
}

