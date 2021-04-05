#pragma once

#include "common.h"
#include "Statement.h"
#include "Argument.h"
#include "Variable.h"
#include "Annotation.h"
#include "AstNode.h"
#include "Token.h"
#include "Type.h"

namespace MaikuroAst {

    class Expression : public AstNode, public EnableSharedFromThisVirtual<Expression> {
     public:
        Expression();

        NodeType getNodeType() override;

     private:
    };

    typedef std::shared_ptr<Expression> ExpressionPtr;
    typedef std::vector<ExpressionPtr>  ExpressionPtrVec;

    class ExpressionStatement : public Statement, public EnableSharedFromThisVirtual<ExpressionStatement> {
     public:
        ExpressionStatement(ExpressionPtr expression, TokenPtr semicolon);

        explicit ExpressionStatement(MaikuroGrammar::MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        std::string toString() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtr& getExpression() const;

     private:
        ExpressionPtr _expression;
    };

    typedef std::shared_ptr<ExpressionStatement> ExpressionStatementPtr;

    class ExpressionList : public AstNode, public EnableSharedFromThisVirtual<ExpressionList> {
     public:
        ExpressionList(const ExpressionPtrVec& expressions, const TokenPtrVec& commas);

        explicit ExpressionList(MaikuroGrammar::MaikuroParser::ExpressionListContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtrVec& getExpressions() const;

        const TokenPtrVec& getCommas() const;

     private:
        ExpressionPtrVec _expressions;
        TokenPtrVec      _commas;
    };

    typedef std::shared_ptr<ExpressionList> ExpressionListPtr;

    class PrimaryExpression : public Expression, public EnableSharedFromThisVirtual<PrimaryExpression> {
     public:
        explicit PrimaryExpression(TokenPtr token);

        explicit PrimaryExpression(MaikuroGrammar::MaikuroParser::PrimaryContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getToken() const;

     private:
        TokenPtr _token;
    };

    typedef std::shared_ptr<PrimaryExpression> PrimaryExpressionPtr;

    class VariableNameExpression : public Expression, public EnableSharedFromThisVirtual<VariableNameExpression> {
     public:
        explicit VariableNameExpression(VariableNamePtr variableName);

        explicit VariableNameExpression(MaikuroGrammar::MaikuroParser::VariableNameContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const VariableNamePtr& getVariableName() const;

     private:
        VariableNamePtr _variableName;
    };

    typedef std::shared_ptr<VariableNameExpression> VariableNameExpressionPtr;
    typedef std::vector<VariableNameExpressionPtr>  VariableNameExpressionPtrVec;

    class ParExpresion : public Expression, public EnableSharedFromThisVirtual<ParExpresion> {
     public:
        ParExpresion(TokenPtr leftPar, ExpressionPtr expression, TokenPtr rightPar);

        explicit ParExpresion(MaikuroGrammar::MaikuroParser::ParExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getLeftPar() const;

        const ExpressionPtr& getExpression() const;

        const TokenPtr& getRightPar() const;

     private:
        TokenPtr      _leftPar;
        ExpressionPtr _expression;
        TokenPtr      _rightPar;
    };

    typedef std::shared_ptr<ParExpresion> ParExpresionPtr;

    class MethodCall : public AstNode, public EnableSharedFromThisVirtual<MethodCall> {
     public:
        MethodCall(TokenPtr identifier, ArgumentsPtr arguments);

        explicit MethodCall(MaikuroGrammar::MaikuroParser::MethodCallContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getIdentifier() const;

        const ArgumentsPtr& getArguments() const;

     private:
        TokenPtr     _identifier;
        ArgumentsPtr _arguments;
    };

    typedef std::shared_ptr<MethodCall> MethodCallPtr;

    class DotExpression : public Expression, public EnableSharedFromThisVirtual<DotExpression> {
     public:
        DotExpression(
            const ExpressionPtr& expression,
            const TokenPtr& dot,
            const TokenPtr& identifier,
            const MethodCallPtr& methodCall
        );

        explicit DotExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtr& getExpression() const;

        const TokenPtr& getDot() const;

        const TokenPtr& getIdentifier() const;

        const MethodCallPtr& getMethodCall() const;

     private:
        ExpressionPtr _expression;
        TokenPtr      _dot;
        TokenPtr      _identifier;
        MethodCallPtr _methodCall;
    };

    typedef std::shared_ptr<DotExpression> DotExpressionPtr;

    class MethodCallExpression : public Expression, public EnableSharedFromThisVirtual<MethodCallExpression> {
     public:
        explicit MethodCallExpression(const MethodCallPtr& methodCall);

        explicit MethodCallExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const MethodCallPtr& getMethodCall() const;

     private:
        MethodCallPtr _methodCall;
    };

    typedef std::shared_ptr<MethodCallExpression> MethodCallExpressionPtr;

    class NewDeclaratorExpression : public Expression, public EnableSharedFromThisVirtual<NewDeclaratorExpression> {
     public:
        NewDeclaratorExpression(const TokenPtr& newToken, const TypePtr& type, const ArgumentsPtr& arguments);

