#include "MaikuroAst/Type.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    Type::Type(
        TypeIdentifierPtr typeIdentifier,
        TokenPtr openBrace,
        NumberLiteralPtr arraySize,
        TokenPtr closeBrace,
        TokenPtr questionMark
    )
        : _typeIdentifier(typeIdentifier),
          _openBrace(openBrace),
          _arraySize(arraySize),
          _closeBrace(closeBrace),
          _questionMark(questionMark) {
    }

    Type::Type(MaikuroParser::TypeContext* ctx) : Type(
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()),
        Token::createToken(ctx->LBRACK()),
        ctx->NUMBER_LITERAL() ? Utils::create<NumberLiteral>(ctx->NUMBER_LITERAL()) : nullptr,
        Token::createToken(ctx->RBRACK()),
        Token::createToken(ctx->QUESTION())) {
    }

    TokenPtrVec Type::getTokens() {
        TokenPtrVec tokens(_typeIdentifier->getTokens());

        if (isArray()) {
            tokens.push_back(_openBrace);

            if (_arraySize) {
                Token::mergeTokens(&tokens, _arraySize->getTokens());
            }

            tokens.push_back(_closeBrace);
        }

        if (isNullable()) {
            tokens.push_back(_questionMark);
        }

        return tokens;
    }

    int Type::getLine() {
        return _typeIdentifier->getLine();
    }

    string Type::toString() {
        std::string out = _typeIdentifier->toString();

        if (isArray()) {
            out += _openBrace->toString();

            if (_arraySize) {
                out += _arraySize->toString();
            }

            out += _closeBrace->toString();
        }

        if (isNullable()) {
            out += _questionMark->toString();
        }

        return out;
    }

    bool Type::isNullable() {
        if (_questionMark) {
            return true;
        }

        return false;
    }

    bool Type::isArray() {
        if (_openBrace) {
            return true;
        }

        return false;
    }

    bool Type::hasArraySize() {
        if (isArray() && _arraySize) {
            return true;
        }

        return false;
    }

    const TypeIdentifierPtr& Type::getTypeIdentifier() const {
        return _typeIdentifier;
    }

    const TokenPtr& Type::getOpenBrace() const {
        return _openBrace;
    }

    const NumberLiteralPtr& Type::getArraySize() const {
        return _arraySize;
    }

    const TokenPtr& Type::getCloseBrace() const {
        return _closeBrace;
    }

    const TokenPtr& Type::getQuestionMark() const {
        return _questionMark;
    }

    AstNode::NodeType Type::getNodeType() {
        return NodeType::TYPE;
    }

    void Type::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Type>::shared_from_this());
    }

    TypeDeclaration::TypeDeclaration(TypePtrVec types, TokenPtrVec pipes) : _types(
        types
    ), _pipes(pipes) {
    }

    TypeDeclaration::TypeDeclaration(MaikuroParser::TypeDeclarationContext* ctx)
        : TypeDeclaration(
        Utils::create<Type>(ctx->type()),
        Token::createTokens(ctx->BITOR())) {
    }

    TokenPtrVec TypeDeclaration::getTokens() {
        TokenPtrVec tokens;

        int i = 0;
        for (const auto& type : _types) {
            Token::mergeTokens(&tokens, type->getTokens());

            if (_pipes.size() > i) {
                tokens.push_back(_pipes[i++]);
            }
        }

        return tokens;
    }

    int TypeDeclaration::getLine() {
        return _types[0]->getLine();
    }

    string TypeDeclaration::toString() {
        return Token::toString(getTokens());
    }

    const TypePtrVec& TypeDeclaration::getTypes() const {
        return _types;
    }

    const TokenPtrVec& TypeDeclaration::getPipes() const {
        return _pipes;
    }

    AstNode::NodeType TypeDeclaration::getNodeType() {
        return NodeType::TYPE_DECLARATION;
    }

    void TypeDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<TypeDeclaration>::shared_from_this());
    }
}