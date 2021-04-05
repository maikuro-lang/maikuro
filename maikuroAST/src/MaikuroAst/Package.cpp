#include "MaikuroAst/Package.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    PackageName::PackageName(
        IdentifierPtrVec identifiers,
        TypeIdentifierPtr typeIdentifier,
        TokenPtrVec dots
    )
        : _identifiers(identifiers), _typeIdentifier(typeIdentifier), _dots(dots) {
    }

    PackageName::PackageName(MaikuroParser::PackageNameContext* ctx) : PackageName(
        Utils::create<Identifier>(ctx->IDENTIFIER()),
        ctx->TYPE_IDENTIFIER() ? Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()) : nullptr,
        Token::createTokens(ctx->DOT())
    ) {
    }

    TokenPtrVec PackageName::getTokens() {
        TokenPtrVec tokens;

        int i = 0;
        for (const auto& identifier : _identifiers) {
            Token::mergeTokens(&tokens, identifier->getTokens());

            if (_dots.size() > i) {
                tokens.push_back(_dots[i++]);
            }
        }

        if (_typeIdentifier) {
            Token::mergeTokens(&tokens, _typeIdentifier->getTokens());
        }

        return tokens;
    }

    int PackageName::getLine() {
        return _identifiers[0]->getLine();
    }

    string PackageName::toString() {
        return Token::toString(getTokens());
    }

    const IdentifierPtrVec& PackageName::getIdentifiers() const {
        return _identifiers;
    }

    const TypeIdentifierPtr& PackageName::getTypeIdentifier() const {
        return _typeIdentifier;
    }

    const TokenPtrVec& PackageName::getDots() const {
        return _dots;
    }

    AstNode::NodeType PackageName::getNodeType() {
        return NodeType::PACKAGE_NAME;
    }

    void PackageName::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<PackageName>::shared_from_this());
    }

    PackageDeclaration::PackageDeclaration(
        TokenPtr packageToken,
        PackageNamePtr packageName,
        TokenPtr semicolon
    )
        : _packageToken(
        packageToken
    ), _packageName(packageName), Statement(semicolon) {
    }

    PackageDeclaration::PackageDeclaration(MaikuroParser::PackageDeclarationContext* ctx)
        : PackageDeclaration(
        Token::createToken(ctx->PACKAGE()),
        Utils::create<PackageName>(ctx->packageName()),
        Token::createToken(ctx->SEMI())) {
    }

    TokenPtrVec PackageDeclaration::getTokens() {
        TokenPtrVec tokens = { _packageToken };

        Token::mergeTokens(&tokens, _packageName->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    const TokenPtr& PackageDeclaration::getPackageToken() const {
        return _packageToken;
    }

    const PackageNamePtr& PackageDeclaration::getPackageName() const {
        return _packageName;
    }

    int PackageDeclaration::getLine() {
        return _packageToken->getLine();
    }

    string PackageDeclaration::toString() {
        return _packageToken->toString() + " " + _packageName->toString() + Statement::toString();
    }

    AstNode::NodeType PackageDeclaration::getNodeType() {
        return NodeType::PACKAGE_DECLARATION;
    }

    void PackageDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<PackageDeclaration>::shared_from_this());
//        visitor->visit(static_pointer_cast<PackageDeclaration>(this->getSharedPtr()));
    }

    ImportDeclaration::ImportDeclaration(
        TokenPtr importToken,
        PackageNamePtr packageName,
        TokenPtr asToken,
        TypeIdentifierPtr typeIdentifier,
        TokenPtr semicolon
    ) : _importToken(
        importToken
    ), _packageName(packageName), _asToken(asToken), _alias(typeIdentifier), Statement(semicolon) {
    }

    ImportDeclaration::ImportDeclaration(MaikuroParser::ImportDeclarationContext* ctx) : ImportDeclaration(
        Token::createToken(ctx->IMPORT()),
        Utils::create<PackageName>(ctx->packageName()),
        Token::createToken(ctx->AS()),
        ctx->TYPE_IDENTIFIER() ? Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()) : nullptr,
        Token::createToken(ctx->SEMI())) {
    }

    TokenPtrVec ImportDeclaration::getTokens() {
        TokenPtrVec tokens          = { _importToken };
        TokenPtrVec statementTokens = Statement::getTokens();

        Token::mergeTokens(&tokens, _packageName->getTokens());

        if (_asToken) {
            tokens.push_back(_asToken);

            Token::mergeTokens(&tokens, _alias->getTokens());
        }

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    const PackageNamePtr& ImportDeclaration::getPackageName() const {
        return _packageName;
    }

    const TypeIdentifierPtr& ImportDeclaration::getAlias() const {
        return _alias;
    }

    int ImportDeclaration::getLine() {
        return _importToken->getLine();
    }

    string ImportDeclaration::toString() {
        auto out = _importToken->toString() + " " + _packageName->toString();

        if (_alias) {
            out += " " + _asToken->toString() + " " + _alias->toString();
        }

        return out + Statement::toString();
    }

    AstNode::NodeType ImportDeclaration::getNodeType() {
        return NodeType::IMPORT_DECLARATION;
    }

    const TokenPtr& ImportDeclaration::getImportToken() const {
        return _importToken;
    }

    const TokenPtr& ImportDeclaration::getAsToken() const {
        return _asToken;
    }

    void ImportDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<ImportDeclaration>::shared_from_this());
    }
}