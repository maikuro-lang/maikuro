#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Block.h"
#include "Type.h"
#include "Expression.h"
#include "Function.h"
#include "Argument.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"

namespace MaikuroAst {
    class SuperClass : public MaikuroAst::AstNode {
     public:
        SuperClass(TokenPtr extendsToken, TypeIdentifierPtr className);

        explicit SuperClass(MaikuroParser::SuperClassContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr          _extendsToken;
        TypeIdentifierPtr _className;
    };

    typedef shared_ptr<SuperClass>      SuperClassPtr;

    class SuperInterfaces : public MaikuroAst::AstNode {
     public:
        SuperInterfaces(
            TokenPtr implementsToken,
            TypeIdentifierPtrVec interfaceNames,
            TokenPtrVec commas
        );

        explicit SuperInterfaces(MaikuroParser::SuperInterfacesContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr             _implementsToken;
        TypeIdentifierPtrVec _interfaceNames;
        TokenPtrVec          _commas;
    };

    typedef shared_ptr<SuperInterfaces> SuperInterfacesPtr;

    class ClassMember : public MaikuroAst::AstNode {
    };

    typedef shared_ptr<ClassMember>         ClassMemberPtr;
    typedef vector<ClassMemberPtr>          ClassMemberPtrVec;

    class PropertyDeclaration : public ClassMember {
     public:
        PropertyDeclaration(
            AnnotationsPtrVec annotations,
            VisibilityModifierPtr visibility,
            TypeDeclarationPtr typeDeclaration,
            IdentifierPtr identifier,
            TokenPtr assignToken,
            ExpressionPtr expression,
            TokenPtr colon
        );

        explicit PropertyDeclaration(MaikuroParser::PropertyDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        AnnotationsPtrVec _annotations;
        VisibilityModifierPtr         _visibility;
        TypeDeclarationPtr    _typeDeclaration;
        IdentifierPtr         _identifier;
        TokenPtr                  _assignToken;
        ExpressionPtr _expression;
        TokenPtr                  _colon;
    };

    typedef shared_ptr<PropertyDeclaration> PropertyDeclarationPtr;

    class MethodDeclaration : public ClassMember {
     public:
        MethodDeclaration(
            AnnotationsPtrVec annotations,
            VisibilityModifierPtr visibility,
            FunctionHeaderPtr functionHeader,
            BlockPtr block
        );

        explicit MethodDeclaration(MaikuroParser::MethodDeclarationContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        AnnotationsPtrVec _annotations;
        VisibilityModifierPtr         _visibility;
        FunctionHeaderPtr    _functionHeader;
        BlockPtr _block;
    };

    typedef shared_ptr<MethodDeclaration>   MethodDeclarationPtr;

    class AnnotationMember : public ClassMember {
     public:
        explicit AnnotationMember(AnnotationsPtr annotations);

        explicit AnnotationMember(MaikuroParser::AnnotationsContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        AnnotationsPtr _annotations;
    };

    typedef shared_ptr<AnnotationMember>    AnnotationMemberPtr;

    class ClassBody : public MaikuroAst::AstNode {
     public:
        ClassBody(TokenPtr leftBra, ClassMemberPtrVec classMembers, TokenPtr rightBra);

        explicit ClassBody(MaikuroParser::ClassBodyContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr          _leftBra;
        ClassMemberPtrVec _classMembers;
        TokenPtr          _rightBra;
    };

    typedef shared_ptr<ClassBody>           ClassBodyPtr;

    class ClassDeclaration : public Statement {
     public:
        ClassDeclaration(
            AnnotationsPtrVec annotations,
            TokenPtr classToken,
            TypeIdentifierPtr typeIdentifier,
            SuperClassPtr superClass,
            SuperInterfacesPtr superInterfaces,
            ClassBodyPtr classBody
        );

        explicit ClassDeclaration(MaikuroParser::ClassDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        AnnotationsPtrVec _annotations;
        TokenPtr                      _classToken;
        TypeIdentifierPtr  _className;
        SuperClassPtr      _superClass;
        SuperInterfacesPtr _superInterfaces;
        ClassBodyPtr       _classBody;
    };

    typedef shared_ptr<ClassDeclaration>    ClassDeclarationPtr;
}


