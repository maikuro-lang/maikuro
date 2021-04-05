#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

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

    AstNode::NodeType Literal::getNodeType() {
        return NodeType::LITERAL;
    }

    void Literal::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Literal>::shared_from_this());
    }

    NullLiteral::NullLiteral(TokenPtr token) : Literal(token) {
    }

    NullLiteral::NullLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType NullLiteral::getNodeType() {
        return NodeType::NULL_LITERAL;
    }

    void NullLiteral::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<NullLiteral>::shared_from_this());
    }

    BoolLiteral::BoolLiteral(TokenPtr token) : Literal(token) {
    }

    BoolLiteral::BoolLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType BoolLiteral::getNodeType() {
        return NodeType::BOOL_LITERAL;
    }

    void BoolLiteral::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<BoolLiteral>::shared_from_this());
    }

    NumberLiteral::NumberLiteral(TokenPtr token) : Literal(token) {
    }

    NumberLiteral::NumberLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType NumberLiteral::getNodeType() {
        return NodeType::NUMBER_LITERAL;
    }

    void NumberLiteral::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<NumberLiteral>::shared_from_this());
    }

    CharLiteral::CharLiteral(TokenPtr token) : Literal(token) {
    }

    CharLiteral::CharLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType CharLiteral::getNodeType() {
        return NodeType::CHAR_LITERAL;
    }

    void CharLiteral::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<CharLiteral>::shared_from_this());
    }

    StringLiteral::StringLiteral(TokenPtr token) : Literal(token) {
    }

    StringLiteral::StringLiteral(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType StringLiteral::getNodeType() {
        return NodeType::STRING_LITERAL;
    }

    void StringLiteral::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<StringLiteral>::shared_from_this());
    }

    Identifier::Identifier(TokenPtr token) : Literal(token) {
    }

    Identifier::Identifier(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType Identifier::getNodeType() {
        return NodeType::IDENTIFIER;
    }

    void Identifier::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Identifier>::shared_from_this());
    }

    TypeIdentifier::TypeIdentifier(TokenPtr token) : Literal(token) {
    }

    TypeIdentifier::TypeIdentifier(antlr4::tree::TerminalNode* node) : Literal(node) {
    }

    AstNode::NodeType TypeIdentifier::getNodeType() {
        return NodeType::TYPE_IDENTIFIER;
    }

    void TypeIdentifier::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<TypeIdentifier>::shared_from_this());
    }

    VisibilityModifier::VisibilityModifier(TokenPtr token) : Literal(token) {
    }

    VisibilityModifier::VisibilityModifier(MaikuroParser::VisibilityModifierContext* ctx)
        : Literal(
        Token::createToken((ctx->PUBLIC() ?: ctx->PROTECTED() ?:
                                             ctx->PRIVATE() ?: ctx->ABSTRACT() ?: ctx->STATIC() ?: ctx->FINAL()
                                                                                                   ?: nullptr))) {
    }

    AstNode::NodeType VisibilityModifier::getNodeType() {
        return NodeType::VISIBILITY_MODIFIER;
    }

    void VisibilityModifier::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<VisibilityModifier>::shared_from_this());
    }
}