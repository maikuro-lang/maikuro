#pragma once

#include "common.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;

    class Statement : public AstNode {
     public:
        explicit Statement(TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        const TokenPtr& getSemicolonToken();

        NodeType getNodeType() override;

     protected:
        TokenPtr _semicolonToken;
    };

    typedef shared_ptr<Statement> StatementPtr;
    typedef vector<StatementPtr>  StatementPtrVec;
}

