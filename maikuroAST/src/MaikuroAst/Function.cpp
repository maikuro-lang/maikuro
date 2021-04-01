#include "MaikuroAst/Function.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"

namespace MaikuroAst {

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
}