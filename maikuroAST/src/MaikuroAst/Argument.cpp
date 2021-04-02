#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"
namespace MaikuroAst {
    Argument::Argument(IdentifierPtr identifier, TokenPtr colon, ExpressionPtr expression)
        : _identifier(identifier), _colon(colon), _expression(expression) {
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
            tokens.push_back(_colon);
        }

        Token::mergeTokens(&tokens, _expression->getTokens());

        return tokens;
    }

    const IdentifierPtr& Argument::getIdentifier() const {
        return _identifier;
    }

    const TokenPtr& Argument::getColon() const {
        return _colon;
    }

    const ExpressionPtr& Argument::getExpression() const {
        return _expression;
    }

    AstNode::NodeType Argument::getNodeType() {
        return NodeType::ARGUMENT;
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

    const TokenPtr& Arguments::getOpenBrace() const {
        return _openBrace;
    }

    const ArgumentPtrVec& Arguments::getArguments() const {
        return _arguments;
    }

    const TokenPtrVec& Arguments::getCommas() const {
        return _commas;
    }

    const TokenPtr& Arguments::getCloseBrace() const {
        return _closeBrace;
    }

    AstNode::NodeType Arguments::getNodeType() {
        return NodeType::ARGUMENTS;
    }
}