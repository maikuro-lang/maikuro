#pragma once

#include "common.h"
#include "Token.h"

namespace MaikuroAst {
    class AstNode {
     public:
        virtual int getLine() = 0;

        virtual string toString() = 0;

        virtual TokenPtrVec getTokens() = 0;
    };

    typedef shared_ptr<AstNode> AstNodePtr;
    typedef vector<AstNodePtr>  AstNodePtrVec;
}

