#pragma once

#include "AstTreeVisitor.h"

namespace MaikuroAst::Tree {
    using MaikuroAst::AstNode;

    template<typename ReturnType>
    class AstTreeBaseVisitor : public AstTreeVisitor<ReturnType> {
     public:
        ReturnType visit(AliasDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(AnnotationPtr) override {
            return nullptr;
        }

        ReturnType visit(AnnotationsPtr) override {
            return nullptr;
        }

        ReturnType visit(ArgumentPtr) override {
            return nullptr;
        }

        ReturnType visit(ArgumentsPtr) override {
            return nullptr;
        }

        ReturnType visit(BlockPtr) override {
            return nullptr;
        }

        ReturnType visit(SuperClassPtr) override {
            return nullptr;
        }

        ReturnType visit(SuperInterfacesPtr) override {
            return nullptr;
        }

        ReturnType visit(ClassMemberPtr) override {
            return nullptr;
        }

        ReturnType visit(PropertyDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(MethodDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(AnnotationMemberPtr) override {
            return nullptr;
        }

        ReturnType visit(ClassBodyPtr) override {
            return nullptr;
        }

        ReturnType visit(ClassDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(ExpressionListPtr) override {
            return nullptr;
        }

        ReturnType visit(PrimaryExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(VariableNameExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(ParExpresionPtr) override {
            return nullptr;
        }

        ReturnType visit(MethodCallPtr) override {
            return nullptr;
        }

        ReturnType visit(DotExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(MethodCallExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(NewDeclaratorExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(SuffixExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(PrefixExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(BopExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(TernaryExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(MatchExpressionCasePtr) override {
            return nullptr;
        }

        ReturnType visit(MatchExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(FormalParameterPtr) override {
            return nullptr;
        }

        ReturnType visit(FormalParameterListPtr) override {
            return nullptr;
        }

        ReturnType visit(FormalParametersPtr) override {
            return nullptr;
        }

        ReturnType visit(FunctionHeaderPtr) override {
            return nullptr;
        }

        ReturnType visit(FunctionDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(NullLiteralPtr) override {
            return nullptr;
        }

        ReturnType visit(BoolLiteralPtr) override {
            return nullptr;
        }

        ReturnType visit(NumberLiteralPtr) override {
            return nullptr;
        }

        ReturnType visit(CharLiteralPtr) override {
            return nullptr;
        }

        ReturnType visit(StringLiteralPtr) override {
            return nullptr;
        }

        ReturnType visit(IdentifierPtr) override {
            return nullptr;
        }

        ReturnType visit(TypeIdentifierPtr) override {
            return nullptr;
        }

        ReturnType visit(VisibilityModifierPtr) override {
            return nullptr;
        }

        ReturnType visit(PackageNamePtr) override {
            return nullptr;
        }

        ReturnType visit(PackageDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(ImportDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(SourceFilePtr) override {
            return nullptr;
        }

        ReturnType visit(ReturnStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(ThrowStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(BreakStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(ContinueStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(IfStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(UnlessStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(WhileStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(UntilStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(LoopStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(DoWhileStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(ForControlPtr) override {
            return nullptr;
        }

        ReturnType visit(ForStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(ForeachControlPtr) override {
            return nullptr;
        }

        ReturnType visit(ForeachStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(CatchClausePtr) override {
            return nullptr;
        }

        ReturnType visit(FinallyBlockPtr) override {
            return nullptr;
        }

        ReturnType visit(TryStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(SwitchLabelPtr) override {
            return nullptr;
        }

        ReturnType visit(SwitchBlockStatementGroupPtr) override {
            return nullptr;
        }

        ReturnType visit(SwitchStatementPtr) override {
            return nullptr;
        }

        ReturnType visit(TokenPtr) override {
            return nullptr;
        }

        ReturnType visit(TypePtr) override {
            return nullptr;
        }

        ReturnType visit(TypeDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(VariableNamePtr) override {
            return nullptr;
        }

        ReturnType visit(VariableNameDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(VariableDeclarationExpressionPtr) override {
            return nullptr;
        }

        ReturnType visit(VariableDeclarationPtr) override {
            return nullptr;
        }

        ReturnType visit(ExpressionStatementPtr) override {
            return nullptr;
        }
    };
}


