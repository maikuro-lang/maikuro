#pragma once

#include "common.h"
#include "Statement.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class Block : public Statement {
     public:
        explicit Block(TokenPtr leftBra, StatementPtrVec statements, TokenPtr rightBra);

        explicit Block(MaikuroParser::BlockContext* ctx);

        int getLine() override {
            return _leftBra->getLine();
        }

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getLeftBra() const;

        const StatementPtrVec& getStatements() const;

        const TokenPtr& getRightBra() const;

     private:
        TokenPtr        _leftBra;
        StatementPtrVec _statements;
        TokenPtr        _rightBra;
    };

    typedef shared_ptr<Block> BlockPtr;
}

