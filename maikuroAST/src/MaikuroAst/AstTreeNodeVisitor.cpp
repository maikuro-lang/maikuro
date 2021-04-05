#include "MaikuroAst.h"

namespace MaikuroAst {

    void AstTreeNodeVisitor::visit(std::shared_ptr<AliasDeclaration> node) {
        this->getVisitor(node)->visit(node);

        node->getAliasToken()->accept(this->getChildVisitor(node));
        node->getType()->accept(this->getChildVisitor(node));
        node->getAssignToken()->accept(this->getChildVisitor(node));
        node->getTypeDeclaration()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Annotation> node) {
        this->getVisitor(node)->visit(node);

        node->getTypeIdentifier()->accept(this->getChildVisitor(node));

        if (node->getArguments()) {
            node->getArguments()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Annotations> node) {
        this->getVisitor(node)->visit(node);

        node->getPrefix()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& annotation : node->getAnnotations()) {
            annotation->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }

        node->getCloseBracket()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Argument> node) {
        this->getVisitor(node)->visit(node);

        if (node->getIdentifier()) {
            node->getIdentifier()->accept(this->getChildVisitor(node));
            node->getColon()->accept(this->getChildVisitor(node));
        }

        node->getExpression()->accept(this->getChildVisitor(node));

    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Arguments> node) {
        this->getVisitor(node)->visit(node);

        node->getOpenBrace()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& argument : node->getArguments()) {
            argument->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }

