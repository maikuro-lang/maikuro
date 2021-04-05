#pragma once

#include "common.h"
#include "Statement.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {

    class PackageName : public AstNode, public EnableSharedFromThisVirtual<PackageName> {
     public:
        PackageName(IdentifierPtrVec identifiers, TypeIdentifierPtr typeIdentifier, TokenPtrVec dots);

        explicit PackageName(MaikuroGrammar::MaikuroParser::PackageNameContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const IdentifierPtrVec& getIdentifiers() const;

        const TypeIdentifierPtr& getTypeIdentifier() const;

        const TokenPtrVec& getDots() const;

     private:
        IdentifierPtrVec  _identifiers;
        TypeIdentifierPtr _typeIdentifier;
        TokenPtrVec       _dots;
    };

    typedef std::shared_ptr<PackageName> PackageNamePtr;

    class PackageDeclaration : public Statement, public EnableSharedFromThisVirtual<PackageDeclaration> {
     public:
        PackageDeclaration(TokenPtr packageToken, PackageNamePtr packageName, TokenPtr semicolon);

        PackageDeclaration(MaikuroGrammar::MaikuroParser::PackageDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getPackageToken() const;

        const PackageNamePtr& getPackageName() const;

     private:
        TokenPtr       _packageToken;
        PackageNamePtr _packageName;
    };

    typedef std::shared_ptr<PackageDeclaration> PackageDeclarationPtr;

    class ImportDeclaration : public Statement, public EnableSharedFromThisVirtual<ImportDeclaration> {
     public:
        ImportDeclaration(
            TokenPtr importToken,
            PackageNamePtr packageName,
            TokenPtr asToken,
            TypeIdentifierPtr typeIdentifier,
            TokenPtr semicolon
        );

        explicit ImportDeclaration(MaikuroGrammar::MaikuroParser::ImportDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        const TokenPtr& getImportToken() const;

        const TokenPtr& getAsToken() const;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const PackageNamePtr& getPackageName() const;

        const TypeIdentifierPtr& getAlias() const;

     private:
        TokenPtr          _importToken;
        PackageNamePtr    _packageName;
        TokenPtr          _asToken;
        TypeIdentifierPtr _alias;
    };

    typedef std::shared_ptr<ImportDeclaration> ImportDeclarationPtr;
    typedef std::vector<ImportDeclarationPtr>  ImportDeclarationPtrVec;
}

