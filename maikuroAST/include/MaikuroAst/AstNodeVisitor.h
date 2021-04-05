#pragma once

namespace MaikuroAst {
    class AliasDeclaration;

    class Annotation;

    class Annotations;

    class Argument;

    class Arguments;

    class Block;

    class SuperClass;

    class SuperInterfaces;

    class PropertyDeclaration;

    class MethodDeclaration;

    class AnnotationMember;

    class ClassBody;

    class ClassDeclaration;

    class ExpressionList;

    class PrimaryExpression;

    class VariableNameExpression;

    class ParExpresion;

    class MethodCall;

    class DotExpression;

    class MethodCallExpression;

    class NewDeclaratorExpression;

    class SuffixExpression;

    class PrefixExpression;

    class BopExpression;

    class TernaryExpression;

    class MatchExpressionCase;

    class MatchExpression;

    class FormalParameter;

    class FormalParameterList;

    class FormalParameters;

    class FunctionHeader;

    class FunctionDeclaration;

    class NullLiteral;

    class BoolLiteral;

    class NumberLiteral;

    class CharLiteral;

    class StringLiteral;

    class Identifier;

    class TypeIdentifier;

    class VisibilityModifier;

    class PackageName;

    class PackageDeclaration;

    class ImportDeclaration;

    class SourceFile;

    class ReturnStatement;

    class ThrowStatement;

    class BreakStatement;

    class ContinueStatement;

    class IfStatement;

    class UnlessStatement;

    class WhileStatement;

    class UntilStatement;

    class LoopStatement;

    class DoWhileStatement;

    class ForControl;

    class ForStatement;

    class ForeachControl;

    class ForeachStatement;

    class CatchClause;

    class FinallyBlock;

    class TryStatement;

    class SwitchLabel;

    class SwitchBlockStatementGroup;

    class SwitchStatement;

    class Token;

    class Type;

    class TypeDeclaration;

    class VariableName;

    class VariableNameDeclaration;

    class VariableDeclarationExpression;

    class VariableDeclaration;

    class ExpressionStatement;

    class ClassMember;

    class Expression;

    class Statement;

    class Literal;

    class AstNodeVisitor {
     public:
        virtual void visit(std::shared_ptr<AliasDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<Annotation> node) = 0;

        virtual void visit(std::shared_ptr<Annotations> node) = 0;

        virtual void visit(std::shared_ptr<Argument> node) = 0;

        virtual void visit(std::shared_ptr<Arguments> node) = 0;

        virtual void visit(std::shared_ptr<Block> node) = 0;

        virtual void visit(std::shared_ptr<SuperClass> node) = 0;

        virtual void visit(std::shared_ptr<SuperInterfaces> node) = 0;

        virtual void visit(std::shared_ptr<PropertyDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<MethodDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<AnnotationMember> node) = 0;

        virtual void visit(std::shared_ptr<ClassBody> node) = 0;

        virtual void visit(std::shared_ptr<ClassDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<ExpressionList> node) = 0;

        virtual void visit(std::shared_ptr<PrimaryExpression> node) = 0;

        virtual void visit(std::shared_ptr<VariableNameExpression> node) = 0;

        virtual void visit(std::shared_ptr<ParExpresion> node) = 0;

        virtual void visit(std::shared_ptr<MethodCall> node) = 0;

        virtual void visit(std::shared_ptr<DotExpression> node) = 0;

        virtual void visit(std::shared_ptr<MethodCallExpression> node) = 0;

        virtual void visit(std::shared_ptr<NewDeclaratorExpression> node) = 0;

        virtual void visit(std::shared_ptr<SuffixExpression> node) = 0;

        virtual void visit(std::shared_ptr<PrefixExpression> node) = 0;

        virtual void visit(std::shared_ptr<BopExpression> node) = 0;

        virtual void visit(std::shared_ptr<TernaryExpression> node) = 0;

        virtual void visit(std::shared_ptr<MatchExpressionCase> node) = 0;

        virtual void visit(std::shared_ptr<MatchExpression> node) = 0;

        virtual void visit(std::shared_ptr<FormalParameter> node) = 0;

        virtual void visit(std::shared_ptr<FormalParameterList> node) = 0;

        virtual void visit(std::shared_ptr<FormalParameters> node) = 0;

        virtual void visit(std::shared_ptr<FunctionHeader> node) = 0;

        virtual void visit(std::shared_ptr<FunctionDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<NullLiteral> node) = 0;

