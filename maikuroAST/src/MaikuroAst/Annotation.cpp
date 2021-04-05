#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    Annotation::Annotation(TypeIdentifierPtr typeIdentifier, ArgumentsPtr arguments)
        : _typeIdentifier(typeIdentifier), _arguments(arguments) {
    }

    Annotation::Annotation(MaikuroParser::AnnotationContext* ctx) : Annotation(
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()),
        ctx->arguments() ? Utils::create<Arguments>(ctx->arguments()) : nullptr
    ) {
    }

    int Annotation::getLine() {
        return _typeIdentifier->getLine();
    }

    string Annotation::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec Annotation::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, _typeIdentifier->getTokens());

        if (_arguments) {
            Token::mergeTokens(&tokens, _arguments->getTokens());
        }

        return tokens;
    }

    const TypeIdentifierPtr& Annotation::getTypeIdentifier() const {
        return _typeIdentifier;
    }

    const ArgumentsPtr& Annotation::getArguments() const {
        return _arguments;
    }

    AstNode::NodeType Annotation::getNodeType() {
        return NodeType::ANNOTATION;
    }

    void Annotation::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Annotation>::shared_from_this());
    }

    Annotations::Annotations(
        TokenPtr prefix,
        AnnotationPtrVec annotations,
        TokenPtrVec commas,
        TokenPtr closeBracket
    )
        : _prefix(prefix), _annotations(annotations), _commas(commas), _closeBracket(closeBracket) {
    }

    Annotations::Annotations(MaikuroParser::AnnotationsContext* ctx) : Annotations(
        Token::createToken(ctx->ATTRIBUTE_PREFIX()),
        Utils::create<Annotation>(ctx->annotation()),
        Token::createTokens(ctx->COMMA()),
        Token::createToken(ctx->RBRACK())
    ) {
    }

    int Annotations::getLine() {
        return _prefix->getLine();
    }

    string Annotations::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec Annotations::getTokens() {
        TokenPtrVec tokens = { _prefix };

        int i = 0;
        for (const auto& annotation : _annotations) {
            Token::mergeTokens(&tokens, annotation->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        tokens.push_back(_closeBracket);

        return tokens;
    }

    const TokenPtr& Annotations::getPrefix() const {
        return _prefix;
    }

    const AnnotationPtrVec& Annotations::getAnnotations() const {
        return _annotations;
    }

    const TokenPtrVec& Annotations::getCommas() const {
        return _commas;
    }

    const TokenPtr& Annotations::getCloseBracket() const {
        return _closeBracket;
    }

    AstNode::NodeType Annotations::getNodeType() {
        return NodeType::ANNOTATIONS;
    }

    void Annotations::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Annotations>::shared_from_this());
    }
}