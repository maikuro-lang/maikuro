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
    class Expression : public Statement {
     public:
        Expression();
     private:
    };

    typedef shared_ptr<MaikuroAst::Expression>  ExpressionPtr;
    typedef vector<MaikuroAst::ExpressionPtr>   ExpressionPtrVec;

    class ExpressionList : public MaikuroAst::AstNode {
     public:
        ExpressionList(const ExpressionPtrVec& expressions, const TokenPtrVec& commas);

        explicit ExpressionList(MaikuroParser::ExpressionListContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionPtrVec _expressions;
        TokenPtrVec      _commas;
    };

    typedef shared_ptr<ExpressionList>          ExpressionListPtr;

    class PrimaryExpression : public MaikuroAst::Expression {
     public:
        explicit PrimaryExpression(TokenPtr token);

        explicit PrimaryExpression(MaikuroParser::PrimaryContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr _token;
    };

    typedef shared_ptr<PrimaryExpression>       PrimaryExpressionPtr;

    class VariableNameExpression : public MaikuroAst::Expression {
     public:
        explicit VariableNameExpression(VariableNamePtr variableName);

        explicit VariableNameExpression(MaikuroParser::VariableNameContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        VariableNamePtr _variableName;
    };

    typedef shared_ptr<VariableNameExpression>  VariableNameExpressionPtr;
    typedef vector<VariableNameExpressionPtr>   VariableNameExpressionPtrVec;

    class ParExpresion : public MaikuroAst::Expression {
     public:
        ParExpresion(TokenPtr leftPar, ExpressionPtr expression, TokenPtr rightPar);

        explicit ParExpresion(MaikuroParser::ParExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr                  _leftPar;
        ExpressionPtr _expression;
        TokenPtr                  _rightPar;
    };

    typedef shared_ptr<ParExpresion>            ParExpresionPtr;

    class MethodCall : public MaikuroAst::AstNode {
     public:
        MethodCall(TokenPtr identifier, ArgumentsPtr arguments);

        explicit MethodCall(MaikuroParser::MethodCallContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr                 _identifier;
        ArgumentsPtr _arguments;
    };

    typedef shared_ptr<MethodCall>              MethodCallPtr;

    class DotExpression : public MaikuroAst::Expression {
     public:
        DotExpression(
            const ExpressionPtr& expression,
            const TokenPtr& dot,
            const TokenPtr& identifier,
            const MethodCallPtr& methodCall
        );

        explicit DotExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionPtr _expression;
        TokenPtr                  _dot;
        TokenPtr      _identifier;
        MethodCallPtr _methodCall;
    };

    typedef shared_ptr<DotExpression>           DotExpressionPtr;

    class MethodCallExpression : public MaikuroAst::Expression {
     public:
        explicit MethodCallExpression(const MethodCallPtr& methodCall);

        explicit MethodCallExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        MethodCallPtr _methodCall;
    };

    typedef shared_ptr<MethodCallExpression>    MethodCallExpressionPtr;

    class NewDeclaratorExpression : public MaikuroAst::Expression {
     public:
        NewDeclaratorExpression(const TokenPtr& newToken, const TypePtr& type, const ArgumentsPtr& arguments);

        explicit NewDeclaratorExpression(MaikuroParser::NewDeclaratorContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr     _newToken;
        TypePtr                  _type;
        ArgumentsPtr _arguments;
    };

    typedef shared_ptr<NewDeclaratorExpression> NewDeclaratorExpressionPtr;

    class SuffixExpression : public MaikuroAst::Expression {
     public:
        SuffixExpression(const ExpressionPtr& expression, const TokenPtr& suffix);

        explicit SuffixExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionPtr _expression;
        TokenPtr                  _suffix;
    };

    typedef shared_ptr<SuffixExpression>        SuffixExpressionPtr;

    class PrefixExpression : public MaikuroAst::Expression {
     public:
        PrefixExpression(const TokenPtr& prefix, const ExpressionPtr& expression);

        explicit PrefixExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr                  _prefix;
        ExpressionPtr _expression;
    };

    typedef shared_ptr<PrefixExpression>        PrefixExpressionPtr;

    class BopExpression : public MaikuroAst::Expression {
     public:
        BopExpression(const ExpressionPtr& leftExpresion, const TokenPtr& bop, const ExpressionPtr& rightExpresion);

        explicit BopExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionPtr _leftExpresion;
        TokenPtr                  _bop;
        ExpressionPtr _rightExpresion;
    };

    typedef shared_ptr<BopExpression>           BopExpressionPtr;

    class TernaryExpression : public MaikuroAst::Expression {
     public:
        TernaryExpression(
            const ExpressionPtr& leftExpression,
            const TokenPtr& bop,
            const ExpressionPtr& trueExpression,
            const TokenPtr& colon,
            const ExpressionPtr& falseExpression
        );

        explicit TernaryExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionPtr _leftExpression;
        TokenPtr                  _bop;
        ExpressionPtr _trueExpression;
        TokenPtr                  _colon;
        ExpressionPtr _falseExpression;
    };

    typedef shared_ptr<TernaryExpression>       TernaryExpressionPtr;

    class MatchExpressionCase : public MaikuroAst::AstNode {
     public:
        MatchExpressionCase(
            const ExpressionListPtr& expressionList,
            const TokenPtr& defaultToken,
            const TokenPtr& doubleArrowToken,
            const ExpressionPtr& expression
        );

        explicit MatchExpressionCase(MaikuroParser::MatchExpressionCaseContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        ExpressionListPtr _expressionList;
        TokenPtr          _defaultToken;
        TokenPtr                  _doubleArrowToken;
        ExpressionPtr _expression;
    };

    typedef shared_ptr<MatchExpressionCase>     MatchExpressionCasePtr;
    typedef vector<MatchExpressionCasePtr>      MatchExpressionCasePtrVec;

    class MatchExpression : public MaikuroAst::Expression {
     public:
        MatchExpression(
            const TokenPtr& matchToken,
            const ParExpresionPtr& parExpresion,
            const TokenPtr& leftBra,
            const MatchExpressionCasePtrVec& matchExpressionCases,
            const TokenPtrVec& commas,
            const TokenPtr& rightBra
        );

        explicit MatchExpression(MaikuroParser::ExpressionContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr                  _matchToken;
        ParExpresionPtr           _parExpresion;
        TokenPtr                  _leftBra;
        MatchExpressionCasePtrVec _matchExpressionCases;
        TokenPtrVec               _commas;
        TokenPtr                  _rightBra;
    };

    typedef shared_ptr<MatchExpression>         MatchExpressionPtr;
}

