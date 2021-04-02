#include "MaikuroAst/Alias.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"

namespace MaikuroAst {

    AliasDeclaration::AliasDeclaration(
        AnnotationsPtrVec annotations,
        TokenPtr aliasToken,
        TypePtr type,
        TokenPtr assignToken,
        TypeDeclarationPtr typeDeclaration,
        TokenPtr semiColon
    )
        : _annotations(annotations),
          _aliasToken(aliasToken),
          _type(type),
          _assignToken(assignToken),
          _typeDeclaration(typeDeclaration),
          Statement(semiColon) {
    }

    AliasDeclaration::AliasDeclaration(MaikuroParser::AliasDeclarationContext* ctx) : AliasDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        Token::createToken(ctx->ALIAS()),
        Utils::create<Type>(ctx->type()),
        Token::createToken(ctx->ASSIGN()),
        Utils::create<TypeDeclaration>(ctx->typeDeclaration()),
        Token::createToken(ctx->SEMI())
    ) {
    }

    TokenPtrVec AliasDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        tokens.push_back(_aliasToken);

        Token::mergeTokens(&tokens, _type->getTokens());

        tokens.push_back(_assignToken);

        Token::mergeTokens(&tokens, _typeDeclaration->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int AliasDeclaration::getLine() {
        return _aliasToken->getLine();
    }

    string AliasDeclaration::toString() {
        return Token::toString(getTokens());
    }

    const AnnotationsPtrVec& AliasDeclaration::getAnnotations() const {
        return _annotations;
    }

    const TokenPtr& AliasDeclaration::getAliasToken() const {
        return _aliasToken;
    }

    const TypePtr& AliasDeclaration::getType() const {
        return _type;
    }

    const TokenPtr& AliasDeclaration::getAssignToken() const {
        return _assignToken;
    }

    const TypeDeclarationPtr& AliasDeclaration::getTypeDeclaration() const {
        return _typeDeclaration;
    }

    AstNode::NodeType AliasDeclaration::getNodeType() {
        return NodeType::ALIAS_DECLARATION;
    }
}