        node->getCloseBrace()->accept(this->getChildVisitor(node));

    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Block> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftBra()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getStatements().begin(),
            node->getStatements().end(),
            [this, node](const StatementPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SuperClass> node) {
        this->getVisitor(node)->visit(node);

        node->getExtendsToken()->accept(this->getChildVisitor(node));
        node->getClassName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SuperInterfaces> node) {
        this->getVisitor(node)->visit(node);

        node->getImplementsToken()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& name : node->getInterfaceNames()) {
            name->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<PropertyDeclaration> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr & i) { i->accept(this->getChildVisitor(node)); }
        );

        if (node->getVisibility()) {
            node->getVisibility()->accept(this->getChildVisitor(node));
        }

        node->getTypeDeclaration()->accept(this->getChildVisitor(node));
        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getAssignToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
        node->getColon()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<MethodDeclaration> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr & i) { i->accept(this->getChildVisitor(node)); }
        );

        if (node->getVisibility()) {
            node->getVisibility()->accept(this->getChildVisitor(node));
        }

        node->getFunctionHeader()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<AnnotationMember> node) {
        this->getVisitor(node)->visit(node);

        node->getAnnotations()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ClassBody> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftBra()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getClassMembers().begin(),
            node->getClassMembers().end(),
            [this, node](const ClassMemberPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ClassDeclaration> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getClassToken()->accept(this->getChildVisitor(node));
        node->getClassName()->accept(this->getChildVisitor(node));

        if (node->getSuperClass()) {
            node->getSuperClass()->accept(this->getChildVisitor(node));
        }

        if (node->getSuperInterfaces()) {
            node->getSuperInterfaces()->accept(this->getChildVisitor(node));
        }

        node->getClassBody()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ExpressionList> node) {
        this->getVisitor(node)->visit(node);

        int i = 0;
        for (const auto& expression : node->getExpressions()) {
            expression->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<PrimaryExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VariableNameExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getVariableName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ParExpresion> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<MethodCall> node) {
        this->getVisitor(node)->visit(node);

        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getArguments()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<DotExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
        node->getDot()->accept(this->getChildVisitor(node));

        if (node->getIdentifier()) {
            node->getIdentifier()->accept(this->getChildVisitor(node));
        }

        if (node->getMethodCall()) {
            node->getMethodCall()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<MethodCallExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getMethodCall()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<NewDeclaratorExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getNewToken()->accept(this->getChildVisitor(node));
        node->getType()->accept(this->getChildVisitor(node));
        node->getArguments()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SuffixExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
        node->getSuffix()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<PrefixExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getPrefix()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<BopExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftExpresion()->accept(this->getChildVisitor(node));
        node->getBop()->accept(this->getChildVisitor(node));
        node->getRightExpresion()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<TernaryExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftExpression()->accept(this->getChildVisitor(node));
        node->getBop()->accept(this->getChildVisitor(node));

        if (node->getTrueExpression()) {
            node->getTrueExpression()->accept(this->getChildVisitor(node));
        }

        node->getColon()->accept(this->getChildVisitor(node));
        node->getFalseExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<MatchExpressionCase> node) {
        this->getVisitor(node)->visit(node);

        if (node->getExpressionList()) {
            node->getExpressionList()->accept(this->getChildVisitor(node));
        }

        if (node->getDefaultToken()) {
            node->getDefaultToken()->accept(this->getChildVisitor(node));
        }

        node->getDoubleArrowToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<MatchExpression> node) {
        this->getVisitor(node)->visit(node);

        node->getMatchToken()->accept(this->getChildVisitor(node));
        node->getParExpresion()->accept(this->getChildVisitor(node));
        node->getLeftBra()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& matchExpressionCase : node->getMatchExpressionCases()) {
            matchExpressionCase->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FormalParameter> node) {
        this->getVisitor(node)->visit(node);

        if (node->getType()) {
            node->getType()->accept(this->getChildVisitor(node));
        }

        if (node->getVariadic()) {
            node->getVariadic()->accept(this->getChildVisitor(node));
        }

        node->getIdentifier()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FormalParameterList> node) {
        this->getVisitor(node)->visit(node);

        int       i = 0;
        for (const auto& parameter : node->getParameters()) {
            parameter->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FormalParameters> node) {
        this->getVisitor(node)->visit(node);

        node->getLeftPar()->accept(this->getChildVisitor(node));

        if (node->getParameters()) {
            node->getParameters()->accept(this->getChildVisitor(node));
        }

        node->getRightPar()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FunctionHeader> node) {
        this->getVisitor(node)->visit(node);

        node->getFun()->accept(this->getChildVisitor(node));
        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getParameters()->accept(this->getChildVisitor(node));

        if  (node->getReturnType()) {
            node->getColon()->accept(this->getChildVisitor(node));
            node->getReturnType()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FunctionDeclaration> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getFunctionHeader()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<NullLiteral> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<BoolLiteral> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<NumberLiteral> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<CharLiteral> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<StringLiteral> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Identifier> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<TypeIdentifier> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VisibilityModifier> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<PackageName> node) {
        this->getVisitor(node)->visit(node);

        int       i = 0;
        for (const auto& identifier : node->getIdentifiers()) {
            identifier->accept(this->getChildVisitor(node));

            if (node->getDots().size() > i) {
                node->getDots()[i++]->accept(this->getChildVisitor(node));
            }
        }

        if (node->getTypeIdentifier()) {
            node->getTypeIdentifier()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<PackageDeclaration> node) {
        this->getVisitor(node)->visit(node);

        node->getPackageToken()->accept(this->getChildVisitor(node));
        node->getPackageName()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ImportDeclaration> node) {
        this->getVisitor(node)->visit(node);

        node->getImportToken()->accept(this->getChildVisitor(node));
        node->getPackageName()->accept(this->getChildVisitor(node));

        if (node->getAlias()) {
            node->getAsToken()->accept(this->getChildVisitor(node));
            node->getAlias()->accept(this->getChildVisitor(node));
        }

        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SourceFile> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        if (node->getPackageDeclaration()) {
            node->getPackageDeclaration()->accept(this->getChildVisitor(node));
        }

        std::for_each(
            node->getImportDeclarations().begin(),
            node->getImportDeclarations().end(),
            [this, node](const ImportDeclarationPtr & i) { i->accept(this->getChildVisitor(node)); }
        );

        std::for_each(
            node->getStatements().begin(),
            node->getStatements().end(),
            [this, node](const StatementPtr & i) { i->accept(this->getChildVisitor(node)); }
        );
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ReturnStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ThrowStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<BreakStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getNumberLiteral()) {
            node->getNumberLiteral()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ContinueStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getNumberLiteral()) {
            node->getNumberLiteral()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<IfStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));

        if (node->getElseToken()) {
            node->getElseToken()->accept(this->getChildVisitor(node));
            node->getElseStatement()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<UnlessStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));

        if (node->getElseToken()) {
            node->getElseToken()->accept(this->getChildVisitor(node));
            node->getElseStatement()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<WhileStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<UntilStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<LoopStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getExpresion()) {
            node->getExpresion()->accept(this->getChildVisitor(node));
        }

        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<DoWhileStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getDoToken()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ForControl> node) {
        this->getVisitor(node)->visit(node);

        if (node->getVariableDeclaration()) {
            node->getVariableDeclaration()->accept(this->getChildVisitor(node));
        }

        if (node->getExpressionList()) {
            node->getExpressionList()->accept(this->getChildVisitor(node));
        }

        node->getSemicolons()[0]->accept(this->getChildVisitor(node));

        if (node->getExpression()) {
            node->getExpression()->accept(this->getChildVisitor(node));
        }

        node->getSemicolons()[1]->accept(this->getChildVisitor(node));

        if (node->getUpdateExpressionList()) {
            node->getUpdateExpressionList()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ForStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getForToken()->accept(this->getChildVisitor(node));
        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getControl()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ForeachControl> node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
        node->getAsToken()->accept(this->getChildVisitor(node));
        node->getIdentifiers()[0]->accept(this->getChildVisitor(node));

        if (node->getIdentifiers().size() == 2) {
            node->getDoubleArrow()->accept(this->getChildVisitor(node));
            node->getIdentifiers()[1]->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ForeachStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getForeachToken()->accept(this->getChildVisitor(node));
        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getControl()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<CatchClause> node) {
        this->getVisitor(node)->visit(node);

        node->getCatchToken()->accept(this->getChildVisitor(node));
        node->getLeftPar()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& pipe : node->getPipes()) {
            pipe->accept(this->getChildVisitor(node));

            if (node->getPipes().size() > i) {
                node->getPipes()[i++]->accept(this->getChildVisitor(node));
            }
        }

        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<FinallyBlock> node) {
        this->getVisitor(node)->visit(node);

        node->getFinallyToken()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<TryStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getTryToken()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getCatches().begin(),
            node->getCatches().end(),
            [this, node](const CatchClausePtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        if (node->getFinallyBlock()) {
            node->getFinallyBlock()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SwitchLabel> node) {
        this->getVisitor(node)->visit(node);

        if (node->getDefaultToken()) {
            node->getDefaultToken()->accept(this->getChildVisitor(node));
        }

        if (node->getCaseToken()) {
            node->getCaseToken()->accept(this->getChildVisitor(node));
        }

        if (node->getIdentifier()) {
            node->getIdentifier()->accept(this->getChildVisitor(node));
        }

        if (node->getExpression()) {
            node->getExpression()->accept(this->getChildVisitor(node));
        }

        node->getColon()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SwitchBlockStatementGroup> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getSwitchLabels().begin(),
            node->getSwitchLabels().end(),
            [this, node](const SwitchLabelPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        std::for_each(
            node->getStatements().begin(),
            node->getStatements().end(),
            [this, node](const StatementPtr & i) { i->accept(this->getChildVisitor(node)); }
        );
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<SwitchStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getSwitchToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getLeftBra()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getSwitchBlockStatementGroups().begin(),
            node->getSwitchBlockStatementGroups().end(),
            [this, node](const SwitchBlockStatementGroupPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        std::for_each(
            node->getSwitchLabels().begin(),
            node->getSwitchLabels().end(),
            [this, node](const SwitchLabelPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Token> node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Type> node) {
        this->getVisitor(node)->visit(node);

        node->getTypeIdentifier()->accept(this->getChildVisitor(node));

        if (node->getOpenBrace()) {
            node->getOpenBrace()->accept(this->getChildVisitor(node));

            if (node->getArraySize()) {
                node->getArraySize()->accept(this->getChildVisitor(node));
            }

            node->getCloseBrace()->accept(this->getChildVisitor(node));
        }

        if (node->getQuestionMark()) {
            node->getQuestionMark()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<TypeDeclaration> node) {
        this->getVisitor(node)->visit(node);

        int       i = 0;
        for (const auto& type : node->getTypes()) {
            type->accept(this->getChildVisitor(node));

            if (node->getPipes().size() > i) {
                node->getPipes()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VariableName> node) {
        this->getVisitor(node)->visit(node);

        if (node->getAtSign()) {
            node->getAtSign()->accept(this->getChildVisitor(node));
        }

        node->getIdentifier()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VariableNameDeclaration> node) {
        this->getVisitor(node)->visit(node);

        if (node->getTypeDeclaration()) {
            node->getTypeDeclaration()->accept(this->getChildVisitor(node));
        }

        node->getVariableName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VariableDeclarationExpression> node) {
        this->getVisitor(node)->visit(node);

        if (node->getAssign()) {
            node->getAssign()->accept(this->getChildVisitor(node));

            int       i = 0;
            for (const auto& expression : node->getExpressions()) {
                expression->accept(this->getChildVisitor(node));

                if (node->getCommas().size() > i) {
                    node->getCommas()[i++]->accept(this->getChildVisitor(node));
                }
            }
        }

        node->getSemicolon()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<VariableDeclaration> node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getVar()->accept(this->getChildVisitor(node));

        int       i = 0;
        for (const auto& name : node->getVariableNames()) {
            name->accept(this->getChildVisitor(node));

            if (node->getSeparators().size() > i) {
                node->getSeparators()[i++]->accept(this->getChildVisitor(node));
            }
        }

        node->getExpressions()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ExpressionStatement> node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<ClassMember> node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Expression> node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Statement> node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(std::shared_ptr<Literal> node) {
        this->getVisitor(node)->visit(node);
    }

    SimpleAstTreeNodeVisitor::SimpleAstTreeNodeVisitor(AstNodeVisitor* visitor)
        : _visitor(visitor) {
    }

    AstNodeVisitor* SimpleAstTreeNodeVisitor::getVisitor(std::shared_ptr<AstNode> node) {
        return _visitor;
    }

    AstNodeVisitor* SimpleAstTreeNodeVisitor::getChildVisitor(std::shared_ptr<AstNode> node) {
        return _visitor;
    }
}