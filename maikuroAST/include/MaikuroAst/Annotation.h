#pragma once

#include "common.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"

namespace MaikuroAst {

    class Arguments;
    typedef std::shared_ptr<Arguments> ArgumentsPtr;

    class Annotation : public AstNode {
     public:
        Annotation(TypeIdentifierPtr typeIdentifier, ArgumentsPtr arguments);

        explicit Annotation(MaikuroGrammar::MaikuroParser::AnnotationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TypeIdentifierPtr& getTypeIdentifier() const;

        const ArgumentsPtr& getArguments() const;

     private:
        TypeIdentifierPtr _typeIdentifier;
        ArgumentsPtr      _arguments;
    };

    typedef std::shared_ptr<Annotation> AnnotationPtr;
    typedef std::vector<AnnotationPtr>  AnnotationPtrVec;

    class Annotations : public AstNode {
     public:
        Annotations(TokenPtr prefix, AnnotationPtrVec annotations, TokenPtrVec commas, TokenPtr closeBracket);

        explicit Annotations(MaikuroGrammar::MaikuroParser::AnnotationsContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getPrefix() const;

        const AnnotationPtrVec& getAnnotations() const;

        const TokenPtrVec& getCommas() const;

        const TokenPtr& getCloseBracket() const;

     private:
        TokenPtr         _prefix;
        AnnotationPtrVec _annotations;
        TokenPtrVec      _commas;
        TokenPtr         _closeBracket;
    };

    typedef std::shared_ptr<Annotations> AnnotationsPtr;
    typedef std::vector<AnnotationsPtr>  AnnotationsPtrVec;
}

