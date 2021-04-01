#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Block.h"
#include "Type.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"

namespace MaikuroAst {
    class FormalParameter : public MaikuroAst::AstNode {
     public:
        FormalParameter(TypePtr type, TokenPtr variadic, IdentifierPtr identifier);

        explicit FormalParameter(MaikuroParser::FormalParameterContext* ctx);

        explicit FormalParameter(MaikuroParser::LastFormalParameterContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TypePtr       _type;
        TokenPtr      _variadic;
        IdentifierPtr _identifier;
    };

    typedef shared_ptr<FormalParameter>     FormalParameterPtr;
    typedef vector<FormalParameterPtr>      FormalParameterPtrVec;

    class FormalParameterList : public MaikuroAst::AstNode {
     public:
        FormalParameterList(FormalParameterPtrVec parameters, TokenPtrVec commas);

        explicit FormalParameterList(MaikuroParser::FormalParameterListContext* ctx);

        int getLine() override {
            return _parameters[0]->getLine();
        }

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        FormalParameterPtrVec _parameters;
        TokenPtrVec           _commas;
    };

    typedef shared_ptr<FormalParameterList> FormalParameterListPtr;
    typedef vector<FormalParameterListPtr>  FormalParameterListPtrVec;

    class FormalParameters : public MaikuroAst::AstNode {
     public:
        FormalParameters(TokenPtr leftPar, FormalParameterListPtr parameters, TokenPtr rightPar);

        explicit FormalParameters(MaikuroParser::FormalParametersContext* ctx);

        int getLine() override {
            return _leftPar->getLine();
        }

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr               _leftPar;
        FormalParameterListPtr _parameters;
        TokenPtr               _rightPar;
    };

    typedef shared_ptr<FormalParameters>    FormalParametersPtr;
    typedef vector<FormalParametersPtr>     FormalParametersPtrVec;

    class FunctionHeader : public MaikuroAst::AstNode {
     public:
        FunctionHeader(
            TokenPtr fun,
            IdentifierPtr identifier,
            FormalParametersPtr parameters,
            TokenPtr colon,
            TypePtr returnType
        );

        explicit FunctionHeader(MaikuroParser::FunctionHeaderContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr            _fun;
        IdentifierPtr       _identifier;
        FormalParametersPtr _parameters;
        TokenPtr            _colon;
        TypePtr             _returnType;
    };

    typedef shared_ptr<FunctionHeader>      FunctionHeaderPtr;
    typedef vector<FunctionHeaderPtr>       FunctionHeaderPtrVec;

    class FunctionDeclaration : public Statement {
     public:
        FunctionDeclaration(AnnotationsPtrVec annotations, FunctionHeaderPtr functionHeader, BlockPtr block);

        explicit FunctionDeclaration(MaikuroParser::FunctionDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        AnnotationsPtrVec _annotations;
        FunctionHeaderPtr    _functionHeader;
        BlockPtr _block;
    };

    typedef shared_ptr<FunctionDeclaration> FunctionPtr;
    typedef vector<FunctionPtr>             FunctionPtrVec;
}

