#include "MaikuroAst/Variable.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Expression.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"

namespace MaikuroAst {

    VariableName::VariableName(TokenPtr atSign, IdentifierPtr identifier) : _atSign(
        atSign
    ), _identifier(identifier) {
    }

    VariableName::VariableName(MaikuroParser::VariableNameContext* ctx) : VariableName(
        Token::createToken(ctx->AT()),
        Utils::create<Identifier>(ctx->IDENTIFIER())) {
    }

    int VariableName::getLine() {
        return _identifier->getLine();
    }

    string VariableName::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec VariableName::getTokens() {
        TokenPtrVec tokens;

        if (_atSign) {
            tokens.push_back(_atSign);
        }

        Token::mergeTokens(&tokens, _identifier->getTokens());

        return tokens;
    }

    const TokenPtr& VariableName::getAtSign() const {
        return _atSign;
    }

    const IdentifierPtr& VariableName::getIdentifier() const {
        return _identifier;
    }

    AstNode::NodeType VariableName::getNodeType() {
        return NodeType::VARIABLE_NAME;
    }

    VariableNameDeclaration::VariableNameDeclaration(
        TypeDeclarationPtr typeDeclaration,
        VariableNamePtr variableName
    ) : _typeDeclaration(
        typeDeclaration
    ), _variableName(variableName) {
    }

    VariableNameDeclaration::VariableNameDeclaration(MaikuroParser::VariableDeclarationNameContext* ctx)
        : VariableNameDeclaration(
        ctx->typeDeclaration()
        ? Utils::create<TypeDeclaration>(ctx->typeDeclaration())
        : nullptr,
        Utils::create<VariableName>(ctx->variableName())
    ) {
    }

    int VariableNameDeclaration::getLine() {
        return _variableName->getLine();
    }

    string VariableNameDeclaration::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec VariableNameDeclaration::getTokens() {
        TokenPtrVec tokens;

        if (_typeDeclaration) {
            Token::mergeTokens(&tokens, _typeDeclaration->getTokens());
        }

        Token::mergeTokens(&tokens, _variableName->getTokens());

        return tokens;
    }

    const TypeDeclarationPtr& VariableNameDeclaration::getTypeDeclaration() const {
        return _typeDeclaration;
    }

    const VariableNamePtr& VariableNameDeclaration::getVariableName() const {
        return _variableName;
    }

    AstNode::NodeType VariableNameDeclaration::getNodeType() {
        return NodeType::VARIABLE_NAME_DECLARATION;
    }

    VariableDeclarationExpression::VariableDeclarationExpression(
        TokenPtr semicolon,
        TokenPtr assign,
        ExpressionPtrVec expressions,
        TokenPtrVec commas
    )
        : _semicolon(semicolon), _assign(assign), _expressions(expressions), _commas(commas) {
    }

    VariableDeclarationExpression::VariableDeclarationExpression(MaikuroParser::VariableDeclarationExpressionContext* ctx)
        : VariableDeclarationExpression(
        Token::createToken(ctx->SEMI()),
        Token::createToken(ctx->ASSIGN()),
        eb_createExpressions(ctx->expression()),
        Token::createTokens(ctx->COMMA())
    ) {
    }

    int VariableDeclarationExpression::getLine() {
        return _semicolon->getLine();
    }

    string VariableDeclarationExpression::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec VariableDeclarationExpression::getTokens() {
        TokenPtrVec tokens;

        if (_assign) {
            tokens.push_back(_assign);
        }

        int i = 0;
        for (const auto& expression : _expressions) {
            Token::mergeTokens(&tokens, expression->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        return tokens;
    }

    const TokenPtr& VariableDeclarationExpression::getSemicolon() const {
        return _semicolon;
    }

    const TokenPtr& VariableDeclarationExpression::getAssign() const {
        return _assign;
    }

    const ExpressionPtrVec& VariableDeclarationExpression::getExpressions() const {
        return _expressions;
    }

    const TokenPtrVec& VariableDeclarationExpression::getCommas() const {
        return _commas;
    }

    AstNode::NodeType VariableDeclarationExpression::getNodeType() {
        return NodeType::VARIABLE_DECLARATION_EXPRESSION;
    }

    VariableDeclaration::VariableDeclaration(
        AnnotationsPtrVec annotations,
        TokenPtr var,
        VariableNameDeclarationPtrVec variableNames,
        TokenPtrVec separators,
        VariableDeclarationExpressionPtr expressions,
        TokenPtr semicolon
    )
        : _annotations(annotations),
          _var(var),
          _variableNames(variableNames),
          _separators(separators),
          _expressions(expressions),
          Statement(semicolon) {
    }

    VariableDeclaration::VariableDeclaration(MaikuroParser::VariableDeclarationContext* ctx)
        : VariableDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        Token::createToken(ctx->VAR()),
        Utils::create<VariableNameDeclaration>(ctx->variableDeclarationName()),
        Token::createTokens(ctx->var_sep),
        Utils::create<VariableDeclarationExpression>(ctx->variableDeclarationExpression()),
        Token::createToken(ctx->variableDeclarationExpression()->SEMI())
    ) {
    }

    TokenPtrVec VariableDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        tokens.push_back(_var);

        int i = 0;
        for (const auto& variableName : _variableNames) {
            Token::mergeTokens(&tokens, variableName->getTokens());

            if (_separators.size() > i) {
                tokens.push_back(_separators[i++]);
            }
        }

        Token::mergeTokens(&tokens, _expressions->getTokens());
        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int VariableDeclaration::getLine() {
        return _var->getLine();
    }

    string VariableDeclaration::toString() {
        return Token::toString(getTokens());
    }

    const AnnotationsPtrVec& VariableDeclaration::getAnnotations() const {
        return _annotations;
    }

    const TokenPtr& VariableDeclaration::getVar() const {
        return _var;
    }

    const VariableNameDeclarationPtrVec& VariableDeclaration::getVariableNames() const {
        return _variableNames;
    }

    const TokenPtrVec& VariableDeclaration::getSeparators() const {
        return _separators;
    }

    const VariableDeclarationExpressionPtr& VariableDeclaration::getExpressions() const {
        return _expressions;
    }

    AstNode::NodeType VariableDeclaration::getNodeType() {
        return NodeType::VARIABLE_DECLARATION;
    }
}