        virtual void visit(std::shared_ptr<BoolLiteral> node) = 0;

        virtual void visit(std::shared_ptr<NumberLiteral> node) = 0;

        virtual void visit(std::shared_ptr<CharLiteral> node) = 0;

        virtual void visit(std::shared_ptr<StringLiteral> node) = 0;

        virtual void visit(std::shared_ptr<Identifier> node) = 0;

        virtual void visit(std::shared_ptr<TypeIdentifier> node) = 0;

        virtual void visit(std::shared_ptr<VisibilityModifier> node) = 0;

        virtual void visit(std::shared_ptr<PackageName> node) = 0;

        virtual void visit(std::shared_ptr<PackageDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<ImportDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<SourceFile> node) = 0;

        virtual void visit(std::shared_ptr<ReturnStatement> node) = 0;

        virtual void visit(std::shared_ptr<ThrowStatement> node) = 0;

        virtual void visit(std::shared_ptr<BreakStatement> node) = 0;

        virtual void visit(std::shared_ptr<ContinueStatement> node) = 0;

        virtual void visit(std::shared_ptr<IfStatement> node) = 0;

        virtual void visit(std::shared_ptr<UnlessStatement> node) = 0;

        virtual void visit(std::shared_ptr<WhileStatement> node) = 0;

        virtual void visit(std::shared_ptr<UntilStatement> node) = 0;

        virtual void visit(std::shared_ptr<LoopStatement> node) = 0;

        virtual void visit(std::shared_ptr<DoWhileStatement> node) = 0;

        virtual void visit(std::shared_ptr<ForControl> node) = 0;

        virtual void visit(std::shared_ptr<ForStatement> node) = 0;

        virtual void visit(std::shared_ptr<ForeachControl> node) = 0;

        virtual void visit(std::shared_ptr<ForeachStatement> node) = 0;

        virtual void visit(std::shared_ptr<CatchClause> node) = 0;

        virtual void visit(std::shared_ptr<FinallyBlock> node) = 0;

        virtual void visit(std::shared_ptr<TryStatement> node) = 0;

        virtual void visit(std::shared_ptr<SwitchLabel> node) = 0;

        virtual void visit(std::shared_ptr<SwitchBlockStatementGroup> node) = 0;

        virtual void visit(std::shared_ptr<SwitchStatement> node) = 0;

        virtual void visit(std::shared_ptr<Token> node) = 0;

        virtual void visit(std::shared_ptr<Type> node) = 0;

        virtual void visit(std::shared_ptr<TypeDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<VariableName> node) = 0;

        virtual void visit(std::shared_ptr<VariableNameDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<VariableDeclarationExpression> node) = 0;

        virtual void visit(std::shared_ptr<VariableDeclaration> node) = 0;

        virtual void visit(std::shared_ptr<ExpressionStatement> node) = 0;

        virtual void visit(std::shared_ptr<ClassMember> node) = 0;

        virtual void visit(std::shared_ptr<Expression> node) = 0;

        virtual void visit(std::shared_ptr<Statement> node) = 0;

        virtual void visit(std::shared_ptr<Literal> node) = 0;
    };

    class AstNodeBaseVisitor : public AstNodeVisitor {
     public:
        void visit(std::shared_ptr<AliasDeclaration> node) override {

        }

        void visit(std::shared_ptr<Annotation> node) override {

        }

        void visit(std::shared_ptr<Annotations> node) override {

        }

        void visit(std::shared_ptr<Argument> node) override {

        }

        void visit(std::shared_ptr<Arguments> node) override {

        }

        void visit(std::shared_ptr<Block> node) override {

        }

        void visit(std::shared_ptr<SuperClass> node) override {

        }

        void visit(std::shared_ptr<SuperInterfaces> node) override {

        }

        void visit(std::shared_ptr<PropertyDeclaration> node) override {

        }

        void visit(std::shared_ptr<MethodDeclaration> node) override {

        }

        void visit(std::shared_ptr<AnnotationMember> node) override {

        }

        void visit(std::shared_ptr<ClassBody> node) override {

        }

        void visit(std::shared_ptr<ClassDeclaration> node) override {

        }

        void visit(std::shared_ptr<ExpressionList> node) override {

        }

        void visit(std::shared_ptr<PrimaryExpression> node) override {

        }

        void visit(std::shared_ptr<VariableNameExpression> node) override {

        }

