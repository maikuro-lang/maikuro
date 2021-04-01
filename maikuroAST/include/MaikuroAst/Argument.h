#pragma once

#include "common.h"
#include "AstNode.h"
#include "Literals.h"
#include "Annotation.h"
#include "Token.h"

namespace MaikuroAst {
    class Expression;

    typedef shared_ptr<Expression>            ExpressionPtr;

    class Argument : public AstNode {
     public:
        Argument(IdentifierPtr identifier, TokenPtr semicolon, ExpressionPtr expression);

        explicit Argument(MaikuroParser::ArgumentContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        IdentifierPtr _identifier;
        TokenPtr      _semicolon;
        ExpressionPtr _expression;
    };

    typedef shared_ptr<Argument>              ArgumentPtr;
    typedef vector<ArgumentPtr>               ArgumentPtrVec;

    class Arguments : public AstNode {
     public:
        Arguments(TokenPtr openBrace, ArgumentPtrVec arguments, TokenPtrVec commas, TokenPtr closeBrace);

        explicit Arguments(MaikuroParser::ArgumentsContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr       _openBrace;
        ArgumentPtrVec _arguments;
        TokenPtrVec    _commas;
        TokenPtr       _closeBrace;
    };

    typedef shared_ptr<MaikuroAst::Arguments> ArgumentsPtr;
}

