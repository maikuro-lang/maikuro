#pragma once

#include "common.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {

    class Type : public AstNode, public EnableSharedFromThisVirtual<Type> {
     public:
        Type(
            TypeIdentifierPtr typeIdentifier,
            TokenPtr openBrace,
            NumberLiteralPtr arraySize,
            TokenPtr closeBrace,
            TokenPtr questionMark
        );

        explicit Type(MaikuroGrammar::MaikuroParser::TypeContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        std::string toString() override;

        bool isNullable();

        bool isArray();

        bool hasArraySize();

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TypeIdentifierPtr& getTypeIdentifier() const;

        const TokenPtr& getOpenBrace() const;

        const NumberLiteralPtr& getArraySize() const;

        const TokenPtr& getCloseBrace() const;

        const TokenPtr& getQuestionMark() const;

     private:
        TypeIdentifierPtr _typeIdentifier;
        TokenPtr          _openBrace;
        NumberLiteralPtr  _arraySize;
        TokenPtr          _closeBrace;
        TokenPtr          _questionMark;
    };

    typedef std::shared_ptr<Type> TypePtr;
    typedef std::vector<TypePtr>  TypePtrVec;

    class TypeDeclaration : public AstNode, public EnableSharedFromThisVirtual<TypeDeclaration> {
     public:
        TypeDeclaration(TypePtrVec types, TokenPtrVec pipes);

        explicit TypeDeclaration(MaikuroGrammar::MaikuroParser::TypeDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TypePtrVec& getTypes() const;

        const TokenPtrVec& getPipes() const;

     private:
        TypePtrVec  _types;
        TokenPtrVec _pipes;
    };

    typedef std::shared_ptr<TypeDeclaration> TypeDeclarationPtr;
    typedef std::vector<TypeDeclarationPtr>  TypeDeclarationPtrVec;
}

