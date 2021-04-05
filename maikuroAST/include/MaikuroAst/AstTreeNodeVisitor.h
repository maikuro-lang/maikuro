#pragma once

#include "AstNodeVisitor.h"
#include "AstNode.h"

namespace MaikuroAst {
    class AstTreeNodeVisitor : public AstNodeVisitor {
     public:
        virtual AstNodeVisitor* getVisitor(AstNode* node) = 0;
        virtual AstNodeVisitor* getChildVisitor(AstNode* node) = 0;

        void visit(AliasDeclaration* node) override;

        void visit(Annotation* node) override;

        void visit(Annotations* node) override;

        void visit(Argument* node) override;

        void visit(Arguments* node) override;

        void visit(Block* node) override;

        void visit(SuperClass* node) override;

        void visit(SuperInterfaces* node) override;

        void visit(PropertyDeclaration* node) override;

        void visit(MethodDeclaration* node) override;

        void visit(AnnotationMember* node) override;

        void visit(ClassBody* node) override;

        void visit(ClassDeclaration* node) override;

        void visit(ExpressionList* node) override;

        void visit(PrimaryExpression* node) override;

        void visit(VariableNameExpression* node) override;

        void visit(ParExpresion* node) override;

        void visit(MethodCall* node) override;

        void visit(DotExpression* node) override;

        void visit(MethodCallExpression* node) override;

        void visit(NewDeclaratorExpression* node) override;

        void visit(SuffixExpression* node) override;

        void visit(PrefixExpression* node) override;

        void visit(BopExpression* node) override;

        void visit(TernaryExpression* node) override;

        void visit(MatchExpressionCase* node) override;

        void visit(MatchExpression* node) override;

        void visit(FormalParameter* node) override;

        void visit(FormalParameterList* node) override;

        void visit(FormalParameters* node) override;

        void visit(FunctionHeader* node) override;

        void visit(FunctionDeclaration* node) override;

        void visit(NullLiteral* node) override;

        void visit(BoolLiteral* node) override;

        void visit(NumberLiteral* node) override;

        void visit(CharLiteral* node) override;

        void visit(StringLiteral* node) override;

        void visit(Identifier* node) override;

        void visit(TypeIdentifier* node) override;

        void visit(VisibilityModifier* node) override;

        void visit(PackageName* node) override;

        void visit(PackageDeclaration* node) override;

        void visit(ImportDeclaration* node) override;

        void visit(SourceFile* node) override;

        void visit(ReturnStatement* node) override;

        void visit(ThrowStatement* node) override;

        void visit(BreakStatement* node) override;

        void visit(ContinueStatement* node) override;

        void visit(IfStatement* node) override;

        void visit(UnlessStatement* node) override;

        void visit(WhileStatement* node) override;

        void visit(UntilStatement* node) override;

        void visit(LoopStatement* node) override;

        void visit(DoWhileStatement* node) override;

        void visit(ForControl* node) override;

        void visit(ForStatement* node) override;

        void visit(ForeachControl* node) override;

        void visit(ForeachStatement* node) override;

        void visit(CatchClause* node) override;

        void visit(FinallyBlock* node) override;

        void visit(TryStatement* node) override;

        void visit(SwitchLabel* node) override;

        void visit(SwitchBlockStatementGroup* node) override;

        void visit(SwitchStatement* node) override;

        void visit(Token* node) override;

        void visit(Type* node) override;

        void visit(TypeDeclaration* node) override;

        void visit(VariableName* node) override;

        void visit(VariableNameDeclaration* node) override;

        void visit(VariableDeclarationExpression* node) override;

        void visit(VariableDeclaration* node) override;

        void visit(ExpressionStatement* node) override;

        void visit(ClassMember* node) override;

        void visit(Expression* node) override;

        void visit(Statement* node) override;

        void visit(Literal* node) override;
    };

    class SimpleAstTreeNodeVisitor : public AstTreeNodeVisitor {
     public:
        explicit SimpleAstTreeNodeVisitor(AstNodeVisitor* visitor);

        AstNodeVisitor* getVisitor(AstNode* node) override;

        AstNodeVisitor* getChildVisitor(AstNode* node) override;

     private:
        AstNodeVisitor* _visitor;
    };
}