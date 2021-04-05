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

    class FormalParameter : public AstNode {
     public:
        FormalParameter(TypePtr type, TokenPtr variadic, IdentifierPtr identifier);

        explicit FormalParameter(MaikuroGrammar::MaikuroParser::FormalParameterContext* ctx);

        explicit FormalParameter(MaikuroGrammar::MaikuroParser::LastFormalParameterContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TypePtr& getType() const;

        const TokenPtr& getVariadic() const;

        const IdentifierPtr& getIdentifier() const;

     private:
        TypePtr       _type;
        TokenPtr      _variadic;
        IdentifierPtr _identifier;
    };

    typedef std::shared_ptr<FormalParameter> FormalParameterPtr;
    typedef std::vector<FormalParameterPtr>  FormalParameterPtrVec;

    class FormalParameterList : public AstNode {
     public:
        FormalParameterList(FormalParameterPtrVec parameters, TokenPtrVec commas);

        explicit FormalParameterList(MaikuroGrammar::MaikuroParser::FormalParameterListContext* ctx);

        int getLine() override {
            return _parameters[0]->getLine();
        }

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const FormalParameterPtrVec& getParameters() const;

        const TokenPtrVec& getCommas() const;

     private:
        FormalParameterPtrVec _parameters;
        TokenPtrVec           _commas;
    };

    typedef std::shared_ptr<FormalParameterList> FormalParameterListPtr;
    typedef std::vector<FormalParameterListPtr>  FormalParameterListPtrVec;

    class FormalParameters : public AstNode {
     public:
        FormalParameters(TokenPtr leftPar, FormalParameterListPtr parameters, TokenPtr rightPar);

        explicit FormalParameters(MaikuroGrammar::MaikuroParser::FormalParametersContext* ctx);

        int getLine() override {
            return _leftPar->getLine();
        }

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getLeftPar() const;

        const FormalParameterListPtr& getParameters() const;

        const TokenPtr& getRightPar() const;

     private:
        TokenPtr               _leftPar;
        FormalParameterListPtr _parameters;
        TokenPtr               _rightPar;
    };

    typedef std::shared_ptr<FormalParameters> FormalParametersPtr;
    typedef std::vector<FormalParametersPtr>  FormalParametersPtrVec;

    class FunctionHeader : public AstNode {
     public:
        FunctionHeader(
            TokenPtr fun,
            IdentifierPtr identifier,
            FormalParametersPtr parameters,
            TokenPtr colon,
            TypePtr returnType
        );

        explicit FunctionHeader(MaikuroGrammar::MaikuroParser::FunctionHeaderContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getFun() const;

        const IdentifierPtr& getIdentifier() const;

        const FormalParametersPtr& getParameters() const;

        const TokenPtr& getColon() const;

        const TypePtr& getReturnType() const;

     private:
        TokenPtr            _fun;
        IdentifierPtr       _identifier;
        FormalParametersPtr _parameters;
        TokenPtr            _colon;
        TypePtr             _returnType;
    };

    typedef std::shared_ptr<FunctionHeader> FunctionHeaderPtr;
    typedef std::vector<FunctionHeaderPtr>  FunctionHeaderPtrVec;

    class FunctionDeclaration : public Statement {
     public:
        FunctionDeclaration(AnnotationsPtrVec annotations, FunctionHeaderPtr functionHeader, BlockPtr block);

        explicit FunctionDeclaration(MaikuroGrammar::MaikuroParser::FunctionDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtrVec& getAnnotations() const;

        const FunctionHeaderPtr& getFunctionHeader() const;

        const BlockPtr& getBlock() const;

     private:
        AnnotationsPtrVec _annotations;
        FunctionHeaderPtr _functionHeader;
        BlockPtr          _block;
    };

    typedef std::shared_ptr<FunctionDeclaration> FunctionDeclarationPtr;
    typedef std::vector<FunctionDeclarationPtr>  FunctionDeclarationPtrVec;
}

