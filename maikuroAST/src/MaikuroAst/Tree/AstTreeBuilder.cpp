
#include "MaikuroAst/Tree/AstTreeBuilder.h"

namespace MaikuroAst::Tree {

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::AliasDeclarationPtr node) {
        return make_shared<AstTree>(
            node, AstTreePtrVec{
                visit(node->getAliasToken()),
                visit(node->getType()),
                visit(node->getAssignToken()),
                visit(node->getTypeDeclaration()),
                visit(node->getSemicolonToken())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::AnnotationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, visit(node->getTypeIdentifier()));

        if (node->getArguments()) {
            tree->add(visit(node->getArguments()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::AnnotationsPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getPrefix()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto annotation : node->getAnnotations()) {
            tree->add(visit(annotation));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        tree->add(node->getCloseBracket());

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ArgumentPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getIdentifier()) {
            tree->add(visit(node->getIdentifier()));
            tree->add(visit(node->getColon()));
        }

        tree->add(AstTreeVisitor::visit(node->getExpression()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ArgumentsPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getOpenBrace()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto argument : node->getArguments()) {
            tree->add(visit(argument));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        tree->add(visit(node->getCloseBrace()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::BlockPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, visit(node->getLeftBra()));

        tree->add(AstTreeVisitor::visit<StatementPtr>(node->getStatements()));
        tree->add(visit(node->getRightBra()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SuperClassPtr node) {
        return make_shared<AstTree>(node, AstTreePtrVec{ visit(node->getExtendsToken()), visit(node->getClassName()) });
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SuperInterfacesPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, visit(node->getImplementsToken()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto identifier : node->getInterfaceNames()) {
            tree->add(visit(identifier));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::PropertyDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations()));

        if (node->getVisibility()) {
            tree->add(visit(node->getVisibility()));
        }

        tree->add(visit(node->getTypeDeclaration()));
        tree->add(visit(node->getIdentifier()));
        tree->add(visit(node->getAssignToken()));
        tree->add(AstTreeVisitor::visit(node->getExpression()));
        tree->add(visit(node->getColon()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::MethodDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations()));

        if (node->getVisibility()) {
            tree->add(visit(node->getVisibility()));
        }

        tree->add(visit(node->getFunctionHeader()));
        tree->add(visit(node->getBlock()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::AnnotationMemberPtr node) {
        return make_shared<AstTree>(node, visit(node->getAnnotations()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ClassBodyPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, visit(node->getLeftBra()));

        tree->add(AstTreeVisitor::visit<ClassMemberPtr>(node->getClassMembers()));
        tree->add(visit(node->getRightBra()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ClassDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations()));
        tree->add(visit(node->getClassToken()));
        tree->add(visit(node->getClassName()));

        if (node->getSuperClass()) {
            tree->add(visit(node->getSuperClass()));
        }

        if (node->getSuperInterfaces()) {
            tree->add(visit(node->getSuperInterfaces()));
        }

        tree->add(visit(node->getClassBody()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ExpressionListPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        auto commas = node->getCommas();

        int       i = 0;
        for (auto expression : node->getExpressions()) {
            tree->add(AstTreeVisitor::visit(expression));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::PrimaryExpressionPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VariableNameExpressionPtr node) {
        return make_shared<AstTree>(node, visit(node->getVariableName()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ParExpresionPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                visit(node->getLeftPar()),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getRightPar())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::MethodCallPtr node) {
        return make_shared<AstTree>(node, AstTreePtrVec{ visit(node->getIdentifier()), visit(node->getArguments()) });
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::DotExpressionPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, AstTreeVisitor::visit(node->getExpression()));

        tree->add(visit(node->getDot()));

        if (node->getIdentifier()) {
            tree->add(visit(node->getIdentifier()));
        }

        if (node->getMethodCall()) {
            tree->add(visit(node->getMethodCall()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::MethodCallExpressionPtr node) {
        return make_shared<AstTree>(node, visit(node->getMethodCall()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::NewDeclaratorExpressionPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                visit(node->getNewToken()),
                visit(node->getType()),
                visit(node->getArguments())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SuffixExpressionPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSuffix())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::PrefixExpressionPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                visit(node->getPrefix()),
                AstTreeVisitor::visit(node->getExpression())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::BopExpressionPtr node) {
        return make_shared<AstTree>(
            node, AstTreePtrVec{
                AstTreeVisitor::visit(node->getLeftExpresion()),
                visit(node->getBop()),
                AstTreeVisitor::visit(node->getRightExpresion())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TernaryExpressionPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit(node->getLeftExpression()));
        tree->add(visit(node->getBop()));

        if (node->getTrueExpression()) {
            tree->add(AstTreeVisitor::visit(node->getTrueExpression()));
        }

        tree->add(visit(node->getColon()));

        tree->add(AstTreeVisitor::visit(node->getFalseExpression()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::MatchExpressionCasePtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getExpressionList()) {
            tree->add(visit(node->getExpressionList()));
        }

        if (node->getDefaultToken()) {
            tree->add(visit(node->getDefaultToken()));
        }

        tree->add(visit(node->getDoubleArrowToken()));

        tree->add(AstTreeVisitor::visit(node->getExpression()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::MatchExpressionPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getMatchToken()));
        tree->add(visit(node->getParExpresion()));
        tree->add(visit(node->getLeftBra()));

        auto commas = node->getCommas();

        int       i = 0;
        for (auto expressionCase : node->getMatchExpressionCases()) {
            tree->add(visit(expressionCase));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        tree->add(visit(node->getRightBra()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FormalParameterPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getType()) {
            tree->add(visit(node->getType()));
        }

        if (node->getVariadic()) {
            tree->add(visit(node->getVariadic()));
        }

        tree->add(visit(node->getIdentifier()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FormalParameterListPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        auto commas = node->getCommas();

        int       i = 0;
        for (auto parameter : node->getParameters()) {
            tree->add(visit(parameter));

            if (commas.size() > i) {
                tree->add(visit(commas[i++]));
            }
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FormalParametersPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getLeftPar()));

        if (node->getParameters()) {
            tree->add(visit(node->getParameters()));
        }

        tree->add(visit(node->getRightPar()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FunctionHeaderPtr node) {
        AstTreePtr tree = make_shared<AstTree>(
            node,
            AstTreePtrVec{ visit(node->getFun()), visit(node->getIdentifier()) }
        );

        tree->add(visit(node->getParameters()));

        if (node->getReturnType()) {
            tree->add(visit(node->getColon()));
            tree->add(visit(node->getReturnType()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FunctionDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations()));

        tree->add(visit(node->getFunctionHeader()));
        tree->add(visit(node->getBlock()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::NullLiteralPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::BoolLiteralPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::NumberLiteralPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::CharLiteralPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::StringLiteralPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::IdentifierPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TypeIdentifierPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VisibilityModifierPtr node) {
        return make_shared<AstTree>(node, visit(node->getToken()));
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::PackageNamePtr node) {
        AstTreePtr  tree = make_shared<AstTree>(node);
        TokenPtrVec dots = node->getDots();

        int       i = 0;
        for (auto identifier : node->getIdentifiers()) {
            tree->add(visit(identifier));

            if (dots.size() > i) {
                tree->add(visit(dots[i++]));
            }
        }

        if (node->getTypeIdentifier()) {
            tree->add(visit(node->getTypeIdentifier()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::PackageDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node, visit(node->getPackageToken()));

        tree->add(visit(node->getPackageName()));

        tree->add(visit(node->getSemicolonToken()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ImportDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getImportToken()));
        tree->add(visit(node->getPackageName()));

        if (node->getAlias()) {
            tree->add(visit(node->getAsToken()));
            tree->add(visit(node->getAlias()));
        }

        tree->add(visit(node->getSemicolonToken()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SourceFilePtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getPackageDeclaration()) {
            tree->add(visit(node->getPackageDeclaration()));
        }

        tree->add(AstTreeVisitor::visit<ImportDeclarationPtr>(node->getImportDeclarations()));
        tree->add(AstTreeVisitor::visit<StatementPtr>(node->getStatements()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ReturnStatementPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                visit(node->getToken()),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSemicolonToken())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ThrowStatementPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                visit(node->getToken()),
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSemicolonToken())
            }
        );
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::BreakStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));

        if (node->getNumberLiteral()) {
            tree->add(visit(node->getNumberLiteral()));
        }

        tree->add(visit(node->getSemicolonToken()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ContinueStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));

        if (node->getNumberLiteral()) {
            tree->add(visit(node->getNumberLiteral()));
        }

        tree->add(visit(node->getSemicolonToken()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::IfStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));
        tree->add(visit(node->getExpresion()));
        tree->add(AstTreeVisitor::visit(node->getStatement()));

        if (node->getElseToken()) {
            tree->add(visit(node->getElseToken()));
            tree->add(AstTreeVisitor::visit(node->getElseStatement()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::UnlessStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));
        tree->add(visit(node->getExpresion()));
        tree->add(AstTreeVisitor::visit(node->getStatement()));

        if (node->getElseToken()) {
            tree->add(visit(node->getElseToken()));
            tree->add(AstTreeVisitor::visit(node->getElseStatement()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::WhileStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));
        tree->add(visit(node->getExpresion()));
        tree->add(visit(node->getBlock()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::UntilStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));
        tree->add(visit(node->getExpresion()));
        tree->add(visit(node->getBlock()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::LoopStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getToken()));

        if (node->getExpresion()) {
            tree->add(visit(node->getExpresion()));
        }

        tree->add(visit(node->getBlock()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::DoWhileStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getDoToken()));

        tree->add(visit(node->getBlock()));

        tree->add(visit(node->getToken()));

        if (node->getExpresion()) {
            tree->add(visit(node->getExpresion()));
        }

        tree->add(visit(node->getSemicolonToken()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ForControlPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getVariableDeclaration()) {
            tree->add(visit(node->getVariableDeclaration()));
        }

        if (node->getExpressionList()) {
            tree->add(visit(node->getExpressionList()));
        }

        tree->add(visit(node->getSemicolons()[0]));

        if (node->getExpression()) {
            tree->add(AstTreeVisitor::visit(node->getExpression()));
        }

        tree->add(visit(node->getSemicolons()[1]));

        if (node->getUpdateExpressionList()) {
            tree->add(visit(node->getUpdateExpressionList()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ForStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getForToken()));
        tree->add(visit(node->getLeftPar()));
        tree->add(visit(node->getControl()));
        tree->add(visit(node->getRightPar()));
        tree->add(AstTreeVisitor::visit(node->getStatement()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ForeachControlPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit(node->getExpression()));
        tree->add(visit(node->getAsToken()));
        tree->add(visit(node->getIdentifiers()[0]));

        if (node->getIdentifiers().size() == 2) {
            tree->add(visit(node->getDoubleArrow()));
            tree->add(visit(node->getIdentifiers()[1]));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ForeachStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getForeachToken()));
        tree->add(visit(node->getLeftPar()));
        tree->add(visit(node->getControl()));
        tree->add(visit(node->getRightPar()));
        tree->add(AstTreeVisitor::visit(node->getStatement()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::CatchClausePtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getCatchToken()));
        tree->add(visit(node->getLeftPar()));

        TokenPtrVec pipes = node->getPipes();

        int       i = 0;
        for (auto identifier : node->getTypeIdentifiers()) {
            tree->add(visit(identifier));

            if (pipes.size() > i) {
                tree->add(visit(pipes[i++]));
            }
        }

        tree->add(visit(node->getIdentifier()));
        tree->add(visit(node->getRightPar()));
        tree->add(node->getBlock());

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::FinallyBlockPtr node) {
        return make_shared<AstTree>(node, AstTreePtrVec{ visit(node->getFinallyToken()), visit(node->getBlock()) });
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TryStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getTryToken()));
        tree->add(visit(node->getBlock()));

        tree->add(AstTreeVisitor::visit<CatchClausePtr>(node->getCatches()));

        if (node->getFinallyBlock()) {
            tree->add(node->getFinallyBlock());
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SwitchLabelPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getDefaultToken()) {
            tree->add(visit(node->getDefaultToken()));
        }

        if (node->getCaseToken()) {
            tree->add(visit(node->getCaseToken()));
        }

        if (node->getIdentifier()) {
            tree->add(visit(node->getIdentifier()));
        }

        if (node->getExpression()) {
            tree->add(AstTreeVisitor::visit(node->getExpression()));
        }

        tree->add(visit(node->getColon()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SwitchBlockStatementGroupPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<SwitchLabelPtr>(node->getSwitchLabels()));
        tree->add(AstTreeVisitor::visit<StatementPtr>(node->getStatements()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::SwitchStatementPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getSwitchToken()));
        tree->add(visit(node->getExpresion()));
        tree->add(visit(node->getLeftBra()));

        tree->add(AstTreeVisitor::visit<SwitchBlockStatementGroupPtr>(node->getSwitchBlockStatementGroups()));
        tree->add(AstTreeVisitor::visit<SwitchLabelPtr>(node->getSwitchLabels()));

        tree->add(visit(node->getRightBra()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TokenPtr node) {
        return make_shared<AstTree>(node);
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TypePtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(visit(node->getTypeIdentifier()));

        if (node->getOpenBrace()) {
            tree->add(visit(node->getOpenBrace()));

            if (node->getArraySize()) {
                tree->add(visit(node->getArraySize()));
            }

            tree->add(visit(node->getCloseBrace()));
        }

        if (node->getQuestionMark()) {
            tree->add(visit(node->getQuestionMark()));
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::TypeDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        TokenPtrVec pipes = node->getPipes();

        int       i = 0;
        for (auto types : node->getTypes()) {
            tree->add(visit(types));

            if (pipes.size() > i) {
                tree->add(visit(pipes[i++]));
            }
        }

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VariableNamePtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getAtSign()) {
            tree->add(visit(node->getAtSign()));
        }

        tree->add(visit(node->getIdentifier()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VariableNameDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getTypeDeclaration()) {
            tree->add(visit(node->getTypeDeclaration()));
        }

        tree->add(visit(node->getVariableName()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VariableDeclarationExpressionPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        if (node->getAssign()) {
            tree->add(visit(node->getAssign()));

            TokenPtrVec commas = node->getCommas();

            int       i = 0;
            for (auto expression : node->getExpressions()) {
                tree->add(AstTreeVisitor::visit(expression));

                if (commas.size() > i) {
                    tree->add(visit(commas[i++]));
                }
            }
        }

        tree->add(visit(node->getSemicolon()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::VariableDeclarationPtr node) {
        AstTreePtr tree = make_shared<AstTree>(node);

        tree->add(AstTreeVisitor::visit<AnnotationsPtr>(node->getAnnotations()));
        tree->add(visit(node->getVar()));

        TokenPtrVec separators = node->getSeparators();

        int       i = 0;
        for (auto variableName : node->getVariableNames()) {
            tree->add(visit(variableName));

            if (separators.size() > i) {
                tree->add(visit(separators[i++]));
            }
        }

        tree->add(visit(node->getExpressions()));

        return tree;
    }

    AstTreePtr AstTreeBuilder::visit(MaikuroAst::ExpressionStatementPtr node) {
        return make_shared<AstTree>(
            node,
            AstTreePtrVec{
                AstTreeVisitor::visit(node->getExpression()),
                visit(node->getSemicolonToken())
            }
        );
    }

    AstTreePtr AstTreeBuilder::build(SourceFilePtr sourceFile) {
        AstTreeBuilder builder;

        return builder.visit(sourceFile);
    }
}