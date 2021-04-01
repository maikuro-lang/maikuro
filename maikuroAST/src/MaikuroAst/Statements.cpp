#include "MaikuroAst/Statements.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/StatementBuilder.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Expression.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {

    TokenExpressionStatement::TokenExpressionStatement(
        TokenPtr token,
        ExpressionPtr expression,
        TokenPtr semicolon
    )
        : _token(token), _expression(expression), Statement(semicolon) {
    }

    TokenPtrVec TokenExpressionStatement::getTokens() {
        TokenPtrVec tokens = { _token };

        if (_expression) {
            Token::mergeTokens(&tokens, _expression->getTokens());
        }

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int TokenExpressionStatement::getLine() {
        return _token->getLine();
    }

    string TokenExpressionStatement::toString() {
        return Token::toString(getTokens());
    }

    ReturnStatement::ReturnStatement(
        const TokenPtr& token,
        const ExpressionPtr& expression,
        const TokenPtr& semicolon
    )
        : TokenExpressionStatement(token, expression, semicolon) {
    }

    ReturnStatement::ReturnStatement(MaikuroParser::StatementContext* ctx) : ReturnStatement(
        Token::createToken(ctx->RETURN()),
        ctx->expression() ? eb_createExpression(ctx->expression()) : nullptr,
        Token::createToken(ctx->SEMI())
    ) {
    }

    ThrowStatement::ThrowStatement(
        const TokenPtr& token,
        const ExpressionPtr& expression,
        const TokenPtr& semicolon
    )
        : TokenExpressionStatement(token, expression, semicolon) {
    }

    ThrowStatement::ThrowStatement(MaikuroParser::StatementContext* ctx) : ThrowStatement(
        Token::createToken(ctx->THROW()),
        eb_createExpression(ctx->expression()),
        Token::createToken(ctx->SEMI())
    ) {
    }

    TokenNumberLiteralStatement::TokenNumberLiteralStatement(
        TokenPtr token,
        NumberLiteralPtr numberLiteral,
        TokenPtr semicolon
    )
        : _token(token), _numberLiteral(numberLiteral), Statement(semicolon) {
    }

    TokenPtrVec TokenNumberLiteralStatement::getTokens() {
        TokenPtrVec tokens = { _token };

        if (_numberLiteral) {
            Token::mergeTokens(&tokens, _numberLiteral->getTokens());
        }

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int TokenNumberLiteralStatement::getLine() {
        return _token->getLine();
    }

    string TokenNumberLiteralStatement::toString() {
        return Token::toString(getTokens());
    }

    BreakStatement::BreakStatement(
        const TokenPtr& token,
        const NumberLiteralPtr& numberLiteral,
        const TokenPtr& semicolon
    )
        : TokenNumberLiteralStatement(token, numberLiteral, semicolon) {
    }

    BreakStatement::BreakStatement(MaikuroParser::StatementContext* ctx) : BreakStatement(
        Token::createToken(ctx->BREAK()),
        ctx->NUMBER_LITERAL() ? Utils::create<NumberLiteral>(ctx->NUMBER_LITERAL()) : nullptr,
        Token::createToken(ctx->SEMI())
    ) {
    }

    ContinueStatement::ContinueStatement(
        const TokenPtr& token,
        const NumberLiteralPtr& numberLiteral,
        const TokenPtr& semicolon
    )
        : TokenNumberLiteralStatement(token, numberLiteral, semicolon) {
    }

    ContinueStatement::ContinueStatement(MaikuroParser::StatementContext* ctx) : ContinueStatement(
        Token::createToken(ctx->CONTINUE()),
        ctx->NUMBER_LITERAL() ? Utils::create<NumberLiteral>(ctx->NUMBER_LITERAL()) : nullptr,
        Token::createToken(ctx->SEMI())
    ) {
    }

    IfStatement::IfStatement(
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const StatementPtr& statement,
        const TokenPtr& elseToken,
        const StatementPtr& elseStatement
    ) :
        _token(token),
        _expresion(expresion),
        _statement(statement),
        _elseToken(elseToken),
        _elseStatement(elseStatement),
        Statement(nullptr) {
    }

    IfStatement::IfStatement(MaikuroParser::StatementContext* ctx) : IfStatement(
        Token::createToken(ctx->IF()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        sb_createStatement(ctx->statement(0)),
        Token::createToken(ctx->ELSE()),
        ctx->statement().size() == 2 ? sb_createStatement(ctx->statement(1)) : nullptr
    ) {
    }

    TokenPtrVec IfStatement::getTokens() {
        TokenPtrVec tokens = { _token };

        Token::mergeTokens(&tokens, _expresion->getTokens());
        Token::mergeTokens(&tokens, _statement->getTokens());
        if (_elseToken) {
            tokens.push_back(_elseToken);

            Token::mergeTokens(&tokens, _elseStatement->getTokens());
        }

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int IfStatement::getLine() {
        return _token->getLine();
    }

    string IfStatement::toString() {
        return Token::toString(getTokens());
    }

    UnlessStatement::UnlessStatement(
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const StatementPtr& statement,
        const TokenPtr& elseToken,
        const StatementPtr& elseStatement
    ) : IfStatement(token, expresion, statement, elseToken, elseStatement) {
    }

    UnlessStatement::UnlessStatement(MaikuroParser::StatementContext* ctx) : IfStatement(
        Token::createToken(ctx->UNLESS()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        sb_createStatement(ctx->statement(0)),
        Token::createToken(ctx->ELSE()),
        ctx->statement().size() == 2 ? sb_createStatement(ctx->statement(1)) : nullptr
    ) {
    }

    WhileStatement::WhileStatement(
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const BlockPtr& block
    ) : _token(token), _expresion(expresion), _block(block), Statement(nullptr) {
    }

    WhileStatement::WhileStatement(MaikuroParser::StatementContext* ctx) : WhileStatement(
        Token::createToken(ctx->WHILE()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    TokenPtrVec WhileStatement::getTokens() {
        TokenPtrVec tokens = { _token };

        if (_expresion) {
            Token::mergeTokens(&tokens, _expresion->getTokens());
        }

        Token::mergeTokens(&tokens, _block->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int WhileStatement::getLine() {
        return _token->getLine();
    }

    string WhileStatement::toString() {
        return Token::toString(getTokens());
    }

    UntilStatement::UntilStatement(
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const BlockPtr& block
    )
        : WhileStatement(token, expresion, block) {
    }

    UntilStatement::UntilStatement(MaikuroParser::StatementContext* ctx) : WhileStatement(
        Token::createToken(ctx->UNTIL()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    LoopStatement::LoopStatement(
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const BlockPtr& block
    )
        : WhileStatement(token, expresion, block) {
    }

    LoopStatement::LoopStatement(MaikuroParser::StatementContext* ctx) : WhileStatement(
        Token::createToken(ctx->LOOP()),
        ctx->parExpression() ? Utils::create<ParExpresion>(ctx->parExpression()) : nullptr,
        Utils::create<Block>(ctx->block())
    ) {
    }

    DoWhileStatement::DoWhileStatement(
        const TokenPtr& doToken,
        const BlockPtr& block,
        const TokenPtr& token,
        const ParExpresionPtr& expresion,
        const TokenPtr& semicolon
    ) : _doToken(doToken), WhileStatement(token, expresion, block) {
        _semicolon = semicolon;
    }

    DoWhileStatement::DoWhileStatement(MaikuroParser::StatementContext* ctx) : DoWhileStatement(
        Token::createToken(ctx->DO()),
        Utils::create<Block>(ctx->block()),
        Token::createToken(ctx->WHILE()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        Token::createToken(ctx->SEMI())
    ) {
    }

    TokenPtrVec DoWhileStatement::getTokens() {
        TokenPtrVec tokens = { _doToken };

        Token::mergeTokens(&tokens, _block->getTokens());

        tokens.push_back(_token);
        Token::mergeTokens(&tokens, _expresion->getTokens());

        tokens.push_back(_semicolon);

        return tokens;
    }

    int DoWhileStatement::getLine() {
        return _doToken->getLine();
    }

    ForControl::ForControl(
        const VariableDeclarationPtr& variableDeclaration,
        const ExpressionListPtr& expressionList,
        const ExpressionPtr& expression,
        const ExpressionListPtr& updateExpressionList,
        const TokenPtrVec& semicolons
    )
        : _variableDeclaration(variableDeclaration),
          _expressionList(expressionList),
          _expression(expression),
          _updateExpressionList(updateExpressionList),
          _semicolons(semicolons) {
    }

    ForControl::ForControl(MaikuroParser::ForControlContext* ctx) : ForControl(
        nullptr,
        nullptr,
        ctx->expression() ? eb_createExpression(ctx->expression()) : nullptr,
        nullptr,
        Token::createTokens(ctx->SEMI())
    ) {
        if (ctx->variableDeclaration()) {
            _variableDeclaration = Utils::create<VariableDeclaration>(ctx->variableDeclaration());
        }

        if (ctx->expressionList().size() == 1) {
            if (!ctx->forUpdate) {
                _expressionList = Utils::create<ExpressionList>(ctx->expressionList(0));
            } else {
                _updateExpressionList = Utils::create<ExpressionList>(ctx->expressionList(0));
            }
        } else {
            _expressionList = Utils::create<ExpressionList>(ctx->expressionList(0));
            _updateExpressionList = Utils::create<ExpressionList>(ctx->expressionList(1));
        }
    }

    int ForControl::getLine() {
        return _semicolons[0]->getLine();
    }

    TokenPtrVec ForControl::getTokens() {
        TokenPtrVec tokens;

        if (_variableDeclaration) {
            Token::mergeTokens(&tokens, _variableDeclaration->getTokens());
        }

        if (_expressionList) {
            Token::mergeTokens(&tokens, _expressionList->getTokens());
        }

        tokens.push_back(_semicolons[0]);

        if (_expression) {
            Token::mergeTokens(&tokens, _expression->getTokens());
        }

        tokens.push_back(_semicolons[1]);

        if (_updateExpressionList) {
            Token::mergeTokens(&tokens, _updateExpressionList->getTokens());
        }

        return tokens;
    }

    string ForControl::toString() {
        return Token::toString(getTokens());
    }

    ForStatement::ForStatement(
        const TokenPtr& forToken,
        const TokenPtr& leftPar,
        const ForControlPtr& control,
        const TokenPtr& rightPar,
        const StatementPtr& statement
    )
        : _forToken(forToken),
          _leftPar(leftPar),
          _control(control),
          _rightPar(rightPar),
          _statement(statement),
          Statement(nullptr) {
    }

    ForStatement::ForStatement(MaikuroParser::StatementContext* ctx) : ForStatement(
        Token::createToken(ctx->FOR()),
        Token::createToken(ctx->LPAREN()),
        Utils::create<ForControl>(ctx->forControl()),
        Token::createToken(ctx->RPAREN()),
        sb_createStatement(ctx->statement(0))
    ) {
    }

    TokenPtrVec ForStatement::getTokens() {
        TokenPtrVec tokens = { _forToken, _leftPar };

        Token::mergeTokens(&tokens, _control->getTokens());

        tokens.push_back(_rightPar);

        Token::mergeTokens(&tokens, _statement->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int ForStatement::getLine() {
        return _forToken->getLine();
    }

    string ForStatement::toString() {
        return Token::toString(getTokens());
    }

    ForeachControl::ForeachControl(
        const ExpressionPtr& expression,
        const TokenPtr& asToken,
        const IdentifierPtrVec& identifiers,
        const TokenPtr& doubleArrow
    ) : _expression(expression), _asToken(asToken), _identifiers(identifiers), _doubleArrow(doubleArrow) {
    }

    ForeachControl::ForeachControl(MaikuroParser::ForeachControlContext* ctx) : ForeachControl(
        eb_createExpression(ctx->expression()),
        Token::createToken(ctx->AS()),
        Utils::create<Identifier>(ctx->IDENTIFIER()),
        Token::createToken(ctx->DOUBLE_ARROW())
    ) {
    }

    int ForeachControl::getLine() {
        return _expression->getLine();
    }

    string ForeachControl::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec ForeachControl::getTokens() {
        TokenPtrVec tokens = _expression->getTokens();

        tokens.push_back(_asToken);

        Token::mergeTokens(&tokens, _identifiers[0]->getTokens());

        if (_doubleArrow) {
            tokens.push_back(_doubleArrow);
            Token::mergeTokens(&tokens, _identifiers[1]->getTokens());
        }

        return tokens;
    }

    ForeachStatement::ForeachStatement(
        const TokenPtr& foreachToken,
        const TokenPtr& leftPar,
        const ForeachControlPtr& control,
        const TokenPtr& rightPar,
        const StatementPtr& statement
    )
        : _foreachToken(foreachToken),
          _leftPar(leftPar),
          _control(control),
          _rightPar(rightPar),
          _statement(statement),
          Statement(nullptr) {
    }

    ForeachStatement::ForeachStatement(MaikuroParser::StatementContext* ctx) : ForeachStatement(
        Token::createToken(ctx->FOREACH()),
        Token::createToken(ctx->LPAREN()),
        Utils::create<ForeachControl>(ctx->foreachControl()),
        Token::createToken(ctx->RPAREN()),
        sb_createStatement(ctx->statement(0))
    ) {

    }

    TokenPtrVec ForeachStatement::getTokens() {
        TokenPtrVec tokens = { _foreachToken, _leftPar };

        Token::mergeTokens(&tokens, _control->getTokens());

        tokens.push_back(_rightPar);

        Token::mergeTokens(&tokens, _statement->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int ForeachStatement::getLine() {
        return _foreachToken->getLine();
    }

    string ForeachStatement::toString() {
        return Token::toString(getTokens());
    }

    FinallyBlock::FinallyBlock(const TokenPtr& finallyToken, const BlockPtr& block)
        : _finallyToken(finallyToken), _block(block) {
    }

    FinallyBlock::FinallyBlock(MaikuroParser::FinallyBlockContext* ctx) : FinallyBlock(
        Token::createToken(ctx->FINALLY()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    int FinallyBlock::getLine() {
        return _finallyToken->getLine();
    }

    string FinallyBlock::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec FinallyBlock::getTokens() {
        TokenPtrVec tokens = { _finallyToken };

        Token::mergeTokens(&tokens, _block->getTokens());

        return tokens;
    }

    CatchClause::CatchClause(
        const TokenPtr& catchToken,
        const TokenPtr& leftPar,
        const TypeIdentifierPtrVec& typeIdentifiers,
        const TokenPtrVec& pipes,
        const IdentifierPtr& identifier,
        const TokenPtr& rightPar,
        const BlockPtr& block
    )
        : _catchToken(catchToken),
          _leftPar(leftPar),
          _typeIdentifiers(typeIdentifiers),
          _pipes(pipes),
          _identifier(identifier),
          _rightPar(rightPar),
          _block(block) {
    }

    CatchClause::CatchClause(MaikuroParser::CatchClauseContext* ctx) : CatchClause(
        Token::createToken(ctx->CATCH()),
        Token::createToken(ctx->LPAREN()),
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()),
        Token::createTokens(ctx->BITOR()),
        ctx->IDENTIFIER() ? Utils::create<Identifier>(ctx->IDENTIFIER()) : nullptr,
        Token::createToken(ctx->RPAREN()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    int CatchClause::getLine() {
        return _catchToken->getLine();
    }

    string CatchClause::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec CatchClause::getTokens() {
        TokenPtrVec tokens = { _catchToken, _leftPar };

        int i = 0;
        for (const auto& typeIdentifier : _typeIdentifiers) {
            Token::mergeTokens(&tokens, typeIdentifier->getTokens());

            if (_pipes.size() > i) {
                tokens.push_back(_pipes[i++]);
            }
        }

        if (_identifier) {
            Token::mergeTokens(&tokens, _identifier->getTokens());
        }

        tokens.push_back(_rightPar);

        Token::mergeTokens(&tokens, _block->getTokens());

        return tokens;
    }

    TryStatement::TryStatement(
        const TokenPtr& tryToken,
        const BlockPtr& block,
        const CatchClausePtrVec& catches,
        const FinallyBlockPtr& finallyBlock
    ) : _tryToken(tryToken), _block(block), _catches(catches), _finallyBlock(finallyBlock), Statement(nullptr) {
    }

    TokenPtrVec TryStatement::getTokens() {
        TokenPtrVec tokens = { _tryToken };

        Token::mergeTokens(&tokens, _block->getTokens());
        Token::mergeTokens(&tokens, Utils::getTokens<CatchClause>(_catches));
        Token::mergeTokens(&tokens, _finallyBlock->getTokens());

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int TryStatement::getLine() {
        return _tryToken->getLine();
    }

    string TryStatement::toString() {
        return Token::toString(getTokens());
    }

    TryStatement::TryStatement(MaikuroParser::StatementContext* ctx) : TryStatement(
        Token::createToken(ctx->TRY()),
        Utils::create<Block>(ctx->block()),
        Utils::create<CatchClause>(ctx->catchClause()),
        ctx->finallyBlock() ? Utils::create<FinallyBlock>(ctx->finallyBlock()) : nullptr
    ) {
    }

    SwitchLabel::SwitchLabel(
        const TokenPtr& caseToken,
        const TokenPtr& defaultToken,
        const ExpressionPtr& expression,
        const IdentifierPtr& identifier,
        const TokenPtr& colon
    )
        : _caseToken(caseToken),
          _defaultToken(defaultToken),
          _expression(expression),
          _identifier(identifier),
          _colon(colon) {
    }

    SwitchLabel::SwitchLabel(MaikuroParser::SwitchLabelContext* ctx) : SwitchLabel(
        ctx->CASE() ? Token::createToken(ctx->CASE()) : nullptr,
        ctx->DEFAULT() ? Token::createToken(ctx->DEFAULT()) : nullptr,
        ctx->expression() ? eb_createExpression(ctx->expression()) : nullptr,
        ctx->IDENTIFIER() ? Utils::create<Identifier>(ctx->IDENTIFIER()) : nullptr,
        Token::createToken(ctx->COLON())
    ) {
    }

    int SwitchLabel::getLine() {
        return _colon->getLine();
    }

    string SwitchLabel::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec SwitchLabel::getTokens() {
        TokenPtrVec tokens;

        if (_defaultToken) {
            tokens.push_back(_defaultToken);
        }

        if (_caseToken) {
            tokens.push_back(_caseToken);
        }

        if (_expression) {
            Token::mergeTokens(&tokens, _expression->getTokens());
        }

        if (_identifier) {
            Token::mergeTokens(&tokens, _identifier->getTokens());
        }

        tokens.push_back(_colon);

        return tokens;
    }

    SwitchBlockStatementGroup::SwitchBlockStatementGroup(
        const SwitchLabelPtrVec& switchLabels,
        const StatementPtrVec& statements
    ) : _switchLabels(switchLabels), _statements(statements) {
    }

    SwitchBlockStatementGroup::SwitchBlockStatementGroup(MaikuroParser::SwitchBlockStatementGroupContext* ctx)
        : SwitchBlockStatementGroup(
        Utils::create<SwitchLabel>(ctx->switchLabel()),
        sb_createStatement(ctx->statement())
    ) {
    }

    int SwitchBlockStatementGroup::getLine() {
        return _switchLabels[0]->getLine();
    }

    string SwitchBlockStatementGroup::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec SwitchBlockStatementGroup::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<SwitchLabel>(_switchLabels));
        Token::mergeTokens(&tokens, Utils::getTokens<Statement>(_statements));

        return tokens;
    }

    SwitchStatement::SwitchStatement(
        const TokenPtr& switchToken,
        const ParExpresionPtr& expresion,
        const TokenPtr& leftBra,
        const SwitchBlockStatementGroupPtrVec& switchBlockStatementGroups,
        const SwitchLabelPtrVec& switchLabels,
        const TokenPtr& rightBra
    )
        : _switchToken(switchToken),
          _expresion(expresion),
          _leftBra(leftBra),
          _switchBlockStatementGroups(switchBlockStatementGroups),
          _switchLabels(switchLabels),
          _rightBra(rightBra),
          Statement(nullptr) {
    }

    SwitchStatement::SwitchStatement(MaikuroParser::StatementContext* ctx) : SwitchStatement(
        Token::createToken(ctx->SWITCH()),
        Utils::create<ParExpresion>(ctx->parExpression()),
        Token::createToken(ctx->LBRACE()),
        Utils::create<SwitchBlockStatementGroup>(ctx->switchBlockStatementGroup()),
        Utils::create<SwitchLabel>(ctx->switchLabel()),
        Token::createToken(ctx->RBRACE())
    ) {
    }

    TokenPtrVec SwitchStatement::getTokens() {
        TokenPtrVec tokens = { _switchToken };

        Token::mergeTokens(&tokens, _expresion->getTokens());

        tokens.push_back(_leftBra);

        Token::mergeTokens(&tokens, Utils::getTokens<SwitchBlockStatementGroup>(_switchBlockStatementGroups));
        Token::mergeTokens(&tokens, Utils::getTokens<SwitchLabel>(_switchLabels));

        tokens.push_back(_rightBra);

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int SwitchStatement::getLine() {
        return _switchToken->getLine();
    }

    string SwitchStatement::toString() {
        return Token::toString(getTokens());
    }
}