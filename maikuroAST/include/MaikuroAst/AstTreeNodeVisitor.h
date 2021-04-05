#pragma once

#include "AstNodeVisitor.h"
#include "AstNode.h"

namespace MaikuroAst {
    class AstTreeNodeVisitor : public AstNodeVisitor {
     public:
        virtual AstNodeVisitor* getVisitor(std::shared_ptr<AstNode> node) = 0;
        virtual AstNodeVisitor* getChildVisitor(std::shared_ptr<AstNode> node) = 0;

        void visit(std::shared_ptr<AliasDeclaration> node) override;

        void visit(std::shared_ptr<Annotation> node) override;

        void visit(std::shared_ptr<Annotations> node) override;

        void visit(std::shared_ptr<Argument> node) override;

        void visit(std::shared_ptr<Arguments> node) override;

        void visit(std::shared_ptr<Block> node) override;

        void visit(std::shared_ptr<SuperClass> node) override;

        void visit(std::shared_ptr<SuperInterfaces> node) override;

        void visit(std::shared_ptr<PropertyDeclaration> node) override;

        void visit(std::shared_ptr<MethodDeclaration> node) override;

        void visit(std::shared_ptr<AnnotationMember> node) override;

        void visit(std::shared_ptr<ClassBody> node) override;

        void visit(std::shared_ptr<ClassDeclaration> node) override;

        void visit(std::shared_ptr<ExpressionList> node) override;

        void visit(std::shared_ptr<PrimaryExpression> node) override;

        void visit(std::shared_ptr<VariableNameExpression> node) override;

        void visit(std::shared_ptr<ParExpresion> node) override;

        void visit(std::shared_ptr<MethodCall> node) override;

        void visit(std::shared_ptr<DotExpression> node) override;

        void visit(std::shared_ptr<MethodCallExpression> node) override;

        void visit(std::shared_ptr<NewDeclaratorExpression> node) override;

        void visit(std::shared_ptr<SuffixExpression> node) override;

        void visit(std::shared_ptr<PrefixExpression> node) override;

        void visit(std::shared_ptr<BopExpression> node) override;

        void visit(std::shared_ptr<TernaryExpression> node) override;

        void visit(std::shared_ptr<MatchExpressionCase> node) override;

        void visit(std::shared_ptr<MatchExpression> node) override;

        void visit(std::shared_ptr<FormalParameter> node) override;

        void visit(std::shared_ptr<FormalParameterList> node) override;

        void visit(std::shared_ptr<FormalParameters> node) override;

        void visit(std::shared_ptr<FunctionHeader> node) override;

        void visit(std::shared_ptr<FunctionDeclaration> node) override;

        void visit(std::shared_ptr<NullLiteral> node) override;

        void visit(std::shared_ptr<BoolLiteral> node) override;

        void visit(std::shared_ptr<NumberLiteral> node) override;

        void visit(std::shared_ptr<CharLiteral> node) override;

        void visit(std::shared_ptr<StringLiteral> node) override;

        void visit(std::shared_ptr<Identifier> node) override;

        void visit(std::shared_ptr<TypeIdentifier> node) override;

        void visit(std::shared_ptr<VisibilityModifier> node) override;

        void visit(std::shared_ptr<PackageName> node) override;

        void visit(std::shared_ptr<PackageDeclaration> node) override;

        void visit(std::shared_ptr<ImportDeclaration> node) override;

        void visit(std::shared_ptr<SourceFile> node) override;

        void visit(std::shared_ptr<ReturnStatement> node) override;

        void visit(std::shared_ptr<ThrowStatement> node) override;

        void visit(std::shared_ptr<BreakStatement> node) override;

        void visit(std::shared_ptr<ContinueStatement> node) override;

        void visit(std::shared_ptr<IfStatement> node) override;

        void visit(std::shared_ptr<UnlessStatement> node) override;

        void visit(std::shared_ptr<WhileStatement> node) override;

        void visit(std::shared_ptr<UntilStatement> node) override;

        void visit(std::shared_ptr<LoopStatement> node) override;

        void visit(std::shared_ptr<DoWhileStatement> node) override;

        void visit(std::shared_ptr<ForControl> node) override;

        void visit(std::shared_ptr<ForStatement> node) override;

        void visit(std::shared_ptr<ForeachControl> node) override;

        void visit(std::shared_ptr<ForeachStatement> node) override;

        void visit(std::shared_ptr<CatchClause> node) override;

        void visit(std::shared_ptr<FinallyBlock> node) override;

        void visit(std::shared_ptr<TryStatement> node) override;

        void visit(std::shared_ptr<SwitchLabel> node) override;

        void visit(std::shared_ptr<SwitchBlockStatementGroup> node) override;

        void visit(std::shared_ptr<SwitchStatement> node) override;

        void visit(std::shared_ptr<Token> node) override;

        void visit(std::shared_ptr<Type> node) override;

        void visit(std::shared_ptr<TypeDeclaration> node) override;

        void visit(std::shared_ptr<VariableName> node) override;

        void visit(std::shared_ptr<VariableNameDeclaration> node) override;

        void visit(std::shared_ptr<VariableDeclarationExpression> node) override;

        void visit(std::shared_ptr<VariableDeclaration> node) override;

        void visit(std::shared_ptr<ExpressionStatement> node) override;

        void visit(std::shared_ptr<ClassMember> node) override;

        void visit(std::shared_ptr<Expression> node) override;

        void visit(std::shared_ptr<Statement> node) override;

        void visit(std::shared_ptr<Literal> node) override;
    };

    class SimpleAstTreeNodeVisitor : public AstTreeNodeVisitor {
     public:
        explicit SimpleAstTreeNodeVisitor(AstNodeVisitor* visitor);

        AstNodeVisitor* getVisitor(std::shared_ptr<AstNode> node) override;

        AstNodeVisitor* getChildVisitor(std::shared_ptr<AstNode> node) override;

     private:
        AstNodeVisitor* _visitor;
    };
}