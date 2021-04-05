#pragma once

#include "AstTree.h"
#include "AstTreeVisitor.h"

namespace MaikuroAst::Tree {
    using std::make_shared;
    using std::vector;
    using std::string;
    using std::initializer_list;

    typedef std::vector<string>        StringVec;
    typedef std::shared_ptr<StringVec> StringVecPtr;

    class AstTreeCodeGenerator : public AstTreeVisitor<StringVecPtr> {
     public:
        static std::string build(MaikuroAst::SourceFilePtr sourceFile);

        StringVecPtr visit(MaikuroAst::AliasDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::AnnotationPtr node) override;

        StringVecPtr visit(MaikuroAst::AnnotationsPtr node) override;

        StringVecPtr visit(MaikuroAst::ArgumentPtr node) override;

        StringVecPtr visit(MaikuroAst::ArgumentsPtr node) override;

        StringVecPtr visit(MaikuroAst::BlockPtr node) override;

        StringVecPtr visit(MaikuroAst::SuperClassPtr node) override;

        StringVecPtr visit(MaikuroAst::SuperInterfacesPtr node) override;

        StringVecPtr visit(MaikuroAst::PropertyDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::MethodDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::AnnotationMemberPtr node) override;

        StringVecPtr visit(MaikuroAst::ClassBodyPtr node) override;

        StringVecPtr visit(MaikuroAst::ClassDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::ExpressionListPtr node) override;

        StringVecPtr visit(MaikuroAst::PrimaryExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::VariableNameExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::ParExpresionPtr node) override;

        StringVecPtr visit(MaikuroAst::MethodCallPtr node) override;

        StringVecPtr visit(MaikuroAst::DotExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::MethodCallExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::NewDeclaratorExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::SuffixExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::PrefixExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::BopExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::TernaryExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::MatchExpressionCasePtr node) override;

        StringVecPtr visit(MaikuroAst::MatchExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::FormalParameterPtr node) override;

        StringVecPtr visit(MaikuroAst::FormalParameterListPtr node) override;

        StringVecPtr visit(MaikuroAst::FormalParametersPtr node) override;

        StringVecPtr visit(MaikuroAst::FunctionHeaderPtr node) override;

        StringVecPtr visit(MaikuroAst::FunctionDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::NullLiteralPtr node) override;

        StringVecPtr visit(MaikuroAst::BoolLiteralPtr node) override;

        StringVecPtr visit(MaikuroAst::NumberLiteralPtr node) override;

        StringVecPtr visit(MaikuroAst::CharLiteralPtr node) override;

        StringVecPtr visit(MaikuroAst::StringLiteralPtr node) override;

        StringVecPtr visit(MaikuroAst::IdentifierPtr node) override;

        StringVecPtr visit(MaikuroAst::TypeIdentifierPtr node) override;

        StringVecPtr visit(MaikuroAst::VisibilityModifierPtr node) override;

        StringVecPtr visit(MaikuroAst::PackageNamePtr node) override;

        StringVecPtr visit(MaikuroAst::PackageDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::ImportDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::SourceFilePtr node) override;

        StringVecPtr visit(MaikuroAst::ReturnStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::ThrowStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::BreakStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::ContinueStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::IfStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::UnlessStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::WhileStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::UntilStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::LoopStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::DoWhileStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::ForControlPtr node) override;

        StringVecPtr visit(MaikuroAst::ForStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::ForeachControlPtr node) override;

        StringVecPtr visit(MaikuroAst::ForeachStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::CatchClausePtr node) override;

        StringVecPtr visit(MaikuroAst::FinallyBlockPtr node) override;

        StringVecPtr visit(MaikuroAst::TryStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::SwitchLabelPtr node) override;

        StringVecPtr visit(MaikuroAst::SwitchBlockStatementGroupPtr node) override;

        StringVecPtr visit(MaikuroAst::SwitchStatementPtr node) override;

        StringVecPtr visit(MaikuroAst::TokenPtr node) override;

        StringVecPtr visit(MaikuroAst::TypePtr node) override;

        StringVecPtr visit(MaikuroAst::TypeDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::VariableNamePtr node) override;

        StringVecPtr visit(MaikuroAst::VariableNameDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::VariableDeclarationExpressionPtr node) override;

        StringVecPtr visit(MaikuroAst::VariableDeclarationPtr node) override;

        StringVecPtr visit(MaikuroAst::ExpressionStatementPtr node) override;

        StringVecPtr character(string c);

        StringVecPtr space();

        StringVecPtr newLine();

        StringVecPtr join(vector<StringVecPtr> vecs);

        StringVecPtr join(vector<string> vecs);

        StringVecPtr flatten(vector<StringVecPtr> vecs);
    };

}

