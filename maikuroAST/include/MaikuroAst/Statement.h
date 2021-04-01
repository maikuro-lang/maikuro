#pragma once

#include "common.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    class Statement : public MaikuroAst::AstNode {
     public:
        explicit Statement(TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        TokenPtr getSemicolonToken();

     protected:
        TokenPtr _semicolon;
    };

    typedef shared_ptr<Statement> StatementPtr;
    typedef vector<StatementPtr>  StatementPtrVec;
}

