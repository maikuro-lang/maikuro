#pragma once

#include "AstTreeVisitor.h"

namespace MaikuroAst::Tree {
    using MaikuroAst::AstNode;

    template<typename ReturnType>
    class AstTreeBaseVisitor : public AstTreeVisitor<ReturnType> {
     public:
        ReturnType visit(AliasDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(AnnotationPtr node) override {
            return nullptr;
        }

        ReturnType visit(AnnotationsPtr node) override {
            return nullptr;
        }

        ReturnType visit(ArgumentPtr node) override {
            return nullptr;
        }

        ReturnType visit(ArgumentsPtr node) override {
            return nullptr;
        }

        ReturnType visit(BlockPtr node) override {
            return nullptr;
        }

        ReturnType visit(SuperClassPtr node) override {
            return nullptr;
        }

        ReturnType visit(SuperInterfacesPtr node) override {
            return nullptr;
        }

        ReturnType visit(ClassMemberPtr node) override {
            return nullptr;
        }

        ReturnType visit(PropertyDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(MethodDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(AnnotationMemberPtr node) override {
            return nullptr;
        }

        ReturnType visit(ClassBodyPtr node) override {
            return nullptr;
        }

        ReturnType visit(ClassDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(ExpressionListPtr node) override {
            return nullptr;
        }

        ReturnType visit(PrimaryExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(VariableNameExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(ParExpresionPtr node) override {
            return nullptr;
        }

        ReturnType visit(MethodCallPtr node) override {
            return nullptr;
        }

        ReturnType visit(DotExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(MethodCallExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(NewDeclaratorExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(SuffixExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(PrefixExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(BopExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(TernaryExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(MatchExpressionCasePtr node) override {
            return nullptr;
        }

        ReturnType visit(MatchExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(FormalParameterPtr node) override {
            return nullptr;
        }

        ReturnType visit(FormalParameterListPtr node) override {
            return nullptr;
        }

        ReturnType visit(FormalParametersPtr node) override {
            return nullptr;
        }

        ReturnType visit(FunctionHeaderPtr node) override {
            return nullptr;
        }

        ReturnType visit(FunctionDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(NullLiteralPtr node) override {
            return nullptr;
        }

        ReturnType visit(BoolLiteralPtr node) override {
            return nullptr;
        }

        ReturnType visit(NumberLiteralPtr node) override {
            return nullptr;
        }

        ReturnType visit(CharLiteralPtr node) override {
            return nullptr;
        }

        ReturnType visit(StringLiteralPtr node) override {
            return nullptr;
        }

        ReturnType visit(IdentifierPtr node) override {
            return nullptr;
        }

        ReturnType visit(TypeIdentifierPtr node) override {
            return nullptr;
        }

        ReturnType visit(VisibilityModifierPtr node) override {
            return nullptr;
        }

        ReturnType visit(PackageNamePtr node) override {
            return nullptr;
        }

        ReturnType visit(PackageDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(ImportDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(SourceFilePtr node) override {
            return nullptr;
        }

        ReturnType visit(ReturnStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(ThrowStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(BreakStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(ContinueStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(IfStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(UnlessStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(WhileStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(UntilStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(LoopStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(DoWhileStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(ForControlPtr node) override {
            return nullptr;
        }

        ReturnType visit(ForStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(ForeachControlPtr node) override {
            return nullptr;
        }

        ReturnType visit(ForeachStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(CatchClausePtr node) override {
            return nullptr;
        }

        ReturnType visit(FinallyBlockPtr node) override {
            return nullptr;
        }

        ReturnType visit(TryStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(SwitchLabelPtr node) override {
            return nullptr;
        }

        ReturnType visit(SwitchBlockStatementGroupPtr node) override {
            return nullptr;
        }

        ReturnType visit(SwitchStatementPtr node) override {
            return nullptr;
        }

        ReturnType visit(TokenPtr node) override {
            return nullptr;
        }

        ReturnType visit(TypePtr node) override {
            return nullptr;
        }

        ReturnType visit(TypeDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(VariableNamePtr node) override {
            return nullptr;
        }

        ReturnType visit(VariableNameDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(VariableDeclarationExpressionPtr node) override {
            return nullptr;
        }

        ReturnType visit(VariableDeclarationPtr node) override {
            return nullptr;
        }

        ReturnType visit(ExpressionStatementPtr node) override {
            return nullptr;
        }
    };
}


