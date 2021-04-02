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

    Expression::Expression() {
    }

    AstNode::NodeType Expression::getNodeType() {
        return NodeType::EXPRESSION;
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

    const ExpressionPtrVec& ExpressionList::getExpressions() const {
        return _expressions;
    }

    const TokenPtrVec& ExpressionList::getCommas() const {
        return _commas;
    }

    AstNode::NodeType ExpressionList::getNodeType() {
        return NodeType::EXPRESSION_LIST;
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

    const TokenPtr& PrimaryExpression::getToken() const {
        return _token;
    }

    AstNode::NodeType PrimaryExpression::getNodeType() {
        return NodeType::PRIMARY_EXPRESSION;
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

    const VariableNamePtr& VariableNameExpression::getVariableName() const {
        return _variableName;
    }

    AstNode::NodeType VariableNameExpression::getNodeType() {
        return NodeType::VARIABLE_NAME;
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

    const TokenPtr& ParExpresion::getLeftPar() const {
        return _leftPar;
    }

    const ExpressionPtr& ParExpresion::getExpression() const {
        return _expression;
    }

    const TokenPtr& ParExpresion::getRightPar() const {
        return _rightPar;
    }

    AstNode::NodeType ParExpresion::getNodeType() {
        return NodeType::PAR_EXPRESION;
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

    const TokenPtr& MethodCall::getIdentifier() const {
        return _identifier;
    }

    const ArgumentsPtr& MethodCall::getArguments() const {
        return _arguments;
    }

    AstNode::NodeType MethodCall::getNodeType() {
        return NodeType::METHOD_CALL;
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

    const ExpressionPtr& DotExpression::getExpression() const {
        return _expression;
    }

    const TokenPtr& DotExpression::getDot() const {
        return _dot;
    }

    const TokenPtr& DotExpression::getIdentifier() const {
        return _identifier;
    }

    const MethodCallPtr& DotExpression::getMethodCall() const {
        return _methodCall;
    }

    AstNode::NodeType DotExpression::getNodeType() {
        return NodeType::DOT_EXPRESSION;
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

    const MethodCallPtr& MethodCallExpression::getMethodCall() const {
        return _methodCall;
    }

    AstNode::NodeType MethodCallExpression::getNodeType() {
        return NodeType::METHOD_CALL_EXPRESSION;
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

    const TokenPtr& NewDeclaratorExpression::getNewToken() const {
        return _newToken;
    }

    const TypePtr& NewDeclaratorExpression::getType() const {
        return _type;
    }

    const ArgumentsPtr& NewDeclaratorExpression::getArguments() const {
        return _arguments;
    }

    AstNode::NodeType NewDeclaratorExpression::getNodeType() {
        return NodeType::NEW_DECLARATOR_EXPRESSION;
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

    const ExpressionPtr& SuffixExpression::getExpression() const {
        return _expression;
    }

    const TokenPtr& SuffixExpression::getSuffix() const {
        return _suffix;
    }

    AstNode::NodeType SuffixExpression::getNodeType() {
        return NodeType::SUFFIX_EXPRESSION;
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

    const TokenPtr& PrefixExpression::getPrefix() const {
        return _prefix;
    }

    const ExpressionPtr& PrefixExpression::getExpression() const {
        return _expression;
    }

    AstNode::NodeType PrefixExpression::getNodeType() {
        return NodeType::PREFIX_EXPRESSION;
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

    const ExpressionPtr& BopExpression::getLeftExpresion() const {
        return _leftExpresion;
    }

    const TokenPtr& BopExpression::getBop() const {
        return _bop;
    }

    const ExpressionPtr& BopExpression::getRightExpresion() const {
        return _rightExpresion;
    }

    AstNode::NodeType BopExpression::getNodeType() {
        return NodeType::BOP_EXPRESSION;
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
            _trueExpression  = eb_createExpression(ctx->expression(1));
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

    const ExpressionPtr& TernaryExpression::getLeftExpression() const {
        return _leftExpression;
    }

    const TokenPtr& TernaryExpression::getBop() const {
        return _bop;
    }

    const ExpressionPtr& TernaryExpression::getTrueExpression() const {
        return _trueExpression;
    }

    const TokenPtr& TernaryExpression::getColon() const {
        return _colon;
    }

    const ExpressionPtr& TernaryExpression::getFalseExpression() const {
        return _falseExpression;
    }

    AstNode::NodeType TernaryExpression::getNodeType() {
        return NodeType::TERNARY_EXPRESSION;
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

    const ExpressionListPtr& MatchExpressionCase::getExpressionList() const {
        return _expressionList;
    }

    const TokenPtr& MatchExpressionCase::getDefaultToken() const {
        return _defaultToken;
    }

    const TokenPtr& MatchExpressionCase::getDoubleArrowToken() const {
        return _doubleArrowToken;
    }

    const ExpressionPtr& MatchExpressionCase::getExpression() const {
        return _expression;
    }

    AstNode::NodeType MatchExpressionCase::getNodeType() {
        return NodeType::MATCH_EXPRESSION_CASE;
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

    const TokenPtr& MatchExpression::getMatchToken() const {
        return _matchToken;
    }

    const ParExpresionPtr& MatchExpression::getParExpresion() const {
        return _parExpresion;
    }

    const TokenPtr& MatchExpression::getLeftBra() const {
        return _leftBra;
    }

    const MatchExpressionCasePtrVec& MatchExpression::getMatchExpressionCases() const {
        return _matchExpressionCases;
    }

    const TokenPtrVec& MatchExpression::getCommas() const {
        return _commas;
    }

    const TokenPtr& MatchExpression::getRightBra() const {
        return _rightBra;
    }

    AstNode::NodeType MatchExpression::getNodeType() {
        return NodeType::MATCH_EXPRESSION;
    }

    ExpressionStatement::ExpressionStatement(ExpressionPtr expression, TokenPtr semicolon) : _expression(expression),
                                                                                             Statement(semicolon) {
    }

    ExpressionStatement::ExpressionStatement(MaikuroParser::StatementContext* ctx) : ExpressionStatement(
        eb_createExpression(ctx->statementExpression),
        Token::createToken(ctx->SEMI())
    ) {
    }

    TokenPtrVec ExpressionStatement::getTokens() {
        TokenPtrVec tokens = { _expression->getTokens() };

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int ExpressionStatement::getLine() {
        return _expression->getLine();
    }

    string ExpressionStatement::toString() {
        return Token::toString(getTokens());
    }

    AstNode::NodeType ExpressionStatement::getNodeType() {
        return NodeType::EXPRESSION_STATEMENT;
    }

    const ExpressionPtr& ExpressionStatement::getExpression() const {
        return _expression;
    }
}