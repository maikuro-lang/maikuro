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
        virtual void visit(AliasDeclaration* node) = 0;

        virtual void visit(Annotation* node) = 0;

        virtual void visit(Annotations* node) = 0;

        virtual void visit(Argument* node) = 0;

        virtual void visit(Arguments* node) = 0;

        virtual void visit(Block* node) = 0;

        virtual void visit(SuperClass* node) = 0;

        virtual void visit(SuperInterfaces* node) = 0;

        virtual void visit(PropertyDeclaration* node) = 0;

        virtual void visit(MethodDeclaration* node) = 0;

        virtual void visit(AnnotationMember* node) = 0;

        virtual void visit(ClassBody* node) = 0;

        virtual void visit(ClassDeclaration* node) = 0;

        virtual void visit(ExpressionList* node) = 0;

        virtual void visit(PrimaryExpression* node) = 0;

        virtual void visit(VariableNameExpression* node) = 0;

        virtual void visit(ParExpresion* node) = 0;

        virtual void visit(MethodCall* node) = 0;

        virtual void visit(DotExpression* node) = 0;

        virtual void visit(MethodCallExpression* node) = 0;

        virtual void visit(NewDeclaratorExpression* node) = 0;

        virtual void visit(SuffixExpression* node) = 0;

        virtual void visit(PrefixExpression* node) = 0;

        virtual void visit(BopExpression* node) = 0;

        virtual void visit(TernaryExpression* node) = 0;

        virtual void visit(MatchExpressionCase* node) = 0;

        virtual void visit(MatchExpression* node) = 0;

        virtual void visit(FormalParameter* node) = 0;

        virtual void visit(FormalParameterList* node) = 0;

        virtual void visit(FormalParameters* node) = 0;

        virtual void visit(FunctionHeader* node) = 0;

        virtual void visit(FunctionDeclaration* node) = 0;

        virtual void visit(NullLiteral* node) = 0;

        virtual void visit(BoolLiteral* node) = 0;

        virtual void visit(NumberLiteral* node) = 0;

        virtual void visit(CharLiteral* node) = 0;

        virtual void visit(StringLiteral* node) = 0;

        virtual void visit(Identifier* node) = 0;

        virtual void visit(TypeIdentifier* node) = 0;

        virtual void visit(VisibilityModifier* node) = 0;

        virtual void visit(PackageName* node) = 0;

        virtual void visit(PackageDeclaration* node) = 0;

        virtual void visit(ImportDeclaration* node) = 0;

        virtual void visit(SourceFile* node) = 0;

        virtual void visit(ReturnStatement* node) = 0;

        virtual void visit(ThrowStatement* node) = 0;

        virtual void visit(BreakStatement* node) = 0;

        virtual void visit(ContinueStatement* node) = 0;

        virtual void visit(IfStatement* node) = 0;

        virtual void visit(UnlessStatement* node) = 0;

        virtual void visit(WhileStatement* node) = 0;

        virtual void visit(UntilStatement* node) = 0;

        virtual void visit(LoopStatement* node) = 0;

        virtual void visit(DoWhileStatement* node) = 0;

        virtual void visit(ForControl* node) = 0;

        virtual void visit(ForStatement* node) = 0;

        virtual void visit(ForeachControl* node) = 0;

        virtual void visit(ForeachStatement* node) = 0;

        virtual void visit(CatchClause* node) = 0;

        virtual void visit(FinallyBlock* node) = 0;

        virtual void visit(TryStatement* node) = 0;

        virtual void visit(SwitchLabel* node) = 0;

        virtual void visit(SwitchBlockStatementGroup* node) = 0;

        virtual void visit(SwitchStatement* node) = 0;

        virtual void visit(Token* node) = 0;

        virtual void visit(Type* node) = 0;

        virtual void visit(TypeDeclaration* node) = 0;

        virtual void visit(VariableName* node) = 0;

        virtual void visit(VariableNameDeclaration* node) = 0;

        virtual void visit(VariableDeclarationExpression* node) = 0;

        virtual void visit(VariableDeclaration* node) = 0;

        virtual void visit(ExpressionStatement* node) = 0;

        virtual void visit(ClassMember* node) = 0;

        virtual void visit(Expression* node) = 0;

        virtual void visit(Statement* node) = 0;

        virtual void visit(Literal* node) = 0;
    };

    class AstNodeBaseVisitor : public AstNodeVisitor {
     public:
        void visit(AliasDeclaration* node) override {

        }

        void visit(Annotation* node) override {

        }

        void visit(Annotations* node) override {

        }

        void visit(Argument* node) override {

        }

        void visit(Arguments* node) override {

        }

        void visit(Block* node) override {

        }

        void visit(SuperClass* node) override {

        }

        void visit(SuperInterfaces* node) override {

        }

        void visit(PropertyDeclaration* node) override {

        }

        void visit(MethodDeclaration* node) override {

        }

        void visit(AnnotationMember* node) override {

        }

        void visit(ClassBody* node) override {

        }

        void visit(ClassDeclaration* node) override {

        }

        void visit(ExpressionList* node) override {

        }

        void visit(PrimaryExpression* node) override {

        }

        void visit(VariableNameExpression* node) override {

        }

        void visit(ParExpresion* node) override {

        }

        void visit(MethodCall* node) override {

        }

        void visit(DotExpression* node) override {

        }

        void visit(MethodCallExpression* node) override {

        }

        void visit(NewDeclaratorExpression* node) override {

        }

        void visit(SuffixExpression* node) override {

        }

        void visit(PrefixExpression* node) override {

        }

        void visit(BopExpression* node) override {

        }

        void visit(TernaryExpression* node) override {

        }

        void visit(MatchExpressionCase* node) override {

        }

        void visit(MatchExpression* node) override {

        }

        void visit(FormalParameter* node) override {

        }

        void visit(FormalParameterList* node) override {

        }

        void visit(FormalParameters* node) override {

        }

        void visit(FunctionHeader* node) override {

        }

        void visit(FunctionDeclaration* node) override {

        }

        void visit(NullLiteral* node) override {

        }

        void visit(BoolLiteral* node) override {

        }

        void visit(NumberLiteral* node) override {

        }

        void visit(CharLiteral* node) override {

        }

        void visit(StringLiteral* node) override {

        }

        void visit(Identifier* node) override {

        }

        void visit(TypeIdentifier* node) override {

        }

        void visit(VisibilityModifier* node) override {

        }

        void visit(PackageName* node) override {

        }

        void visit(PackageDeclaration* node) override {

        }

        void visit(ImportDeclaration* node) override {

        }

        void visit(SourceFile* node) override {

        }

        void visit(ReturnStatement* node) override {

        }

        void visit(ThrowStatement* node) override {

        }

        void visit(BreakStatement* node) override {

        }

        void visit(ContinueStatement* node) override {

        }

        void visit(IfStatement* node) override {

        }

        void visit(UnlessStatement* node) override {

        }

        void visit(WhileStatement* node) override {

        }

        void visit(UntilStatement* node) override {

        }

        void visit(LoopStatement* node) override {

        }

        void visit(DoWhileStatement* node) override {

        }

        void visit(ForControl* node) override {

        }

        void visit(ForStatement* node) override {

        }

        void visit(ForeachControl* node) override {

        }

        void visit(ForeachStatement* node) override {

        }

        void visit(CatchClause* node) override {

        }

        void visit(FinallyBlock* node) override {

        }

        void visit(TryStatement* node) override {

        }

        void visit(SwitchLabel* node) override {

        }

        void visit(SwitchBlockStatementGroup* node) override {

        }

        void visit(SwitchStatement* node) override {

        }

        void visit(Token* node) override {

        }

        void visit(Type* node) override {

        }

        void visit(TypeDeclaration* node) override {

        }

        void visit(VariableName* node) override {

        }

        void visit(VariableNameDeclaration* node) override {

        }

        void visit(VariableDeclarationExpression* node) override {

        }

        void visit(VariableDeclaration* node) override {

        }

        void visit(ExpressionStatement* node) override {

        }

        void visit(ClassMember* node) override {

        }

        void visit(Expression* node) override {

        }

        void visit(Statement* node) override {

        }

        void visit(Literal* node) override {

        }
    };
}