        explicit NewDeclaratorExpression(MaikuroGrammar::MaikuroParser::NewDeclaratorContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getNewToken() const;

        const TypePtr& getType() const;

        const ArgumentsPtr& getArguments() const;

     private:
        TokenPtr     _newToken;
        TypePtr      _type;
        ArgumentsPtr _arguments;
    };

    typedef std::shared_ptr<NewDeclaratorExpression> NewDeclaratorExpressionPtr;

    class SuffixExpression : public Expression, public EnableSharedFromThisVirtual<SuffixExpression> {
     public:
        SuffixExpression(const ExpressionPtr& expression, const TokenPtr& suffix);

        explicit SuffixExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtr& getExpression() const;

        const TokenPtr& getSuffix() const;

     private:
        ExpressionPtr _expression;
        TokenPtr      _suffix;
    };

    typedef std::shared_ptr<SuffixExpression> SuffixExpressionPtr;

    class PrefixExpression : public Expression, public EnableSharedFromThisVirtual<PrefixExpression> {
     public:
        PrefixExpression(const TokenPtr& prefix, const ExpressionPtr& expression);

        explicit PrefixExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getPrefix() const;

        const ExpressionPtr& getExpression() const;

     private:
        TokenPtr      _prefix;
        ExpressionPtr _expression;
    };

    typedef std::shared_ptr<PrefixExpression> PrefixExpressionPtr;

    class BopExpression : public Expression, public EnableSharedFromThisVirtual<BopExpression> {
     public:
        BopExpression(const ExpressionPtr& leftExpresion, const TokenPtr& bop, const ExpressionPtr& rightExpresion);

        explicit BopExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtr& getLeftExpresion() const;

        const TokenPtr& getBop() const;

        const ExpressionPtr& getRightExpresion() const;

     private:
        ExpressionPtr _leftExpresion;
        TokenPtr      _bop;
        ExpressionPtr _rightExpresion;
    };

    typedef std::shared_ptr<BopExpression> BopExpressionPtr;

    class TernaryExpression : public Expression, public EnableSharedFromThisVirtual<TernaryExpression> {
     public:
        TernaryExpression(
            const ExpressionPtr& leftExpression,
            const TokenPtr& bop,
            const ExpressionPtr& trueExpression,
            const TokenPtr& colon,
            const ExpressionPtr& falseExpression
        );

        explicit TernaryExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionPtr& getLeftExpression() const;

        const TokenPtr& getBop() const;

        const ExpressionPtr& getTrueExpression() const;

        const TokenPtr& getColon() const;

        const ExpressionPtr& getFalseExpression() const;

     private:
        ExpressionPtr _leftExpression;
        TokenPtr      _bop;
        ExpressionPtr _trueExpression;
        TokenPtr      _colon;
        ExpressionPtr _falseExpression;
    };

    typedef std::shared_ptr<TernaryExpression> TernaryExpressionPtr;

    class MatchExpressionCase : public AstNode, public EnableSharedFromThisVirtual<MatchExpressionCase> {
     public:
        MatchExpressionCase(
            const ExpressionListPtr& expressionList,
            const TokenPtr& defaultToken,
            const TokenPtr& doubleArrowToken,
            const ExpressionPtr& expression
        );

        explicit MatchExpressionCase(MaikuroGrammar::MaikuroParser::MatchExpressionCaseContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const ExpressionListPtr& getExpressionList() const;

        const TokenPtr& getDefaultToken() const;

        const TokenPtr& getDoubleArrowToken() const;

        const ExpressionPtr& getExpression() const;

     private:
        ExpressionListPtr _expressionList;
        TokenPtr          _defaultToken;
        TokenPtr          _doubleArrowToken;
        ExpressionPtr     _expression;
    };

    typedef std::shared_ptr<MatchExpressionCase> MatchExpressionCasePtr;
    typedef std::vector<MatchExpressionCasePtr>  MatchExpressionCasePtrVec;

    class MatchExpression : public Expression, public EnableSharedFromThisVirtual<MatchExpression> {
     public:
        MatchExpression(
            const TokenPtr& matchToken,
            const ParExpresionPtr& parExpresion,
            const TokenPtr& leftBra,
            const MatchExpressionCasePtrVec& matchExpressionCases,
            const TokenPtrVec& commas,
            const TokenPtr& rightBra
        );

        explicit MatchExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const TokenPtr& getMatchToken() const;

        const ParExpresionPtr& getParExpresion() const;

        const TokenPtr& getLeftBra() const;

        const MatchExpressionCasePtrVec& getMatchExpressionCases() const;

        const TokenPtrVec& getCommas() const;

        const TokenPtr& getRightBra() const;

     private:
        TokenPtr                  _matchToken;
        ParExpresionPtr           _parExpresion;
        TokenPtr                  _leftBra;
        MatchExpressionCasePtrVec _matchExpressionCases;
        TokenPtrVec               _commas;
        TokenPtr                  _rightBra;
    };

    typedef std::shared_ptr<MatchExpression> MatchExpressionPtr;
}

