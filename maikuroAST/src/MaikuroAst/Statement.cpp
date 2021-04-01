#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    Statement::Statement(TokenPtr semicolon) : _semicolon(semicolon) {
    }

    TokenPtrVec Statement::getTokens() {
        TokenPtrVec tokens;

        if (_semicolon) {
            tokens.push_back(_semicolon);
        }

        return tokens;
    }

    int Statement::getLine() {
        return _semicolon->getLine();
    }

    string Statement::toString() {
        return _semicolon->toString();
    }

    TokenPtr Statement::getSemicolonToken() {
        return _semicolon;
    }
}