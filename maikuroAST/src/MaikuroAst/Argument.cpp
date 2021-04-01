#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"
namespace MaikuroAst {
    Argument::Argument(IdentifierPtr identifier, TokenPtr semicolon, ExpressionPtr expression)
        : _identifier(identifier), _semicolon(semicolon), _expression(expression) {
    }

    Argument::Argument(MaikuroParser::ArgumentContext* ctx) : Argument(
        ctx->IDENTIFIER() ? Utils::create<Identifier>(ctx->IDENTIFIER()) : nullptr,
        Token::createToken(ctx->COLON()),
        eb_createExpression(ctx->expression())
    ) {
    }

    int Argument::getLine() {
        return _identifier->getLine();
    }

    string Argument::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec Argument::getTokens() {
        TokenPtrVec tokens;

        if (_identifier) {
            tokens.push_back(_identifier->getToken());
            tokens.push_back(_semicolon);
        }

        Token::mergeTokens(&tokens, _expression->getTokens());

        return tokens;
    }

    Arguments::Arguments(
        TokenPtr openBrace,
        ArgumentPtrVec arguments,
        TokenPtrVec commas,
        TokenPtr closeBrace
    )
        : _openBrace(
        openBrace
    ), _arguments(arguments), _commas(commas), _closeBrace(closeBrace) {
    }

    Arguments::Arguments(MaikuroParser::ArgumentsContext* ctx) : Arguments(
        Token::createToken(ctx->LPAREN()),
        Utils::create<Argument>(ctx->argument()),
        Token::createTokens(ctx->COMMA()),
        Token::createToken(ctx->RPAREN())
    ) {
    }

    int Arguments::getLine() {
        return _openBrace->getLine();
    }

    string Arguments::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec Arguments::getTokens() {
        TokenPtrVec tokens = { _openBrace };

        int i = 0;
        for (const auto& argument : _arguments) {
            Token::mergeTokens(&tokens, argument->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        tokens.push_back(_closeBrace);

        return tokens;
    }
}