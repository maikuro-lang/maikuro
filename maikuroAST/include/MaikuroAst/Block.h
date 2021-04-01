#pragma once

#include "common.h"
#include "Statement.h"
#include "Token.h"

namespace MaikuroAst {
    class Block : public Statement {
     public:
        explicit Block(TokenPtr leftBra, StatementPtrVec statements, TokenPtr rightBra);

        explicit Block(MaikuroParser::BlockContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override {
            return _leftBra->getLine();
        }

        string toString() override;

     private:
        TokenPtr        _leftBra;
        StatementPtrVec _statements;
        TokenPtr        _rightBra;
    };

    typedef shared_ptr<Block> BlockPtr;
}

