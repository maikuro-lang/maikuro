#pragma once

#include "common.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    class Statement : public AstNode, public EnableSharedFromThisVirtual<Statement> {
     public:
        explicit Statement(TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        std::string toString() override;

        const TokenPtr& getSemicolonToken();

        NodeType getNodeType() override;

     protected:
        TokenPtr _semicolonToken;
    };

    typedef std::shared_ptr<Statement> StatementPtr;
    typedef std::vector<StatementPtr>  StatementPtrVec;
}

