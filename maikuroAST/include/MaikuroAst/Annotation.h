#pragma once

#include "common.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"

namespace MaikuroAst {
    class Arguments;

    typedef shared_ptr<Arguments>   ArgumentsPtr;

    class Annotation : public AstNode {
     public:
        Annotation(TypeIdentifierPtr typeIdentifier, ArgumentsPtr arguments);

        explicit Annotation(MaikuroParser::AnnotationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TypeIdentifierPtr _typeIdentifier;
        ArgumentsPtr      _arguments;
    };

    typedef shared_ptr<Annotation>  AnnotationPtr;
    typedef vector<AnnotationPtr>   AnnotationPtrVec;

    class Annotations : public AstNode {
     public:
        Annotations(TokenPtr prefix, AnnotationPtrVec annotations, TokenPtrVec commas, TokenPtr closeBracket);

        explicit Annotations(MaikuroParser::AnnotationsContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr         _prefix;
        AnnotationPtrVec _annotations;
        TokenPtrVec      _commas;
        TokenPtr         _closeBracket;
    };

    typedef shared_ptr<Annotations> AnnotationsPtr;
    typedef vector<AnnotationsPtr>  AnnotationsPtrVec;
}

