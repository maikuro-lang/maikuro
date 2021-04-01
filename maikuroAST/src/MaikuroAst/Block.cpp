#include "MaikuroAst/Block.h"
#include "MaikuroAst/StatementBuilder.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    Block::Block(TokenPtr leftBra, StatementPtrVec statements, TokenPtr rightBra)
        : _leftBra(leftBra), _statements(statements), _rightBra(rightBra), Statement(nullptr) {
    }

    Block::Block(MaikuroParser::BlockContext* ctx) : Block(
        Token::createToken(ctx->LBRACE()),
        sb_createStatement(ctx->statement()),
        Token::createToken(ctx->RBRACE())
    ) {
    }

    TokenPtrVec Block::getTokens() {
        TokenPtrVec tokens = { _leftBra };

        Token::mergeTokens(&tokens, Utils::getTokens<Statement>(_statements));

        tokens.push_back(_rightBra);

        return tokens;
    }

    string Block::toString() {
        return Token::toString(getTokens());
    }
}