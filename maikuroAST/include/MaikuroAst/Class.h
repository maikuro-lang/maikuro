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

    class SuperClass : public AstNode {
     public:
        SuperClass(TokenPtr extendsToken, TypeIdentifierPtr className);

        explicit SuperClass(MaikuroGrammar::MaikuroParser::SuperClassContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getExtendsToken() const;

        const TypeIdentifierPtr& getClassName() const;

     private:
        TokenPtr          _extendsToken;
        TypeIdentifierPtr _className;
    };

    typedef std::shared_ptr<SuperClass> SuperClassPtr;

    class SuperInterfaces : public AstNode {
     public:
        SuperInterfaces(
            TokenPtr implementsToken,
            TypeIdentifierPtrVec interfaceNames,
            TokenPtrVec commas
        );

        explicit SuperInterfaces(MaikuroGrammar::MaikuroParser::SuperInterfacesContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getImplementsToken() const;

        const TypeIdentifierPtrVec& getInterfaceNames() const;

        const TokenPtrVec& getCommas() const;

     private:
        TokenPtr             _implementsToken;
        TypeIdentifierPtrVec _interfaceNames;
        TokenPtrVec          _commas;
    };

    typedef std::shared_ptr<SuperInterfaces> SuperInterfacesPtr;

    class ClassMember : public AstNode {
     public:
        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<ClassMember> ClassMemberPtr;
    typedef std::vector<ClassMemberPtr>  ClassMemberPtrVec;

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

        explicit PropertyDeclaration(MaikuroGrammar::MaikuroParser::PropertyDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtrVec& getAnnotations() const;

        const VisibilityModifierPtr& getVisibility() const;

        const TypeDeclarationPtr& getTypeDeclaration() const;

        const IdentifierPtr& getIdentifier() const;

        const TokenPtr& getAssignToken() const;

        const ExpressionPtr& getExpression() const;

        const TokenPtr& getColon() const;

     private:
        AnnotationsPtrVec     _annotations;
        VisibilityModifierPtr _visibility;
        TypeDeclarationPtr    _typeDeclaration;
        IdentifierPtr         _identifier;
        TokenPtr              _assignToken;
        ExpressionPtr         _expression;
        TokenPtr              _colon;
    };

    typedef std::shared_ptr<PropertyDeclaration> PropertyDeclarationPtr;

    class MethodDeclaration : public ClassMember {
     public:
        MethodDeclaration(
            AnnotationsPtrVec annotations,
            VisibilityModifierPtr visibility,
            FunctionHeaderPtr functionHeader,
            BlockPtr block
        );

        explicit MethodDeclaration(MaikuroGrammar::MaikuroParser::MethodDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtrVec& getAnnotations() const;

        const VisibilityModifierPtr& getVisibility() const;

        const FunctionHeaderPtr& getFunctionHeader() const;

        const BlockPtr& getBlock() const;

     private:
        AnnotationsPtrVec     _annotations;
        VisibilityModifierPtr _visibility;
        FunctionHeaderPtr     _functionHeader;
        BlockPtr              _block;
    };

    typedef std::shared_ptr<MethodDeclaration> MethodDeclarationPtr;

    class AnnotationMember : public ClassMember {
     public:
        explicit AnnotationMember(AnnotationsPtr annotations);

        explicit AnnotationMember(MaikuroGrammar::MaikuroParser::AnnotationsContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtr& getAnnotations() const;

     private:
        AnnotationsPtr _annotations;
    };

    typedef std::shared_ptr<AnnotationMember> AnnotationMemberPtr;

    class ClassBody : public AstNode {
     public:
        ClassBody(TokenPtr leftBra, ClassMemberPtrVec classMembers, TokenPtr rightBra);

        explicit ClassBody(MaikuroGrammar::MaikuroParser::ClassBodyContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getLeftBra() const;

        const ClassMemberPtrVec& getClassMembers() const;

        const TokenPtr& getRightBra() const;

     private:
        TokenPtr          _leftBra;
        ClassMemberPtrVec _classMembers;
        TokenPtr          _rightBra;
    };

    typedef std::shared_ptr<ClassBody> ClassBodyPtr;

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

        explicit ClassDeclaration(MaikuroGrammar::MaikuroParser::ClassDeclarationContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtrVec& getAnnotations() const;

        const TokenPtr& getClassToken() const;

        const TypeIdentifierPtr& getClassName() const;

        const SuperClassPtr& getSuperClass() const;

        const SuperInterfacesPtr& getSuperInterfaces() const;

        const ClassBodyPtr& getClassBody() const;

     private:
        AnnotationsPtrVec  _annotations;
        TokenPtr           _classToken;
        TypeIdentifierPtr  _className;
        SuperClassPtr      _superClass;
        SuperInterfacesPtr _superInterfaces;
        ClassBodyPtr       _classBody;
    };

    typedef std::shared_ptr<ClassDeclaration> ClassDeclarationPtr;
}


