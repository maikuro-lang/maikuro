#pragma once

#include "AstTree.h"
#include "AstTreeVisitor.h"

namespace MaikuroAst::Tree {
    using std::make_shared;

    class AstTreeBuilder : public AstTreeVisitor<AstTreePtr> {
     public:
        static AstTreePtr build(MaikuroAst::SourceFilePtr sourceFile);

        AstTreePtr visit(MaikuroAst::AliasDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::AnnotationPtr node) override;

        AstTreePtr visit(MaikuroAst::AnnotationsPtr node) override;

        AstTreePtr visit(MaikuroAst::ArgumentPtr node) override;

        AstTreePtr visit(MaikuroAst::ArgumentsPtr node) override;

        AstTreePtr visit(MaikuroAst::BlockPtr node) override;

        AstTreePtr visit(MaikuroAst::SuperClassPtr node) override;

        AstTreePtr visit(MaikuroAst::SuperInterfacesPtr node) override;

        AstTreePtr visit(MaikuroAst::PropertyDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::MethodDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::AnnotationMemberPtr node) override;

        AstTreePtr visit(MaikuroAst::ClassBodyPtr node) override;

        AstTreePtr visit(MaikuroAst::ClassDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::ExpressionListPtr node) override;

        AstTreePtr visit(MaikuroAst::PrimaryExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::VariableNameExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::ParExpresionPtr node) override;

        AstTreePtr visit(MaikuroAst::MethodCallPtr node) override;

        AstTreePtr visit(MaikuroAst::DotExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::MethodCallExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::NewDeclaratorExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::SuffixExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::PrefixExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::BopExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::TernaryExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::MatchExpressionCasePtr node) override;

        AstTreePtr visit(MaikuroAst::MatchExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::FormalParameterPtr node) override;

        AstTreePtr visit(MaikuroAst::FormalParameterListPtr node) override;

        AstTreePtr visit(MaikuroAst::FormalParametersPtr node) override;

        AstTreePtr visit(MaikuroAst::FunctionHeaderPtr node) override;

        AstTreePtr visit(MaikuroAst::FunctionDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::NullLiteralPtr node) override;

        AstTreePtr visit(MaikuroAst::BoolLiteralPtr node) override;

        AstTreePtr visit(MaikuroAst::NumberLiteralPtr node) override;

        AstTreePtr visit(MaikuroAst::CharLiteralPtr node) override;

        AstTreePtr visit(MaikuroAst::StringLiteralPtr node) override;

        AstTreePtr visit(MaikuroAst::IdentifierPtr node) override;

        AstTreePtr visit(MaikuroAst::TypeIdentifierPtr node) override;

        AstTreePtr visit(MaikuroAst::VisibilityModifierPtr node) override;

        AstTreePtr visit(MaikuroAst::PackageNamePtr node) override;

        AstTreePtr visit(MaikuroAst::PackageDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::ImportDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::SourceFilePtr node) override;

        AstTreePtr visit(MaikuroAst::ReturnStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::ThrowStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::BreakStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::ContinueStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::IfStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::UnlessStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::WhileStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::UntilStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::LoopStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::DoWhileStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::ForControlPtr node) override;

        AstTreePtr visit(MaikuroAst::ForStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::ForeachControlPtr node) override;

        AstTreePtr visit(MaikuroAst::ForeachStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::CatchClausePtr node) override;

        AstTreePtr visit(MaikuroAst::FinallyBlockPtr node) override;

        AstTreePtr visit(MaikuroAst::TryStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::SwitchLabelPtr node) override;

        AstTreePtr visit(MaikuroAst::SwitchBlockStatementGroupPtr node) override;

        AstTreePtr visit(MaikuroAst::SwitchStatementPtr node) override;

        AstTreePtr visit(MaikuroAst::TokenPtr node) override;

        AstTreePtr visit(MaikuroAst::TypePtr node) override;

        AstTreePtr visit(MaikuroAst::TypeDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::VariableNamePtr node) override;

        AstTreePtr visit(MaikuroAst::VariableNameDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::VariableDeclarationExpressionPtr node) override;

        AstTreePtr visit(MaikuroAst::VariableDeclarationPtr node) override;

        AstTreePtr visit(MaikuroAst::ExpressionStatementPtr node) override;
    };

}

