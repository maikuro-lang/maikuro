#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    Statement::Statement(TokenPtr semicolon) : _semicolonToken(semicolon) {
    }

    TokenPtrVec Statement::getTokens() {
        TokenPtrVec tokens;

        if (_semicolonToken) {
            tokens.push_back(_semicolonToken);
        }

        return tokens;
    }

    int Statement::getLine() {
        return _semicolonToken->getLine();
    }

    string Statement::toString() {
        return _semicolonToken->toString();
    }

    const TokenPtr& Statement::getSemicolonToken() {
        return _semicolonToken;
    }

    AstNode::NodeType Statement::getNodeType() {
        return NodeType::STATEMENT;
    }
}