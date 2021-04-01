#pragma once

#include "common.h"
#include "Statement.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    class PackageName : public MaikuroAst::AstNode {
     public:
        PackageName(IdentifierPtrVec identifiers, TypeIdentifierPtr typeIdentifier, TokenPtrVec dots);

        explicit PackageName(MaikuroParser::PackageNameContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        IdentifierPtrVec  _identifiers;
        TypeIdentifierPtr _typeIdentifier;
        TokenPtrVec                   _dots;
    };

    typedef shared_ptr<PackageName>        PackageNamePtr;

    class PackageDeclaration : public Statement {
     public:
        PackageDeclaration(TokenPtr packageToken, PackageNamePtr packageName, TokenPtr semicolon);

        PackageDeclaration(MaikuroParser::PackageDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        TokenPtr getPackageToken() const;

        PackageNamePtr getPackageName() const;

        int getLine() override;

        string toString() override;

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

        TokenPtrVec getTokens() override;

        PackageNamePtr getPackageName() const;

        TypeIdentifierPtr getAlias() const;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr          _importToken;
        PackageNamePtr    _packageName;
        TokenPtr                      _asToken;
        TypeIdentifierPtr _alias;
    };

    typedef shared_ptr<ImportDeclaration>  ImportDeclarationPtr;
    typedef vector<ImportDeclarationPtr>   ImportDeclarationPtrVec;
}

