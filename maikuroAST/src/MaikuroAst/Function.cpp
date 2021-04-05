#include "MaikuroAst/Function.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    FormalParameter::FormalParameter(TypePtr type, TokenPtr variadic, IdentifierPtr identifier)
        : _type(type), _variadic(variadic), _identifier(identifier) {
    }

    FormalParameter::FormalParameter(MaikuroParser::FormalParameterContext* ctx)
        : FormalParameter(
        Utils::create<Type>(ctx->type()),
        nullptr,
        Utils::create<Identifier>(ctx->IDENTIFIER())
    ) {
    }

    FormalParameter::FormalParameter(MaikuroParser::LastFormalParameterContext* ctx)
        : FormalParameter(
        Utils::create<Type>(ctx->type()),
        Token::createToken(ctx->ELLIPSIS()),
        Utils::create<Identifier>(ctx->IDENTIFIER())
    ) {
    }

    int FormalParameter::getLine() {
        return _type->getLine();
    }

    string FormalParameter::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FormalParameter::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, _type->getTokens());

        if (_variadic) {
            tokens.push_back(_variadic);
        }

        Token::mergeTokens(&tokens, _identifier->getTokens());

        return tokens;
    }

    const TypePtr& FormalParameter::getType() const {
        return _type;
    }

    const TokenPtr& FormalParameter::getVariadic() const {
        return _variadic;
    }

    const IdentifierPtr& FormalParameter::getIdentifier() const {
        return _identifier;
    }

    AstNode::NodeType FormalParameter::getNodeType() {
        return NodeType::FORMAL_PARAMETER;
    }

    void FormalParameter::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<FormalParameter>::shared_from_this());
    }

    FormalParameterList::FormalParameterList(
        FormalParameterPtrVec parameters,
        TokenPtrVec commas
    )
        : _parameters(parameters), _commas(commas) {
    }

    FormalParameterList::FormalParameterList(MaikuroParser::FormalParameterListContext* ctx)
        : FormalParameterList(
        Utils::create<FormalParameter>(ctx->formalParameter()),
        Token::createTokens(ctx->COMMA())
    ) {
        if (ctx->lastFormalParameter()) {
            _parameters.push_back(
                Utils::create<FormalParameter>(ctx->lastFormalParameter())
            );
        }
    }

    string FormalParameterList::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FormalParameterList::getTokens() {
        TokenPtrVec tokens;

        int i = 0;
        for (const auto& parameter : _parameters) {
            Token::mergeTokens(&tokens, parameter->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        return tokens;
    }

    const FormalParameterPtrVec& FormalParameterList::getParameters() const {
        return _parameters;
    }

    const TokenPtrVec& FormalParameterList::getCommas() const {
        return _commas;
    }

    AstNode::NodeType FormalParameterList::getNodeType() {
        return NodeType::FORMAL_PARAMETER_LIST;
    }

    void FormalParameterList::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<FormalParameterList>::shared_from_this());
    }

    FormalParameters::FormalParameters(
        TokenPtr leftPar,
        FormalParameterListPtr parameters,
        TokenPtr rightPar
    )
        : _leftPar(leftPar), _parameters(parameters), _rightPar(rightPar) {
    }

    FormalParameters::FormalParameters(MaikuroParser::FormalParametersContext* ctx)
        : FormalParameters(
        Token::createToken(ctx->LPAREN()),
        ctx->formalParameterList()
        ? Utils::create<FormalParameterList>(ctx->formalParameterList())
        : nullptr,
        Token::createToken(ctx->RPAREN())
    ) {
    }

    string FormalParameters::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FormalParameters::getTokens() {
        TokenPtrVec tokens = { _leftPar };

        if (_parameters) {
            Token::mergeTokens(&tokens, _parameters->getTokens());
        }

        tokens.push_back(_rightPar);

        return tokens;
    }

    const TokenPtr& FormalParameters::getLeftPar() const {
        return _leftPar;
    }

    const FormalParameterListPtr& FormalParameters::getParameters() const {
        return _parameters;
    }

    const TokenPtr& FormalParameters::getRightPar() const {
        return _rightPar;
    }

    AstNode::NodeType FormalParameters::getNodeType() {
        return NodeType::FORMAL_PARAMETERS;
    }

    void FormalParameters::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<FormalParameters>::shared_from_this());
    }

    FunctionHeader::FunctionHeader(
        TokenPtr fun,
        IdentifierPtr identifier,
        FormalParametersPtr parameters,
        TokenPtr colon,
        TypePtr returnType
    ) : _fun(fun), _identifier(identifier), _parameters(parameters), _colon(colon), _returnType(returnType) {
    }

    FunctionHeader::FunctionHeader(MaikuroParser::FunctionHeaderContext* ctx) : FunctionHeader(
        Token::createToken(ctx->FUN()),
        Utils::create<Identifier>(ctx->IDENTIFIER()),
        Utils::create<FormalParameters>(ctx->formalParameters()),
        Token::createToken(ctx->COLON()),
        ctx->type() ? Utils::create<Type>(ctx->type()) : nullptr
    ) {
    }

    int FunctionHeader::getLine() {
        return _fun->getLine();
    }

    string FunctionHeader::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FunctionHeader::getTokens() {
        TokenPtrVec tokens = { _fun };

        Token::mergeTokens(&tokens, _identifier->getTokens());
        Token::mergeTokens(&tokens, _parameters->getTokens());

        if (_colon) {
            tokens.push_back(_colon);
            Token::mergeTokens(&tokens, _returnType->getTokens());
        }

        return tokens;
    }

    const TokenPtr& FunctionHeader::getFun() const {
        return _fun;
    }

    const IdentifierPtr& FunctionHeader::getIdentifier() const {
        return _identifier;
    }

    const FormalParametersPtr& FunctionHeader::getParameters() const {
        return _parameters;
    }

    const TokenPtr& FunctionHeader::getColon() const {
        return _colon;
    }

    const TypePtr& FunctionHeader::getReturnType() const {
        return _returnType;
    }

    AstNode::NodeType FunctionHeader::getNodeType() {
        return NodeType::FUNCTION_HEADER;
    }

    void FunctionHeader::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<FunctionHeader>::shared_from_this());
    }

    FunctionDeclaration::FunctionDeclaration(
        AnnotationsPtrVec annotations,
        FunctionHeaderPtr functionHeader,
        BlockPtr block
    )
        : _annotations(annotations), _functionHeader(functionHeader), _block(block), Statement(nullptr) {
    }

    FunctionDeclaration::FunctionDeclaration(MaikuroParser::FunctionDeclarationContext* ctx)
        : FunctionDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        Utils::create<FunctionHeader>(ctx->functionHeader()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    int FunctionDeclaration::getLine() {
        return _functionHeader->getLine();
    }

    string FunctionDeclaration::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FunctionDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));
        Token::mergeTokens(&tokens, _functionHeader->getTokens());
        Token::mergeTokens(&tokens, _block->getTokens());

        return tokens;
    }

    const AnnotationsPtrVec& FunctionDeclaration::getAnnotations() const {
        return _annotations;
    }

    const FunctionHeaderPtr& FunctionDeclaration::getFunctionHeader() const {
        return _functionHeader;
    }

    const BlockPtr& FunctionDeclaration::getBlock() const {
        return _block;
    }

    AstNode::NodeType FunctionDeclaration::getNodeType() {
        return NodeType::FUNCTION_DECLARATION;
    }

    void FunctionDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<FunctionDeclaration>::shared_from_this());
    }
}