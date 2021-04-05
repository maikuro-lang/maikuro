#include "MaikuroAst.h"

namespace MaikuroAst {

    void AstTreeNodeVisitor::visit(AliasDeclaration* node) {
        this->getVisitor(node)->visit(node);

        node->getAliasToken()->accept(this->getChildVisitor(node));
        node->getType()->accept(this->getChildVisitor(node));
        node->getAssignToken()->accept(this->getChildVisitor(node));
        node->getTypeDeclaration()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(Annotation* node) {
        this->getVisitor(node)->visit(node);

        node->getTypeIdentifier()->accept(this->getChildVisitor(node));

        if (node->getArguments()) {
            node->getArguments()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(Annotations* node) {
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

    void AstTreeNodeVisitor::visit(Argument* node) {
        this->getVisitor(node)->visit(node);

        if (node->getIdentifier()) {
            node->getIdentifier()->accept(this->getChildVisitor(node));
            node->getColon()->accept(this->getChildVisitor(node));
        }

        node->getExpression()->accept(this->getChildVisitor(node));

    }

    void AstTreeNodeVisitor::visit(Arguments* node) {
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

    void AstTreeNodeVisitor::visit(Block* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftBra()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getStatements().begin(),
            node->getStatements().end(),
            [this, node](const StatementPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(SuperClass* node) {
        this->getVisitor(node)->visit(node);

        node->getExtendsToken()->accept(this->getChildVisitor(node));
        node->getClassName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(SuperInterfaces* node) {
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

    void AstTreeNodeVisitor::visit(PropertyDeclaration* node) {
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

    void AstTreeNodeVisitor::visit(MethodDeclaration* node) {
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

    void AstTreeNodeVisitor::visit(AnnotationMember* node) {
        this->getVisitor(node)->visit(node);

        node->getAnnotations()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ClassBody* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftBra()->accept(this->getChildVisitor(node));

        std::for_each(
            node->getClassMembers().begin(),
            node->getClassMembers().end(),
            [this, node](const ClassMemberPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getRightBra()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ClassDeclaration* node) {
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

    void AstTreeNodeVisitor::visit(ExpressionList* node) {
        this->getVisitor(node)->visit(node);

        int i = 0;
        for (const auto& expression : node->getExpressions()) {
            expression->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(PrimaryExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(VariableNameExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getVariableName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ParExpresion* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(MethodCall* node) {
        this->getVisitor(node)->visit(node);

        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getArguments()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(DotExpression* node) {
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

    void AstTreeNodeVisitor::visit(MethodCallExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getMethodCall()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(NewDeclaratorExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getNewToken()->accept(this->getChildVisitor(node));
        node->getType()->accept(this->getChildVisitor(node));
        node->getArguments()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(SuffixExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
        node->getSuffix()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(PrefixExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getPrefix()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(BopExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftExpresion()->accept(this->getChildVisitor(node));
        node->getBop()->accept(this->getChildVisitor(node));
        node->getRightExpresion()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(TernaryExpression* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftExpression()->accept(this->getChildVisitor(node));
        node->getBop()->accept(this->getChildVisitor(node));

        if (node->getTrueExpression()) {
            node->getTrueExpression()->accept(this->getChildVisitor(node));
        }

        node->getColon()->accept(this->getChildVisitor(node));
        node->getFalseExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(MatchExpressionCase* node) {
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

    void AstTreeNodeVisitor::visit(MatchExpression* node) {
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

    void AstTreeNodeVisitor::visit(FormalParameter* node) {
        this->getVisitor(node)->visit(node);

        if (node->getType()) {
            node->getType()->accept(this->getChildVisitor(node));
        }

        if (node->getVariadic()) {
            node->getVariadic()->accept(this->getChildVisitor(node));
        }

        node->getIdentifier()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(FormalParameterList* node) {
        this->getVisitor(node)->visit(node);

        int       i = 0;
        for (const auto& parameter : node->getParameters()) {
            parameter->accept(this->getChildVisitor(node));

            if (node->getCommas().size() > i) {
                node->getCommas()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(FormalParameters* node) {
        this->getVisitor(node)->visit(node);

        node->getLeftPar()->accept(this->getChildVisitor(node));

        if (node->getParameters()) {
            node->getParameters()->accept(this->getChildVisitor(node));
        }

        node->getRightPar()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(FunctionHeader* node) {
        this->getVisitor(node)->visit(node);

        node->getFun()->accept(this->getChildVisitor(node));
        node->getIdentifier()->accept(this->getChildVisitor(node));
        node->getParameters()->accept(this->getChildVisitor(node));

        if  (node->getReturnType()) {
            node->getColon()->accept(this->getChildVisitor(node));
            node->getReturnType()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(FunctionDeclaration* node) {
        this->getVisitor(node)->visit(node);

        std::for_each(
            node->getAnnotations().begin(),
            node->getAnnotations().end(),
            [this, node](const AnnotationsPtr& i) { i->accept(this->getChildVisitor(node)); }
        );

        node->getFunctionHeader()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(NullLiteral* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(BoolLiteral* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(NumberLiteral* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(CharLiteral* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(StringLiteral* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(Identifier* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(TypeIdentifier* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(VisibilityModifier* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(PackageName* node) {
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

    void AstTreeNodeVisitor::visit(PackageDeclaration* node) {
        this->getVisitor(node)->visit(node);

        node->getPackageToken()->accept(this->getChildVisitor(node));
        node->getPackageName()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ImportDeclaration* node) {
        this->getVisitor(node)->visit(node);

        node->getImportToken()->accept(this->getChildVisitor(node));
        node->getPackageName()->accept(this->getChildVisitor(node));

        if (node->getAlias()) {
            node->getAsToken()->accept(this->getChildVisitor(node));
            node->getAlias()->accept(this->getChildVisitor(node));
        }

        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(SourceFile* node) {
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

    void AstTreeNodeVisitor::visit(ReturnStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ThrowStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(BreakStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getNumberLiteral()) {
            node->getNumberLiteral()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(ContinueStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getNumberLiteral()) {
            node->getNumberLiteral()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(IfStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));

        if (node->getElseToken()) {
            node->getElseToken()->accept(this->getChildVisitor(node));
            node->getElseStatement()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(UnlessStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));

        if (node->getElseToken()) {
            node->getElseToken()->accept(this->getChildVisitor(node));
            node->getElseStatement()->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(WhileStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(UntilStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(LoopStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getToken()->accept(this->getChildVisitor(node));

        if (node->getExpresion()) {
            node->getExpresion()->accept(this->getChildVisitor(node));
        }

        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(DoWhileStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getDoToken()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
        node->getToken()->accept(this->getChildVisitor(node));
        node->getExpresion()->accept(this->getChildVisitor(node));
        node->getSemicolonToken()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ForControl* node) {
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

    void AstTreeNodeVisitor::visit(ForStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getForToken()->accept(this->getChildVisitor(node));
        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getControl()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ForeachControl* node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
        node->getAsToken()->accept(this->getChildVisitor(node));
        node->getIdentifiers()[0]->accept(this->getChildVisitor(node));

        if (node->getIdentifiers().size() == 2) {
            node->getDoubleArrow()->accept(this->getChildVisitor(node));
            node->getIdentifiers()[1]->accept(this->getChildVisitor(node));
        }
    }

    void AstTreeNodeVisitor::visit(ForeachStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getForeachToken()->accept(this->getChildVisitor(node));
        node->getLeftPar()->accept(this->getChildVisitor(node));
        node->getControl()->accept(this->getChildVisitor(node));
        node->getRightPar()->accept(this->getChildVisitor(node));
        node->getStatement()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(CatchClause* node) {
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

    void AstTreeNodeVisitor::visit(FinallyBlock* node) {
        this->getVisitor(node)->visit(node);

        node->getFinallyToken()->accept(this->getChildVisitor(node));
        node->getBlock()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(TryStatement* node) {
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

    void AstTreeNodeVisitor::visit(SwitchLabel* node) {
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

    void AstTreeNodeVisitor::visit(SwitchBlockStatementGroup* node) {
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

    void AstTreeNodeVisitor::visit(SwitchStatement* node) {
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

    void AstTreeNodeVisitor::visit(Token* node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(Type* node) {
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

    void AstTreeNodeVisitor::visit(TypeDeclaration* node) {
        this->getVisitor(node)->visit(node);

        int       i = 0;
        for (const auto& type : node->getTypes()) {
            type->accept(this->getChildVisitor(node));

            if (node->getPipes().size() > i) {
                node->getPipes()[i++]->accept(this->getChildVisitor(node));
            }
        }
    }

    void AstTreeNodeVisitor::visit(VariableName* node) {
        this->getVisitor(node)->visit(node);

        if (node->getAtSign()) {
            node->getAtSign()->accept(this->getChildVisitor(node));
        }

        node->getIdentifier()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(VariableNameDeclaration* node) {
        this->getVisitor(node)->visit(node);

        if (node->getTypeDeclaration()) {
            node->getTypeDeclaration()->accept(this->getChildVisitor(node));
        }

        node->getVariableName()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(VariableDeclarationExpression* node) {
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

    void AstTreeNodeVisitor::visit(VariableDeclaration* node) {
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

    void AstTreeNodeVisitor::visit(ExpressionStatement* node) {
        this->getVisitor(node)->visit(node);

        node->getExpression()->accept(this->getChildVisitor(node));
    }

    void AstTreeNodeVisitor::visit(ClassMember* node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(Expression* node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(Statement* node) {
        this->getVisitor(node)->visit(node);
    }

    void AstTreeNodeVisitor::visit(Literal* node) {
        this->getVisitor(node)->visit(node);
    }

    AstNodeVisitor* SimpleAstTreeNodeVisitor::getVisitor(AstNode* node) {
        return _visitor;
    }

    SimpleAstTreeNodeVisitor::SimpleAstTreeNodeVisitor(AstNodeVisitor* visitor)
        : _visitor(visitor) {
    }

    AstNodeVisitor* SimpleAstTreeNodeVisitor::getChildVisitor(AstNode* node) {
        return _visitor;
    }
}