        void visit(std::shared_ptr<ParExpresion> node) override {

        }

        void visit(std::shared_ptr<MethodCall> node) override {

        }

        void visit(std::shared_ptr<DotExpression> node) override {

        }

        void visit(std::shared_ptr<MethodCallExpression> node) override {

        }

        void visit(std::shared_ptr<NewDeclaratorExpression> node) override {

        }

        void visit(std::shared_ptr<SuffixExpression> node) override {

        }

        void visit(std::shared_ptr<PrefixExpression> node) override {

        }

        void visit(std::shared_ptr<BopExpression> node) override {

        }

        void visit(std::shared_ptr<TernaryExpression> node) override {

        }

        void visit(std::shared_ptr<MatchExpressionCase> node) override {

        }

        void visit(std::shared_ptr<MatchExpression> node) override {

        }

        void visit(std::shared_ptr<FormalParameter> node) override {

        }

        void visit(std::shared_ptr<FormalParameterList> node) override {

        }

        void visit(std::shared_ptr<FormalParameters> node) override {

        }

        void visit(std::shared_ptr<FunctionHeader> node) override {

        }

        void visit(std::shared_ptr<FunctionDeclaration> node) override {

        }

        void visit(std::shared_ptr<NullLiteral> node) override {

        }

        void visit(std::shared_ptr<BoolLiteral> node) override {

        }

        void visit(std::shared_ptr<NumberLiteral> node) override {

        }

        void visit(std::shared_ptr<CharLiteral> node) override {

        }

        void visit(std::shared_ptr<StringLiteral> node) override {

        }

        void visit(std::shared_ptr<Identifier> node) override {

        }

        void visit(std::shared_ptr<TypeIdentifier> node) override {

        }

        void visit(std::shared_ptr<VisibilityModifier> node) override {

        }

        void visit(std::shared_ptr<PackageName> node) override {

        }

        void visit(std::shared_ptr<PackageDeclaration> node) override {

        }

        void visit(std::shared_ptr<ImportDeclaration> node) override {

        }

        void visit(std::shared_ptr<SourceFile> node) override {

        }

        void visit(std::shared_ptr<ReturnStatement> node) override {

        }

        void visit(std::shared_ptr<ThrowStatement> node) override {

        }

        void visit(std::shared_ptr<BreakStatement> node) override {

        }

        void visit(std::shared_ptr<ContinueStatement> node) override {

        }

        void visit(std::shared_ptr<IfStatement> node) override {

        }

        void visit(std::shared_ptr<UnlessStatement> node) override {

        }

        void visit(std::shared_ptr<WhileStatement> node) override {

        }

        void visit(std::shared_ptr<UntilStatement> node) override {

        }

        void visit(std::shared_ptr<LoopStatement> node) override {

        }

        void visit(std::shared_ptr<DoWhileStatement> node) override {

        }

        void visit(std::shared_ptr<ForControl> node) override {

        }

        void visit(std::shared_ptr<ForStatement> node) override {

        }

        void visit(std::shared_ptr<ForeachControl> node) override {

        }

        void visit(std::shared_ptr<ForeachStatement> node) override {

        }

        void visit(std::shared_ptr<CatchClause> node) override {

        }

        void visit(std::shared_ptr<FinallyBlock> node) override {

        }

        void visit(std::shared_ptr<TryStatement> node) override {

        }

        void visit(std::shared_ptr<SwitchLabel> node) override {

        }

        void visit(std::shared_ptr<SwitchBlockStatementGroup> node) override {

        }

        void visit(std::shared_ptr<SwitchStatement> node) override {

        }

        void visit(std::shared_ptr<Token> node) override {

        }

        void visit(std::shared_ptr<Type> node) override {

        }

        void visit(std::shared_ptr<TypeDeclaration> node) override {

        }

        void visit(std::shared_ptr<VariableName> node) override {

        }

        void visit(std::shared_ptr<VariableNameDeclaration> node) override {

        }

        void visit(std::shared_ptr<VariableDeclarationExpression> node) override {

        }

        void visit(std::shared_ptr<VariableDeclaration> node) override {

        }

        void visit(std::shared_ptr<ExpressionStatement> node) override {

        }

        void visit(std::shared_ptr<ClassMember> node) override {

        }

        void visit(std::shared_ptr<Expression> node) override {

        }

        void visit(std::shared_ptr<Statement> node) override {

        }

        void visit(std::shared_ptr<Literal> node) override {

        }
    };
}