#pragma once

#include "common.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class Type : public AstNode {
     public:
        Type(
            TypeIdentifierPtr typeIdentifier,
            TokenPtr openBrace,
            NumberLiteralPtr arraySize,
            TokenPtr closeBrace,
            TokenPtr questionMark
        );

        explicit Type(MaikuroParser::TypeContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        bool isNullable();

        bool isArray();

        bool hasArraySize();

        AstNode::NodeType getNodeType() override;

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

    typedef shared_ptr<Type> TypePtr;
    typedef vector<TypePtr>  TypePtrVec;

    class TypeDeclaration : public AstNode {
     public:
        TypeDeclaration(TypePtrVec types, TokenPtrVec pipes);

        explicit TypeDeclaration(MaikuroParser::TypeDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TypePtrVec& getTypes() const;

        const TokenPtrVec& getPipes() const;

     private:
        TypePtrVec  _types;
        TokenPtrVec _pipes;
    };

    typedef shared_ptr<TypeDeclaration> TypeDeclarationPtr;
    typedef vector<TypeDeclarationPtr>  TypeDeclarationPtrVec;
}

