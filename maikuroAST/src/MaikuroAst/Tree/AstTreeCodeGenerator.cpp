#include "MaikuroAst/Tree/AstTreeCodeGenerator.h"

namespace MaikuroAst::Tree {

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::AliasDeclarationPtr node) {
        return join(
            {
                visit(node->getAliasToken()),
                space(),
                visit(node->getType()),
                space(),
                visit(node->getAssignToken()),
                space(),
                visit(node->getTypeDeclaration()),
                space(),
                visit(node->getSemicolonToken()),
                newLine()
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::AnnotationPtr node) {
        vector<StringVecPtr> source = { visit(node->getTypeIdentifier()) };

        if (node->getArguments()) {
            source.push_back(visit(node->getArguments()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::AnnotationsPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getPrefix()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto annotation : node->getAnnotations()) {
            source.push_back(visit(annotation));

            if (commas.size() > i) {
                source.push_back(visit(commas[i++]));
                source.push_back(space());
            }
        }

        source.push_back(visit(node->getCloseBracket()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ArgumentPtr node) {
        vector<StringVecPtr> source;

        if (node->getIdentifier()) {
            source.push_back(visit(node->getIdentifier()));
            source.push_back(visit(node->getColon()));
        }

        source.push_back(AstTreeVisitor::visit(node->getExpression()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ArgumentsPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getOpenBrace()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto argument : node->getArguments()) {
            source.push_back(visit(argument));

            if (commas.size() > i) {
                source.push_back(visit(commas[i++]));
                source.push_back(space());
            }
        }

        source.push_back(visit(node->getCloseBrace()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::BlockPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getLeftBra()));

        for (auto statements : AstTreeVisitor::visit<StatementPtr>(node->getStatements())) {
            for (auto line : *statements) {
                source.push_back(
                    join(
                        {
                            "   ",
                            line
                        }
                    )
                );
            }
        }

        source.push_back(visit(node->getRightBra()));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SuperClassPtr node) {
        return join(
            {
                visit(node->getExtendsToken()),
                space(),
                visit(node->getClassName())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SuperInterfacesPtr node) {
        vector<StringVecPtr> source = { visit(node->getImplementsToken()) };

        auto commas = node->getCommas();

        int       i = 0;
        for (auto identifier : node->getInterfaceNames()) {
            source.push_back(visit(identifier));

            if (commas.size() > i) {
                source.push_back(visit(commas[i++]));
                source.push_back(space());
            }
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::PropertyDeclarationPtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        vector<StringVecPtr> line;
        if (node->getVisibility()) {
            line.push_back(visit(node->getVisibility()));
            line.push_back(space());
        }

        line.push_back(visit(node->getTypeDeclaration()));
        line.push_back(space());
        line.push_back(visit(node->getIdentifier()));
        line.push_back(space());
        line.push_back(visit(node->getAssignToken()));
        line.push_back(space());
        line.push_back(AstTreeVisitor::visit(node->getExpression()));
        line.push_back(visit(node->getColon()));

        source.push_back(join(line));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::MethodDeclarationPtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        vector<StringVecPtr> line;
        if (node->getVisibility()) {
            line.push_back(visit(node->getVisibility()));
            line.push_back(space());
        }

        line.push_back(visit(node->getFunctionHeader()));
        source.push_back(join(line));

        auto      lines = visit(node->getBlock());
        for (auto l : *lines) {
            source.push_back(
                join({ l })
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::AnnotationMemberPtr node) {
        return visit(node->getAnnotations());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ClassBodyPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getLeftBra()));

        for (auto a : AstTreeVisitor::visit<ClassMemberPtr>(node->getClassMembers())) {
            for (auto line : *a) {
                source.push_back(
                    join(
                        {
                            "    ",
                            line
                        }
                    )
                );
            }
            source.push_back(character(""));
        }

        source.push_back(visit(node->getRightBra()));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ClassDeclarationPtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        vector<StringVecPtr> line;
        line.push_back(visit(node->getClassToken()));
        line.push_back(space());
        line.push_back(visit(node->getClassName()));
        line.push_back(space());

        if (node->getSuperClass()) {
            line.push_back(visit(node->getSuperClass()));
            line.push_back(space());
        }

        if (node->getSuperInterfaces()) {
            line.push_back(visit(node->getSuperInterfaces()));
            line.push_back(space());
        }

        source.push_back(join(line));
        source.push_back(visit(node->getClassBody()));

        source.push_back(character(""));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ExpressionListPtr node) {
        vector<StringVecPtr> source;

        auto commas = node->getCommas();

        int       i = 0;
        for (auto expression : node->getExpressions()) {
            source.push_back(AstTreeVisitor::visit(expression));

            if (commas.size() > i) {
                source.push_back(visit(commas[i++]));
                source.push_back(space());
            }
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::PrimaryExpressionPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VariableNameExpressionPtr node) {
        return visit(node->getVariableName());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ParExpresionPtr node) {
        return join(
            {
                visit(node->getLeftPar()),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getRightPar())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::MethodCallPtr node) {
        return join({ visit(node->getIdentifier()), visit(node->getArguments()) });
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::DotExpressionPtr node) {
        vector<StringVecPtr> source = { AstTreeVisitor::visit(node->getExpression()) };

        source.push_back(visit(node->getDot()));

        if (node->getIdentifier()) {
            source.push_back(visit(node->getIdentifier()));
        }

        if (node->getMethodCall()) {
            source.push_back(visit(node->getMethodCall()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::MethodCallExpressionPtr node) {
        return visit(node->getMethodCall());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::NewDeclaratorExpressionPtr node) {
        return join(
            {
                visit(node->getNewToken()),
                space(),
                visit(node->getType()),
                visit(node->getArguments())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SuffixExpressionPtr node) {
        return join(
            {
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSuffix())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::PrefixExpressionPtr node) {
        return join(
            {
                visit(node->getPrefix()),
                AstTreeVisitor::visit(node->getExpression())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::BopExpressionPtr node) {
        return join(
            {
                AstTreeVisitor::visit(node->getLeftExpresion()),
                space(),
                visit(node->getBop()),
                space(),
                AstTreeVisitor::visit(node->getRightExpresion())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TernaryExpressionPtr node) {
        vector<StringVecPtr> source;

        source.push_back(AstTreeVisitor::visit(node->getLeftExpression()));
        source.push_back(space());
        source.push_back(visit(node->getBop()));

        if (node->getTrueExpression()) {
            source.push_back(space());
            source.push_back(AstTreeVisitor::visit(node->getTrueExpression()));
            source.push_back(space());
        }

        source.push_back(visit(node->getColon()));
        source.push_back(space());
        source.push_back(AstTreeVisitor::visit(node->getFalseExpression()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::MatchExpressionCasePtr node) {
        vector<StringVecPtr> source;

        if (node->getExpressionList()) {
            source.push_back(visit(node->getExpressionList()));
        }

        if (node->getDefaultToken()) {
            source.push_back(visit(node->getDefaultToken()));
        }

        source.push_back(space());
        source.push_back(visit(node->getDoubleArrowToken()));
        source.push_back(space());

        source.push_back(AstTreeVisitor::visit(node->getExpression()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::MatchExpressionPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getMatchToken()));
        line.push_back(space());
        line.push_back(visit(node->getParExpresion()));
        line.push_back(space());
        line.push_back(visit(node->getLeftBra()));

        source.push_back(join(line));

        auto commas = node->getCommas();

        int       i     = 0;
        auto      cases = AstTreeVisitor::visit<MatchExpressionCasePtr>(node->getMatchExpressionCases());
        for (auto lines : cases) {
            for (auto l : *lines) {
                vector<StringVecPtr> ll;
                ll.push_back(character("    "));
                ll.push_back(character(l));

                if (commas.size() > i) {
                    ll.push_back(visit(commas[i++]));
                }

                source.push_back(join(ll));
            }
        }

        source.push_back(visit(node->getRightBra()));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FormalParameterPtr node) {
        vector<StringVecPtr> source;

        if (node->getType()) {
            source.push_back(visit(node->getType()));
            source.push_back(space());
        }

        if (node->getVariadic()) {
            source.push_back(visit(node->getVariadic()));
        }

        source.push_back(visit(node->getIdentifier()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FormalParameterListPtr node) {
        vector<StringVecPtr> source;

        auto commas = node->getCommas();

        int       i = 0;
        for (auto parameter : node->getParameters()) {
            source.push_back(visit(parameter));

            if (commas.size() > i) {
                source.push_back(visit(commas[i++]));
                source.push_back(space());
            }
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FormalParametersPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getLeftPar()));

        if (node->getParameters()) {
            source.push_back(visit(node->getParameters()));
        }

        source.push_back(visit(node->getRightPar()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FunctionHeaderPtr node) {
        vector<StringVecPtr> source = { visit(node->getFun()), space(), visit(node->getIdentifier()) };

        source.push_back(visit(node->getParameters()));

        if (node->getReturnType()) {
            source.push_back(visit(node->getColon()));
            source.push_back(space());
            source.push_back(visit(node->getReturnType()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FunctionDeclarationPtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        source.push_back(visit(node->getFunctionHeader()));
        auto      lines = visit(node->getBlock());
        for (auto l : *lines) {
            source.push_back(
                join({ l })
            );
        }

        source.push_back(character(""));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::NullLiteralPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::BoolLiteralPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::NumberLiteralPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::CharLiteralPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::StringLiteralPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::IdentifierPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TypeIdentifierPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VisibilityModifierPtr node) {
        return visit(node->getToken());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::PackageNamePtr node) {
        vector<StringVecPtr> source;
        TokenPtrVec          dots = node->getDots();

        int       i = 0;
        for (auto identifier : node->getIdentifiers()) {
            source.push_back(visit(identifier));

            if (dots.size() > i) {
                source.push_back(visit(dots[i++]));
            }
        }

        if (node->getTypeIdentifier()) {
            source.push_back(visit(node->getTypeIdentifier()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::PackageDeclarationPtr node) {
        vector<StringVecPtr> source = { visit(node->getPackageToken()), space() };

        source.push_back(visit(node->getPackageName()));

        source.push_back(visit(node->getSemicolonToken()));

        source.push_back(newLine());

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ImportDeclarationPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getImportToken()));
        source.push_back(space());
        source.push_back(visit(node->getPackageName()));

        if (node->getAlias()) {
            source.push_back(space());
            source.push_back(visit(node->getAsToken()));
            source.push_back(space());
            source.push_back(visit(node->getAlias()));
        }

        source.push_back(visit(node->getSemicolonToken()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SourceFilePtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        if (node->getPackageDeclaration()) {
            source.push_back(visit(node->getPackageDeclaration()));
        }

        for (auto a : AstTreeVisitor::visit<ImportDeclarationPtr>(node->getImportDeclarations())) {
            source.push_back(a);
        }

        source.push_back(character(""));

        for (auto a : AstTreeVisitor::visit<StatementPtr>(node->getStatements())) {
            for (auto line : *a) {
                source.push_back(
                    join(
                        {
                            line
                        }
                    )
                );
            }
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ReturnStatementPtr node) {
        return join(
            {
                visit(node->getToken()), space(),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSemicolonToken())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ThrowStatementPtr node) {
        return join(
            {
                visit(node->getToken()), space(),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSemicolonToken())
            }
        );
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::BreakStatementPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getToken()));

        if (node->getNumberLiteral()) {
            source.push_back(space());
            source.push_back(visit(node->getNumberLiteral()));
        }

        source.push_back(visit(node->getSemicolonToken()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ContinueStatementPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getToken()));

        if (node->getNumberLiteral()) {
            source.push_back(space());
            source.push_back(visit(node->getNumberLiteral()));
        }

        source.push_back(visit(node->getSemicolonToken()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::IfStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));
        line.push_back(space());

        source.push_back(join(line));
        auto      lines = AstTreeVisitor::visit(node->getStatement());
        for (auto l : *lines) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        if (node->getElseToken()) {
            source.push_back(visit(node->getElseToken()));

            auto      lines = AstTreeVisitor::visit(node->getElseStatement());
            for (auto l : *lines) {
                source.push_back(
                    join(
                        {
                            l
                        }
                    )
                );
            }
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::UnlessStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));
        line.push_back(space());

        source.push_back(join(line));
        auto      lines = AstTreeVisitor::visit(node->getStatement());
        for (auto l : *lines) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        if (node->getElseToken()) {
            source.push_back(visit(node->getElseToken()));

            auto      lines = AstTreeVisitor::visit(node->getElseStatement());
            for (auto l : *lines) {
                source.push_back(
                    join(
                        {
                            l
                        }
                    )
                );
            }
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::WhileStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));

        source.push_back(join(line));
        auto      lines = visit(node->getBlock());
        for (auto l : *lines) {
            source.push_back(
                join(
                    {
                        "    ",
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::UntilStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));

        source.push_back(join(line));
        auto      lines = visit(node->getBlock());
        for (auto l : *lines) {
            source.push_back(
                join(
                    {
                        "    ",
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::LoopStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getToken()));

        if (node->getExpresion()) {
            line.push_back(space());
            line.push_back(visit(node->getExpresion()));
        }

        source.push_back(join(line));
        auto      lines = visit(node->getBlock());
        for (auto l : *lines) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::DoWhileStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        source.push_back(visit(node->getDoToken()));

        for (auto l : *visit(node->getBlock())) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        line.push_back(visit(node->getToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));
        line.push_back(visit(node->getSemicolonToken()));

        source.push_back(join(line));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ForControlPtr node) {
        vector<StringVecPtr> source;

        if (node->getVariableDeclaration()) {
            source.push_back(visit(node->getVariableDeclaration()));
        }

        if (node->getExpressionList()) {
            source.push_back(visit(node->getExpressionList()));
        }

        source.push_back(visit(node->getSemicolons()[0]));
        source.push_back(space());

        if (node->getExpression()) {
            source.push_back(AstTreeVisitor::visit(node->getExpression()));
        }

        source.push_back(visit(node->getSemicolons()[1]));
        source.push_back(space());

        if (node->getUpdateExpressionList()) {
            source.push_back(visit(node->getUpdateExpressionList()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ForStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getForToken()));
        line.push_back(space());
        line.push_back(visit(node->getLeftPar()));
        line.push_back(visit(node->getControl()));
        line.push_back(visit(node->getRightPar()));

        source.push_back(join(line));
        for (auto l : *AstTreeVisitor::visit(node->getStatement())) {
            source.push_back(
                join(
                    {
                        "    ",
                        l
                    }
                )
            );

        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ForeachControlPtr node) {
        vector<StringVecPtr> source;

        source.push_back(AstTreeVisitor::visit(node->getExpression()));
        source.push_back(space());
        source.push_back(visit(node->getAsToken()));
        source.push_back(space());
        source.push_back(visit(node->getIdentifiers()[0]));

        if (node->getIdentifiers().size() == 2) {
            source.push_back(space());
            source.push_back(visit(node->getDoubleArrow()));
            source.push_back(space());
            source.push_back(visit(node->getIdentifiers()[1]));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ForeachStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getForeachToken()));
        line.push_back(space());
        line.push_back(visit(node->getLeftPar()));
        line.push_back(visit(node->getControl()));
        line.push_back(visit(node->getRightPar()));
        line.push_back(space());

        source.push_back(join(line));

        for (auto l : *AstTreeVisitor::visit(node->getStatement())) {
            source.push_back(
                join(
                    {
                        "    ",
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::CatchClausePtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getCatchToken()));
        line.push_back(space());
        line.push_back(visit(node->getLeftPar()));

        TokenPtrVec pipes = node->getPipes();

        int       i = 0;
        for (auto identifier : node->getTypeIdentifiers()) {
            line.push_back(visit(identifier));

            if (pipes.size() > i) {
                line.push_back(space());
                line.push_back(visit(pipes[i++]));
                line.push_back(space());
            }
        }

        line.push_back(visit(node->getIdentifier()));
        line.push_back(visit(node->getRightPar()));
        source.push_back(join(line));

        for (auto l : *visit(node->getBlock())) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::FinallyBlockPtr node) {
        vector<StringVecPtr> source = { visit(node->getFinallyToken()) };

        for (auto l : *visit(node->getBlock())) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TryStatementPtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getTryToken()));

        for (auto l : *visit(node->getBlock())) {
            source.push_back(
                join(
                    {
                        l
                    }
                )
            );
        }

        for (auto a : AstTreeVisitor::visit<CatchClausePtr>(node->getCatches())) {
            for (auto l : *a) {
                source.push_back(
                    join(
                        {
                            l
                        }
                    )
                );
            }
        }

        if (node->getFinallyBlock()) {
            for (auto l : *visit(node->getFinallyBlock())) {
                source.push_back(
                    join(
                        {
                            l
                        }
                    )
                );
            }
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SwitchLabelPtr node) {
        vector<StringVecPtr> source;

        if (node->getDefaultToken()) {
            source.push_back(visit(node->getDefaultToken()));
        }

        if (node->getCaseToken()) {
            source.push_back(visit(node->getCaseToken()));
        }

        if (node->getIdentifier()) {
            source.push_back(visit(node->getIdentifier()));
        }

        if (node->getExpression()) {
            source.push_back(AstTreeVisitor::visit(node->getExpression()));
        }

        source.push_back(visit(node->getColon()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SwitchBlockStatementGroupPtr node) {
        vector<StringVecPtr> source;

        for (auto a : AstTreeVisitor::visit<SwitchLabelPtr>(node->getSwitchLabels())) {
            for (auto l : *a) {
                source.push_back(
                    join(
                        {
                            l
                        }
                    )
                );
            }
        }

        for (auto a : AstTreeVisitor::visit<StatementPtr>(node->getStatements())) {
            for (auto l : *a) {
                source.push_back(
                    join(
                        {
                            "    ",
                            l
                        }
                    )
                );
            }
        }

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::SwitchStatementPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        line.push_back(visit(node->getSwitchToken()));
        line.push_back(space());
        line.push_back(visit(node->getExpresion()));
        line.push_back(space());
        line.push_back(visit(node->getLeftBra()));
        line.push_back(newLine());

        source.push_back(join(line));

        for (auto a : AstTreeVisitor::visit<SwitchBlockStatementGroupPtr>(node->getSwitchBlockStatementGroups())) {
            for (auto line : *a) {
                source.push_back(
                    join(
                        {
                            "    ",
                            line
                        }
                    )
                );
            }
        }

        for (auto a : AstTreeVisitor::visit<SwitchLabelPtr>(node->getSwitchLabels())) {
            for (auto line : *a) {
                source.push_back(
                    join(
                        {
                            "    ",
                            line
                        }
                    )
                );
            }
        }

        source.push_back(visit(node->getRightBra()));

        return flatten(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TokenPtr node) {
        return character(node->getValue());
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TypePtr node) {
        vector<StringVecPtr> source;

        source.push_back(visit(node->getTypeIdentifier()));

        if (node->getOpenBrace()) {
            source.push_back(visit(node->getOpenBrace()));

            if (node->getArraySize()) {
                source.push_back(visit(node->getArraySize()));
            }

            source.push_back(visit(node->getCloseBrace()));
        }

        if (node->getQuestionMark()) {
            source.push_back(visit(node->getQuestionMark()));
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::TypeDeclarationPtr node) {
        vector<StringVecPtr> source;

        TokenPtrVec pipes = node->getPipes();

        int       i = 0;
        for (auto types : node->getTypes()) {
            source.push_back(visit(types));

            if (pipes.size() > i) {
                source.push_back(space());
                source.push_back(visit(pipes[i++]));
                source.push_back(space());
            }
        }

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VariableNamePtr node) {
        vector<StringVecPtr> source;

        if (node->getAtSign()) {
            source.push_back(visit(node->getAtSign()));
        }

        source.push_back(visit(node->getIdentifier()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VariableNameDeclarationPtr node) {
        vector<StringVecPtr> source;

        if (node->getTypeDeclaration()) {
            source.push_back(visit(node->getTypeDeclaration()));
            source.push_back(space());
        }

        source.push_back(visit(node->getVariableName()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VariableDeclarationExpressionPtr node) {
        vector<StringVecPtr> source;

        if (node->getAssign()) {
            source.push_back(space());
            source.push_back(visit(node->getAssign()));
            source.push_back(space());

            TokenPtrVec commas = node->getCommas();

            int       i = 0;
            for (auto expression : node->getExpressions()) {
                source.push_back(AstTreeVisitor::visit(expression));

                if (commas.size() > i) {
                    source.push_back(visit(commas[i++]));
                    source.push_back(space());
                }
            }
        }

        source.push_back(visit(node->getSemicolon()));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::VariableDeclarationPtr node) {
        vector<StringVecPtr> source;
        vector<StringVecPtr> line;

        for (auto a : AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations())) {
            source.push_back(a);
        }

        line.push_back(visit(node->getVar()));
        line.push_back(space());

        TokenPtrVec separators = node->getSeparators();

        int       i = 0;
        for (auto variableName : node->getVariableNames()) {
            line.push_back(visit(variableName));

            if (separators.size() > i) {
                line.push_back(visit(separators[i++]));
                line.push_back(space());
            }
        }

        line.push_back(visit(node->getExpressions()));

        source.push_back(join(line));

        return join(source);
    }

    StringVecPtr AstTreeCodeGenerator::visit(MaikuroAst::ExpressionStatementPtr node) {
        return join({ AstTreeVisitor::visit(node->getExpression()), visit(node->getSemicolonToken()) });
    }

    string AstTreeCodeGenerator::build(SourceFilePtr sourceFile) {
        AstTreeCodeGenerator builder;

        StringVecPtr lines = builder.visit(sourceFile);
        string       output;

        for (auto line : *lines) {
            output += line + "\n";
        }

        return output;
    }

    StringVecPtr AstTreeCodeGenerator::character(string c) {
        return make_shared<StringVec>(initializer_list<string>{ c });
    }

    StringVecPtr AstTreeCodeGenerator::space() {
        return character(" ");
    }

    StringVecPtr AstTreeCodeGenerator::newLine() {
        return character("\n");
    }

    StringVecPtr AstTreeCodeGenerator::join(vector<StringVecPtr> vecs) {
        string result;

        for (auto vec : vecs) {
            if (!vec) {
                continue;
            }

            for (auto v : *vec) {
                result.append(v);
            }
        }

        return make_shared<StringVec>(initializer_list<string>{ result });
    }

    StringVecPtr AstTreeCodeGenerator::join(vector<string> vecs) {
        string result;

        for (auto vec : vecs) {
            result.append(vec);
        }

        return make_shared<StringVec>(initializer_list<string>{ result });
    }

    StringVecPtr AstTreeCodeGenerator::flatten(vector<StringVecPtr> vecs) {
        StringVecPtr result = make_shared<StringVec>();

        for (auto vec : vecs) {
            if (!vec) {
                continue;
            }

            for (auto v : *vec) {
                result->push_back(v);
            }
        }

        return result;
    }

}