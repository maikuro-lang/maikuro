#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"
namespace MaikuroAst {

    Literal::Literal(TokenPtr token) : _token(token) {
    }

    Literal::Literal(antlr4::tree::TerminalNode* node) : Literal(Token::createToken(node)) {
    }

    TokenPtrVec Literal::getTokens() {
        return { _token };
    }

    TokenPtr Literal::getToken() {
        return _token;
    }

    string Literal::getValue() {
        return _token->getValue();
    }

    int Literal::getLine() {
        return _token->getLine();
    }

    string Literal::toString() {
        return _token->toString();
    }

    NullLiteral::NullLiteral(TokenPtr token) : Literal(token) {
    }

    NullLiteral::NullLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    BoolLiteral::BoolLiteral(TokenPtr token) : Literal(token) {
    }

    BoolLiteral::BoolLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    NumberLiteral::NumberLiteral(TokenPtr token) : Literal(token) {
    }

    NumberLiteral::NumberLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    CharLiteral::CharLiteral(TokenPtr token) : Literal(token) {
    }

    CharLiteral::CharLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    StringLiteral::StringLiteral(TokenPtr token) : Literal(token) {
    }

    StringLiteral::StringLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    Identifier::Identifier(TokenPtr token) : Literal(token) {
    }

    Identifier::Identifier(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    TypeIdentifier::TypeIdentifier(TokenPtr token) : Literal(token) {
    }

    TypeIdentifier::TypeIdentifier(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    VisibilityModifier::VisibilityModifier(TokenPtr token) : Literal(token) {
    }

    VisibilityModifier::VisibilityModifier(MaikuroParser::VisibilityModifierContext* ctx)
        : Literal(
        Token::createToken((ctx->PUBLIC() ?: ctx->PROTECTED() ?:
                                             ctx->PRIVATE() ?: ctx->ABSTRACT() ?: ctx->STATIC() ?: ctx->FINAL()
                                                                                                   ?: nullptr))) {
    }
}