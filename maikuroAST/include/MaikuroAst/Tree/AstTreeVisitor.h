#pragma once

#include "MaikuroAst.h"
#include "AstTree.h"

namespace MaikuroAst::Tree {
    using namespace MaikuroAst;
    using std::vector;

    template<typename ReturnType>
    class AstTreeVisitor {
     public:
        template<typename T>
        vector<ReturnType> visit(vector<T> nodes) {
            vector<ReturnType> results;
            for (auto node : nodes) {
                results.push_back(visit(node));
            }

            return results;
        }

        virtual ReturnType visit(AliasDeclarationPtr node) = 0;
        virtual ReturnType visit(AnnotationPtr node) = 0;
        virtual ReturnType visit(AnnotationsPtr node) = 0;
        virtual ReturnType visit(ArgumentPtr node) = 0;
        virtual ReturnType visit(ArgumentsPtr node) = 0;
        virtual ReturnType visit(BlockPtr node) = 0;
        virtual ReturnType visit(SuperClassPtr node) = 0;
        virtual ReturnType visit(SuperInterfacesPtr node) = 0;
        virtual ReturnType visit(PropertyDeclarationPtr node) = 0;
        virtual ReturnType visit(MethodDeclarationPtr node) = 0;
        virtual ReturnType visit(AnnotationMemberPtr node) = 0;
        virtual ReturnType visit(ClassBodyPtr node) = 0;
        virtual ReturnType visit(ClassDeclarationPtr node) = 0;
        virtual ReturnType visit(ExpressionListPtr node) = 0;
        virtual ReturnType visit(PrimaryExpressionPtr node) = 0;
        virtual ReturnType visit(VariableNameExpressionPtr node) = 0;
        virtual ReturnType visit(ParExpresionPtr node) = 0;
        virtual ReturnType visit(MethodCallPtr node) = 0;
        virtual ReturnType visit(DotExpressionPtr node) = 0;
        virtual ReturnType visit(MethodCallExpressionPtr node) = 0;
        virtual ReturnType visit(NewDeclaratorExpressionPtr node) = 0;
        virtual ReturnType visit(SuffixExpressionPtr node) = 0;
        virtual ReturnType visit(PrefixExpressionPtr node) = 0;
        virtual ReturnType visit(BopExpressionPtr node) = 0;
        virtual ReturnType visit(TernaryExpressionPtr node) = 0;
        virtual ReturnType visit(MatchExpressionCasePtr node) = 0;
        virtual ReturnType visit(MatchExpressionPtr node) = 0;
        virtual ReturnType visit(FormalParameterPtr node) = 0;
        virtual ReturnType visit(FormalParameterListPtr node) = 0;
        virtual ReturnType visit(FormalParametersPtr node) = 0;
        virtual ReturnType visit(FunctionHeaderPtr node) = 0;
        virtual ReturnType visit(FunctionDeclarationPtr node) = 0;
        virtual ReturnType visit(NullLiteralPtr node) = 0;
        virtual ReturnType visit(BoolLiteralPtr node) = 0;
        virtual ReturnType visit(NumberLiteralPtr node) = 0;
        virtual ReturnType visit(CharLiteralPtr node) = 0;
        virtual ReturnType visit(StringLiteralPtr node) = 0;
        virtual ReturnType visit(IdentifierPtr node) = 0;
        virtual ReturnType visit(TypeIdentifierPtr node) = 0;
        virtual ReturnType visit(VisibilityModifierPtr node) = 0;
        virtual ReturnType visit(PackageNamePtr node) = 0;
        virtual ReturnType visit(PackageDeclarationPtr node) = 0;
        virtual ReturnType visit(ImportDeclarationPtr node) = 0;
        virtual ReturnType visit(SourceFilePtr node) = 0;
        virtual ReturnType visit(ReturnStatementPtr node) = 0;
        virtual ReturnType visit(ThrowStatementPtr node) = 0;
        virtual ReturnType visit(BreakStatementPtr node) = 0;
        virtual ReturnType visit(ContinueStatementPtr node) = 0;
        virtual ReturnType visit(IfStatementPtr node) = 0;
        virtual ReturnType visit(UnlessStatementPtr node) = 0;
        virtual ReturnType visit(WhileStatementPtr node) = 0;
        virtual ReturnType visit(UntilStatementPtr node) = 0;
        virtual ReturnType visit(LoopStatementPtr node) = 0;
        virtual ReturnType visit(DoWhileStatementPtr node) = 0;
        virtual ReturnType visit(ForControlPtr node) = 0;
        virtual ReturnType visit(ForStatementPtr node) = 0;
        virtual ReturnType visit(ForeachControlPtr node) = 0;
        virtual ReturnType visit(ForeachStatementPtr node) = 0;
        virtual ReturnType visit(CatchClausePtr node) = 0;
        virtual ReturnType visit(FinallyBlockPtr node) = 0;
        virtual ReturnType visit(TryStatementPtr node) = 0;
        virtual ReturnType visit(SwitchLabelPtr node) = 0;
        virtual ReturnType visit(SwitchBlockStatementGroupPtr node) = 0;
        virtual ReturnType visit(SwitchStatementPtr node) = 0;
        virtual ReturnType visit(TokenPtr node) = 0;
        virtual ReturnType visit(TypePtr node) = 0;
        virtual ReturnType visit(TypeDeclarationPtr node) = 0;
        virtual ReturnType visit(VariableNamePtr node) = 0;
        virtual ReturnType visit(VariableNameDeclarationPtr node) = 0;
        virtual ReturnType visit(VariableDeclarationExpressionPtr node) = 0;
        virtual ReturnType visit(VariableDeclarationPtr node) = 0;
        virtual ReturnType visit(ExpressionStatementPtr node) = 0;

