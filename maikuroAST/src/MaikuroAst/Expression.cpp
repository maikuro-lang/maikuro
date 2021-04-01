#include "MaikuroAst/Expression.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"
#include "MaikuroAst/Variable.h"

namespace MaikuroAst {

    Expression::Expression() : Statement(nullptr) {
    }

    ExpressionList::ExpressionList(const ExpressionPtrVec& expressions, const TokenPtrVec& commas)
        : _expressions(expressions), _commas(commas) {
    }

    ExpressionList::ExpressionList(MaikuroParser::ExpressionListContext* ctx) : ExpressionList(
        eb_createExpressions(ctx->expression()),
        Token::createTokens(ctx->COMMA())
    ) {

    }

    int ExpressionList::getLine() {
        return _expressions[0]->getLine();
    }

    string ExpressionList::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec ExpressionList::getTokens() {
        TokenPtrVec tokens;

        int i = 0;
        for (const auto& expression : _expressions) {
            Token::mergeTokens(&tokens, expression->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        return tokens;
    }

    PrimaryExpression::PrimaryExpression(TokenPtr token) : _token(token) {
    }

    PrimaryExpression::PrimaryExpression(MaikuroParser::PrimaryContext* ctx) : PrimaryExpression(
        Token::createToken(ctx->children[0])
    ) {
    }

    int PrimaryExpression::getLine() {
        return _token->getLine();
    }

    string PrimaryExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec PrimaryExpression::getTokens() {
        return { _token };
    }

    VariableNameExpression::VariableNameExpression(VariableNamePtr variableName) : _variableName(
        variableName
    ) {
    }

    VariableNameExpression::VariableNameExpression(MaikuroParser::VariableNameContext* ctx)
        : VariableNameExpression(
        Utils::create<VariableName>(ctx)
    ) {
    }

    int VariableNameExpression::getLine() {
        return _variableName->getLine();
    }

    string VariableNameExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec VariableNameExpression::getTokens() {
        return _variableName->getTokens();
    }

    ParExpresion::ParExpresion(TokenPtr leftPar, ExpressionPtr expression, TokenPtr rightPar)
        : _leftPar(leftPar), _expression(expression), _rightPar(rightPar) {
    }

    ParExpresion::ParExpresion(MaikuroParser::ParExpressionContext* ctx) : ParExpresion(
        Token::createToken(ctx->LPAREN()),
        eb_createExpression(ctx->expression()),
        Token::createToken(ctx->RPAREN())
    ) {
    }

    int ParExpresion::getLine() {
        return _leftPar->getLine();
    }

    string ParExpresion::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec ParExpresion::getTokens() {
        TokenPtrVec tokens = { _leftPar };

        Token::mergeTokens(&tokens, _expression->getTokens());

        tokens.push_back(_rightPar);

        return tokens;
    }

    MethodCall::MethodCall(TokenPtr identifier, ArgumentsPtr arguments)
        : _identifier(identifier), _arguments(arguments) {
    }

    MethodCall::MethodCall(MaikuroParser::MethodCallContext* ctx) : MethodCall(
        Token::createToken(ctx->IDENTIFIER() ?: ctx->THIS() ?: ctx->SUPER()),
        Utils::create<Arguments>(ctx->arguments())
    ) {
    }

    int MethodCall::getLine() {
        return _identifier->getLine();
    }

    string MethodCall::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec MethodCall::getTokens() {
        TokenPtrVec tokens = { _identifier };

        Token::mergeTokens(&tokens, _arguments->getTokens());

        return tokens;
    }

    DotExpression::DotExpression(
        const ExpressionPtr& expression,
        const TokenPtr& dot,
        const TokenPtr& identifier,
        const MethodCallPtr& methodCall
    ) : _expression(expression), _dot(dot), _identifier(identifier), _methodCall(methodCall) {
    }

    DotExpression::DotExpression(MaikuroParser::ExpressionContext* ctx) : DotExpression(
        eb_createExpression(ctx->expression(0)),
        Token::createToken(ctx->bop),
        Token::createToken(
            ctx->dotExpression()->IDENTIFIER() ?: ctx->dotExpression()->THIS() ?: ctx->dotExpression()
                                                                                     ->SUPER() ?: nullptr
        ),
        ctx->dotExpression()->methodCall() ? Utils::create<MethodCall>(ctx->dotExpression()->methodCall()) : nullptr
    ) {
    }

    int DotExpression::getLine() {
        return _expression->getLine();
    }

    string DotExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec DotExpression::getTokens() {
        TokenPtrVec tokens = _expression->getTokens();

        tokens.push_back(_dot);

        if (_methodCall) {
            Token::mergeTokens(&tokens, _methodCall->getTokens());
        } else {
            tokens.push_back(_identifier);
        }

        return tokens;
    }

    MethodCallExpression::MethodCallExpression(const MethodCallPtr& methodCall) : _methodCall(methodCall) {
    }

    MethodCallExpression::MethodCallExpression(MaikuroParser::ExpressionContext* ctx)
        : MethodCallExpression(
        Utils::create<MethodCall>(ctx->methodCall())
    ) {
    }

    int MethodCallExpression::getLine() {
        return _methodCall->getLine();
    }

    string MethodCallExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec MethodCallExpression::getTokens() {
        return _methodCall->getTokens();
    }

    NewDeclaratorExpression::NewDeclaratorExpression(
        const TokenPtr& newToken,
        const TypePtr& type,
        const ArgumentsPtr& arguments
    ) : _newToken(
        newToken
    ), _type(type), _arguments(arguments) {
    }

    NewDeclaratorExpression::NewDeclaratorExpression(MaikuroParser::NewDeclaratorContext* ctx)
        : NewDeclaratorExpression(
        Token::createToken(ctx->NEW()),
        Utils::create<Type>(ctx->type()),
        Utils::create<Arguments>(ctx->arguments())
    ) {
    }

    int NewDeclaratorExpression::getLine() {
        return _newToken->getLine();
    }

    string NewDeclaratorExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec NewDeclaratorExpression::getTokens() {
        TokenPtrVec tokens = { _newToken };

        Token::mergeTokens(&tokens, _type->getTokens());
        Token::mergeTokens(&tokens, _arguments->getTokens());

        return tokens;
    }

    SuffixExpression::SuffixExpression(const ExpressionPtr& expression, const TokenPtr& suffix)
        : _expression(expression), _suffix(suffix) {
    }

    SuffixExpression::SuffixExpression(MaikuroParser::ExpressionContext* ctx) : SuffixExpression(
        eb_createExpression(ctx->expression(0)),
        Token::createToken(ctx->suffix)
    ) {
    }

    int SuffixExpression::getLine() {
        return _expression->getLine();
    }

    string SuffixExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec SuffixExpression::getTokens() {
        TokenPtrVec tokens = _expression->getTokens();

        tokens.push_back(_suffix);

        return tokens;
    }

    PrefixExpression::PrefixExpression(const TokenPtr& prefix, const ExpressionPtr& expression)
        : _prefix(prefix), _expression(expression) {
    }

    PrefixExpression::PrefixExpression(MaikuroParser::ExpressionContext* ctx) : PrefixExpression(
        Token::createToken(ctx->prefix),
        eb_createExpression(ctx->expression(0))
    ) {
    }

    int PrefixExpression::getLine() {
        return _expression->getLine();
    }

    string PrefixExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec PrefixExpression::getTokens() {
        TokenPtrVec tokens = { _prefix };

        Token::mergeTokens(&tokens, _expression->getTokens());

        return tokens;
    }

    BopExpression::BopExpression(
        const ExpressionPtr& leftExpresion,
        const TokenPtr& bop,
        const ExpressionPtr& rightExpresion
    )
        : _leftExpresion(leftExpresion), _bop(bop), _rightExpresion(rightExpresion) {
    }

    BopExpression::BopExpression(MaikuroParser::ExpressionContext* ctx) : BopExpression(
        eb_createExpression(ctx->expression(0)),
        Token::createToken(ctx->bop),
        eb_createExpression(ctx->expression(1))
    ) {
    }

    int BopExpression::getLine() {
        return _leftExpresion->getLine();
    }

    string BopExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec BopExpression::getTokens() {
        TokenPtrVec tokens = _leftExpresion->getTokens();

        tokens.push_back(_bop);

        Token::mergeTokens(&tokens, _rightExpresion->getTokens());

        return tokens;
    }

    TernaryExpression::TernaryExpression(
        const ExpressionPtr& leftExpression,
        const TokenPtr& bop,
        const ExpressionPtr& trueExpression,
        const TokenPtr& colon,
        const ExpressionPtr& falseExpression
    )
        : _leftExpression(leftExpression),
          _bop(bop),
          _trueExpression(trueExpression),
          _colon(colon),
          _falseExpression(falseExpression) {
    }

    TernaryExpression::TernaryExpression(MaikuroParser::ExpressionContext* ctx) : TernaryExpression(
        nullptr,
        Token::createToken(ctx->bop),
        nullptr,
        Token::createToken(ctx->COLON()),
        nullptr
    ) {
        _leftExpression = eb_createExpression(ctx->expression(0));
        if (ctx->expression().size() == 2) {
            _falseExpression = eb_createExpression(ctx->expression(1));
        } else {
            _trueExpression = eb_createExpression(ctx->expression(1));
            _falseExpression = eb_createExpression(ctx->expression(2));
        }
    }

    int TernaryExpression::getLine() {
        return _leftExpression->getLine();
    }

    string TernaryExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec TernaryExpression::getTokens() {
        TokenPtrVec tokens = _leftExpression->getTokens();

        tokens.push_back(_bop);

        if (_trueExpression) {
            Token::mergeTokens(&tokens, _trueExpression->getTokens());
        }

        tokens.push_back(_colon);

        Token::mergeTokens(&tokens, _falseExpression->getTokens());

        return tokens;
    }

    MatchExpressionCase::MatchExpressionCase(
        const ExpressionListPtr& expressionList,
        const TokenPtr& defaultToken,
        const TokenPtr& doubleArrowToken,
        const ExpressionPtr& expression
    )
        : _expressionList(expressionList),
          _defaultToken(defaultToken),
          _doubleArrowToken(doubleArrowToken),
          _expression(expression) {
    }

    MatchExpressionCase::MatchExpressionCase(MaikuroParser::MatchExpressionCaseContext* ctx)
        : MatchExpressionCase(
        ctx->expressionList() ? Utils::create<ExpressionList>(ctx->expressionList()) : nullptr,
        Token::createToken(ctx->DEFAULT()),
        Token::createToken(ctx->DOUBLE_ARROW()),
        eb_createExpression(ctx->expression())
    ) {

    }

    int MatchExpressionCase::getLine() {
        return _doubleArrowToken->getLine();
    }

    string MatchExpressionCase::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec MatchExpressionCase::getTokens() {
        TokenPtrVec tokens;

        if (_defaultToken) {
            tokens.push_back(_defaultToken);
        } else {
            Token::mergeTokens(&tokens, _expressionList->getTokens());
        }

        tokens.push_back(_doubleArrowToken);

        Token::mergeTokens(&tokens, _expression->getTokens());

        return tokens;
    }

    MatchExpression::MatchExpression(
        const TokenPtr& matchToken,
        const ParExpresionPtr& parExpresion,
        const TokenPtr& leftBra,
        const MatchExpressionCasePtrVec& matchExpressionCases,
        const TokenPtrVec& commas,
        const TokenPtr& rightBra
    )
        : _matchToken(matchToken),
          _parExpresion(parExpresion),
          _leftBra(leftBra),
          _matchExpressionCases(matchExpressionCases),
          _commas(commas),
          _rightBra(rightBra) {
    }

    MatchExpression::MatchExpression(MaikuroParser::ExpressionContext* ctx) : MatchExpression(
        Token::createToken(ctx->MATCH()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        Token::createToken(ctx->LBRACE()),
        Utils::create<MatchExpressionCase>(ctx->matchExpressionCase()),
        Token::createTokens(ctx->COMMA()),
        Token::createToken(ctx->RBRACE())
    ) {
    }

    int MatchExpression::getLine() {
        return _matchToken->getLine();
    }

    string MatchExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec MatchExpression::getTokens() {
        TokenPtrVec tokens = { _matchToken };

        Token::mergeTokens(&tokens, _parExpresion->getTokens());

        tokens.push_back(_leftBra);

        Token::mergeTokens(&tokens, Utils::getTokens<MatchExpressionCase>(_matchExpressionCases));

        tokens.push_back(_rightBra);

        return tokens;
    }
}