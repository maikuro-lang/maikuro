#pragma once

#include "common.h"
#include "Statement.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class PackageName : public AstNode {
     public:
        PackageName(IdentifierPtrVec identifiers, TypeIdentifierPtr typeIdentifier, TokenPtrVec dots);

        explicit PackageName(MaikuroParser::PackageNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const IdentifierPtrVec& getIdentifiers() const;

        const TypeIdentifierPtr& getTypeIdentifier() const;

        const TokenPtrVec& getDots() const;

     private:
        IdentifierPtrVec  _identifiers;
        TypeIdentifierPtr _typeIdentifier;
        TokenPtrVec       _dots;
    };

    typedef shared_ptr<PackageName> PackageNamePtr;

    class PackageDeclaration : public Statement {
     public:
        PackageDeclaration(TokenPtr packageToken, PackageNamePtr packageName, TokenPtr semicolon);

        PackageDeclaration(MaikuroParser::PackageDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getPackageToken() const;

        const PackageNamePtr& getPackageName() const;

     private:
        TokenPtr       _packageToken;
        PackageNamePtr _packageName;
    };

    typedef shared_ptr<PackageDeclaration> PackageDeclarationPtr;

    class ImportDeclaration : public Statement {
     public:
        ImportDeclaration(
            TokenPtr importToken,
            PackageNamePtr packageName,
            TokenPtr asToken,
            TypeIdentifierPtr typeIdentifier,
            TokenPtr semicolon
        );

        explicit ImportDeclaration(MaikuroParser::ImportDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        const TokenPtr& getImportToken() const;

        const TokenPtr& getAsToken() const;

        NodeType getNodeType() override;

        const PackageNamePtr& getPackageName() const;

        const TypeIdentifierPtr& getAlias() const;

     private:
        TokenPtr          _importToken;
        PackageNamePtr    _packageName;
        TokenPtr          _asToken;
        TypeIdentifierPtr _alias;
    };

    typedef shared_ptr<ImportDeclaration> ImportDeclarationPtr;
    typedef vector<ImportDeclarationPtr>  ImportDeclarationPtrVec;
}