        ReturnType visit(ClassMemberPtr node) {
            switch (node->getNodeType()) {
                case AstNode::NodeType::PROPERTY_DECLARATION:
                    return visit(std::dynamic_pointer_cast<PropertyDeclaration>(node));
                case AstNode::NodeType::METHOD_DECLARATION:
                    return visit(std::dynamic_pointer_cast<MethodDeclaration>(node));
                case AstNode::NodeType::ANNOTATION_MEMBER:
                    return visit(std::dynamic_pointer_cast<AnnotationMember>(node));
                default:
                    return nullptr;
            }
        }

        ReturnType visit(ExpressionPtr node) {
            switch (node->getNodeType()) {
                case AstNode::NodeType::BOP_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<BopExpression>(node));
                case AstNode::NodeType::DOT_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<DotExpression>(node));
                case AstNode::NodeType::MATCH_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<MatchExpression>(node));
                case AstNode::NodeType::METHOD_CALL_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<MethodCallExpression>(node));
                case AstNode::NodeType::NEW_DECLARATOR_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<NewDeclaratorExpression>(node));
                case AstNode::NodeType::PAR_EXPRESION:
                    return visit(std::dynamic_pointer_cast<ParExpresion>(node));
                case AstNode::NodeType::PREFIX_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<PrefixExpression>(node));
                case AstNode::NodeType::PRIMARY_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<PrimaryExpression>(node));
                case AstNode::NodeType::SUFFIX_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<SuffixExpression>(node));
                case AstNode::NodeType::TERNARY_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<TernaryExpression>(node));
                case AstNode::NodeType::VARIABLE_NAME_EXPRESSION:
                    return visit(std::dynamic_pointer_cast<VariableNameExpression>(node));
                default:
                    return nullptr;
            }
        }

        ReturnType visit(StatementPtr node) {
            switch (node->getNodeType()) {
                case AstNode::NodeType::ALIAS_DECLARATION:
                    return visit(std::dynamic_pointer_cast<AliasDeclaration>(node));
                case AstNode::NodeType::BLOCK:
                    return visit(std::dynamic_pointer_cast<Block>(node));
                case AstNode::NodeType::CLASS_DECLARATION:
                    return visit(std::dynamic_pointer_cast<ClassDeclaration>(node));
                case AstNode::NodeType::EXPRESSION_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ExpressionStatement>(node));
                case AstNode::NodeType::FOREACH_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ForeachControl>(node));
                case AstNode::NodeType::FOR_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ForStatement>(node));
                case AstNode::NodeType::FUNCTION_DECLARATION:
                    return visit(std::dynamic_pointer_cast<FunctionDeclaration>(node));
                case AstNode::NodeType::IF_STATEMENT:
                    return visit(std::dynamic_pointer_cast<IfStatement>(node));
                case AstNode::NodeType::UNLESS_STATEMENT:
                    return visit(std::dynamic_pointer_cast<UnlessStatement>(node));
                case AstNode::NodeType::SWITCH_STATEMENT:
                    return visit(std::dynamic_pointer_cast<SwitchStatement>(node));
                case AstNode::NodeType::TOKEN_EXPRESSION_STATEMENT:
                    return visit(std::dynamic_pointer_cast<TokenExpressionStatement>(node));
                case AstNode::NodeType::RETURN_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ReturnStatement>(node));
                case AstNode::NodeType::THROW_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ThrowStatement>(node));
                case AstNode::NodeType::TOKEN_NUMBER_LITERAL_STATEMENT:
                    return visit(std::dynamic_pointer_cast<TokenNumberLiteralStatement>(node));
                case AstNode::NodeType::BREAK_STATEMENT:
                    return visit(std::dynamic_pointer_cast<BreakStatement>(node));
                case AstNode::NodeType::CONTINUE_STATEMENT:
                    return visit(std::dynamic_pointer_cast<ContinueStatement>(node));
                case AstNode::NodeType::TRY_STATEMENT:
                    return visit(std::dynamic_pointer_cast<TryStatement>(node));
                case AstNode::NodeType::VARIABLE_DECLARATION:
                    return visit(std::dynamic_pointer_cast<VariableDeclaration>(node));
                case AstNode::NodeType::WHILE_STATEMENT:
                    return visit(std::dynamic_pointer_cast<WhileStatement>(node));
                case AstNode::NodeType::DO_WHILE_STATEMENT:
                    return visit(std::dynamic_pointer_cast<DoWhileStatement>(node));
                case AstNode::NodeType::LOOP_STATEMENT:
                    return visit(std::dynamic_pointer_cast<LoopStatement>(node));
                case AstNode::NodeType::UNTIL_STATEMENT:
                    return visit(std::dynamic_pointer_cast<UntilStatement>(node));
                default:
                    return nullptr;
            }
        }
    };
}