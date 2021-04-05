#pragma once

#include "common.h"
#include "Statement.h"
#include "Token.h"

namespace MaikuroAst {

    class Block : public Statement {
     public:
        explicit Block(TokenPtr leftBra, StatementPtrVec statements, TokenPtr rightBra);

        explicit Block(MaikuroGrammar::MaikuroParser::BlockContext* ctx);

        int getLine() override {
            return _leftBra->getLine();
        }

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getLeftBra() const;

        const StatementPtrVec& getStatements() const;

        const TokenPtr& getRightBra() const;

     private:
        TokenPtr        _leftBra;
        StatementPtrVec _statements;
        TokenPtr        _rightBra;
    };

    typedef std::shared_ptr<Block> BlockPtr;
}

