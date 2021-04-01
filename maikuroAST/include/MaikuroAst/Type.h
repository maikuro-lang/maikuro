#pragma once

#include "common.h"
#include "Literals.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    class Type : public MaikuroAst::AstNode {
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

     private:
        TypeIdentifierPtr _typeIdentifier;
        TokenPtr          _openBrace;
        NumberLiteralPtr  _arraySize;
        TokenPtr          _closeBrace;
        TokenPtr          _questionMark;
    };

    typedef shared_ptr<Type>            TypePtr;
    typedef vector<TypePtr>             TypePtrVec;

    class TypeDeclaration : public MaikuroAst::AstNode {
     public:
        TypeDeclaration(TypePtrVec types, TokenPtrVec pipes);

        explicit TypeDeclaration(MaikuroParser::TypeDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TypePtrVec              _types;
        TokenPtrVec _pipes;
    };

    typedef shared_ptr<TypeDeclaration> TypeDeclarationPtr;
    typedef vector<TypeDeclarationPtr>  TypeDeclarationPtrVec;
}

