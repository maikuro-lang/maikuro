#pragma once

#include "common.h"
#include "Statement.h"
#include "Expression.h"
#include "Block.h"
#include "Argument.h"
#include "AstNode.h"
#include "Literals.h"
#include "Token.h"
#include "Variable.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class TokenExpressionStatement : public Statement {
     public:
        TokenExpressionStatement(TokenPtr token, ExpressionPtr expression, TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        const TokenPtr& getToken() const;

        NodeType getNodeType() override;

        const ExpressionPtr& getExpression() const;

     private:
        TokenPtr      _token;
        ExpressionPtr _expression;
    };

    class ReturnStatement : public TokenExpressionStatement {
     public:
        ReturnStatement(const TokenPtr& token, const ExpressionPtr& expression, const TokenPtr& semicolon);

        explicit ReturnStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<ReturnStatement> ReturnStatementPtr;

    class ThrowStatement : public TokenExpressionStatement {
     public:
        ThrowStatement(const TokenPtr& token, const ExpressionPtr& expression, const TokenPtr& semicolon);

        explicit ThrowStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<ThrowStatement> ThrowStatementPtr;

    class TokenNumberLiteralStatement : public Statement {
     public:
        TokenNumberLiteralStatement(TokenPtr token, NumberLiteralPtr numberLiteral, TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        const TokenPtr& getToken() const;

        NodeType getNodeType() override;

        const NumberLiteralPtr& getNumberLiteral() const;

     private:
        TokenPtr         _token;
        NumberLiteralPtr _numberLiteral;
    };

    class BreakStatement : public TokenNumberLiteralStatement {
     public:
        BreakStatement(const TokenPtr& token, const NumberLiteralPtr& numberLiteral, const TokenPtr& semicolon);

        explicit BreakStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<BreakStatement> BreakStatementPtr;

    class ContinueStatement : public TokenNumberLiteralStatement {
     public:
        ContinueStatement(const TokenPtr& token, const NumberLiteralPtr& numberLiteral, const TokenPtr& semicolon);

        explicit ContinueStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<ContinueStatement> ContinueStatementPtr;

    class IfStatement : public Statement {
     public:
        IfStatement(
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const StatementPtr& statement,
            const TokenPtr& elseToken,
            const StatementPtr& elseStatement
        );

        explicit IfStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getToken() const;

        const ParExpresionPtr& getExpresion() const;

        const StatementPtr& getStatement() const;

        const TokenPtr& getElseToken() const;

        const StatementPtr& getElseStatement() const;

     private:
        TokenPtr        _token;
        ParExpresionPtr _expresion;
        StatementPtr    _statement;
        TokenPtr        _elseToken;
        StatementPtr    _elseStatement;
    };

    typedef shared_ptr<IfStatement> IfStatementPtr;

    class UnlessStatement : public IfStatement {
     public:
        UnlessStatement(
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const StatementPtr& statement,
            const TokenPtr& elseToken,
            const StatementPtr& elseStatement
        );

        explicit UnlessStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<UnlessStatement> UnlessStatementPtr;

    class WhileStatement : public Statement {
     public:
        WhileStatement(
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const BlockPtr& block
        );

        explicit WhileStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getToken() const;

        const ParExpresionPtr& getExpresion() const;

        const BlockPtr& getBlock() const;

     protected:
        TokenPtr        _token;
        ParExpresionPtr _expresion;
        BlockPtr        _block;
    };

    typedef shared_ptr<WhileStatement> WhileStatementPtr;

    class UntilStatement : public WhileStatement {
     public:
        UntilStatement(const TokenPtr& token, const ParExpresionPtr& expresion, const BlockPtr& block);

        explicit UntilStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<UntilStatement> UntilStatementPtr;

    class LoopStatement : public WhileStatement {
     public:
        LoopStatement(const TokenPtr& token, const ParExpresionPtr& expresion, const BlockPtr& block);

        explicit LoopStatement(MaikuroParser::StatementContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<LoopStatement> LoopStatementPtr;

    class DoWhileStatement : public WhileStatement {
     public:
        DoWhileStatement(
            const TokenPtr& doToken,
            const BlockPtr& block,
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const TokenPtr& semicolon
        );

        explicit DoWhileStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getDoToken() const;

     private:
        TokenPtr _doToken;
    };

    typedef shared_ptr<DoWhileStatement> DoWhileStatementPtr;

    class ForControl : public AstNode {
     public:
        ForControl(
            const VariableDeclarationPtr& variableDeclaration,
            const ExpressionListPtr& expressionList,
            const ExpressionPtr& expression,
            const ExpressionListPtr& updateExpressionList,
            const TokenPtrVec& semicolons
        );

        explicit ForControl(MaikuroParser::ForControlContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const VariableDeclarationPtr& getVariableDeclaration() const;

        const ExpressionListPtr& getExpressionList() const;

        const ExpressionPtr& getExpression() const;

        const ExpressionListPtr& getUpdateExpressionList() const;

        const TokenPtrVec& getSemicolons() const;

     private:
        VariableDeclarationPtr _variableDeclaration;
        ExpressionListPtr      _expressionList;
        ExpressionPtr          _expression;
        ExpressionListPtr      _updateExpressionList;
        TokenPtrVec            _semicolons;
    };

    typedef shared_ptr<ForControl> ForControlPtr;

    class ForStatement : public Statement {
     public:
        ForStatement(
            const TokenPtr& forToken,
            const TokenPtr& leftPar,
            const ForControlPtr& control,
            const TokenPtr& rightPar,
            const StatementPtr& statement
        );

        explicit ForStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getForToken() const;

        const TokenPtr& getLeftPar() const;

        const ForControlPtr& getControl() const;

        const TokenPtr& getRightPar() const;

        const StatementPtr& getStatement() const;

     private:
        TokenPtr      _forToken;
        TokenPtr      _leftPar;
        ForControlPtr _control;
        TokenPtr      _rightPar;
        StatementPtr  _statement;
    };

    typedef shared_ptr<ForStatement> ForStatementPtr;

    class ForeachControl : public AstNode {
     public:
        ForeachControl(
            const ExpressionPtr& expression,
            const TokenPtr& asToken,
            const IdentifierPtrVec& identifiers,
            const TokenPtr& doubleArrow
        );

        explicit ForeachControl(MaikuroParser::ForeachControlContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const ExpressionPtr& getExpression() const;

        const TokenPtr& getAsToken() const;

        const IdentifierPtrVec& getIdentifiers() const;

        const TokenPtr& getDoubleArrow() const;

     private:
        ExpressionPtr    _expression;
        TokenPtr         _asToken;
        IdentifierPtrVec _identifiers;
        TokenPtr         _doubleArrow;
    };

    typedef shared_ptr<ForeachControl> ForeachControlPtr;

    class ForeachStatement : public Statement {
     public:
        ForeachStatement(
            const TokenPtr& foreachToken,
            const TokenPtr& leftPar,
            const ForeachControlPtr& control,
            const TokenPtr& rightPar,
            const StatementPtr& statement
        );

        explicit ForeachStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getForeachToken() const;

        const TokenPtr& getLeftPar() const;

        const ForeachControlPtr& getControl() const;

        const TokenPtr& getRightPar() const;

        const StatementPtr& getStatement() const;

     private:
        TokenPtr          _foreachToken;
        TokenPtr          _leftPar;
        ForeachControlPtr _control;
        TokenPtr          _rightPar;
        StatementPtr      _statement;
    };

    typedef shared_ptr<ForeachStatement> ForeachStatementPtr;

    class CatchClause : public AstNode {
     public:
        CatchClause(
            const TokenPtr& catchToken,
            const TokenPtr& leftPar,
            const TypeIdentifierPtrVec& typeIdentifiers,
            const TokenPtrVec& pipes,
            const IdentifierPtr& identifier,
            const TokenPtr& rightPar,
            const BlockPtr& block
        );

        explicit CatchClause(MaikuroParser::CatchClauseContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getCatchToken() const;

        const TokenPtr& getLeftPar() const;

        const TypeIdentifierPtrVec& getTypeIdentifiers() const;

        const TokenPtrVec& getPipes() const;

        const IdentifierPtr& getIdentifier() const;

        const TokenPtr& getRightPar() const;

        const BlockPtr& getBlock() const;

     private:
        TokenPtr             _catchToken;
        TokenPtr             _leftPar;
        TypeIdentifierPtrVec _typeIdentifiers;
        TokenPtrVec          _pipes;
        IdentifierPtr        _identifier;
        TokenPtr             _rightPar;
        BlockPtr             _block;
    };

    typedef shared_ptr<CatchClause> CatchClausePtr;
    typedef vector<CatchClausePtr>  CatchClausePtrVec;

    class FinallyBlock : public AstNode {
     public:
        FinallyBlock(const TokenPtr& finallyToken, const BlockPtr& block);

        explicit FinallyBlock(MaikuroParser::FinallyBlockContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getFinallyToken() const;

        const BlockPtr& getBlock() const;

     private:
        TokenPtr _finallyToken;
        BlockPtr _block;
    };

    typedef shared_ptr<FinallyBlock> FinallyBlockPtr;
    typedef vector<FinallyBlockPtr>  FinallyBlockPtrVec;

    class TryStatement : public Statement {
     public:
        TryStatement(
            const TokenPtr& tryToken,
            const BlockPtr& block,
            const CatchClausePtrVec& catches,
            const FinallyBlockPtr& finallyBlock
        );

        explicit TryStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getTryToken() const;

        const BlockPtr& getBlock() const;

        const CatchClausePtrVec& getCatches() const;

        const FinallyBlockPtr& getFinallyBlock() const;

     private:
        TokenPtr          _tryToken;
        BlockPtr          _block;
        CatchClausePtrVec _catches;
        FinallyBlockPtr   _finallyBlock;
    };

    typedef shared_ptr<TryStatement> TryStatementPtr;

    class SwitchLabel : public AstNode {
     public:
        SwitchLabel(
            const TokenPtr& caseToken,
            const TokenPtr& defaultToken,
            const ExpressionPtr& expression,
            const IdentifierPtr& identifier,
            const TokenPtr& colon
        );

        explicit SwitchLabel(MaikuroParser::SwitchLabelContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getCaseToken() const;

        const TokenPtr& getDefaultToken() const;

        const ExpressionPtr& getExpression() const;

        const IdentifierPtr& getIdentifier() const;

        const TokenPtr& getColon() const;

     private:
        TokenPtr      _caseToken;
        TokenPtr      _defaultToken;
        ExpressionPtr _expression;
        IdentifierPtr _identifier;
        TokenPtr      _colon;
    };

    typedef shared_ptr<SwitchLabel> SwitchLabelPtr;
    typedef vector<SwitchLabelPtr>  SwitchLabelPtrVec;

    class SwitchBlockStatementGroup : public AstNode {
     public:
        SwitchBlockStatementGroup(const SwitchLabelPtrVec& switchLabels, const StatementPtrVec& statements);

        explicit SwitchBlockStatementGroup(MaikuroParser::SwitchBlockStatementGroupContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const SwitchLabelPtrVec& getSwitchLabels() const;

        const StatementPtrVec& getStatements() const;

     private:
        SwitchLabelPtrVec _switchLabels;
        StatementPtrVec   _statements;
    };

    typedef shared_ptr<SwitchBlockStatementGroup> SwitchBlockStatementGroupPtr;
    typedef vector<SwitchBlockStatementGroupPtr>  SwitchBlockStatementGroupPtrVec;

    class SwitchStatement : public Statement {
     public:
        SwitchStatement(
            const TokenPtr& switchToken,
            const ParExpresionPtr& expresion,
            const TokenPtr& leftBra,
            const SwitchBlockStatementGroupPtrVec& switchBlockStatementGroups,
            const SwitchLabelPtrVec& switchLabels,
            const TokenPtr& rightBra
        );

        explicit SwitchStatement(MaikuroParser::StatementContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const TokenPtr& getSwitchToken() const;

        const ParExpresionPtr& getExpresion() const;

        const TokenPtr& getLeftBra() const;

        const SwitchBlockStatementGroupPtrVec& getSwitchBlockStatementGroups() const;

        const SwitchLabelPtrVec& getSwitchLabels() const;

        const TokenPtr& getRightBra() const;

     private:
        TokenPtr                        _switchToken;
        ParExpresionPtr                 _expresion;
        TokenPtr                        _leftBra;
        SwitchBlockStatementGroupPtrVec _switchBlockStatementGroups;
        SwitchLabelPtrVec               _switchLabels;
        TokenPtr                        _rightBra;
    };

    typedef shared_ptr<SwitchStatement> SwitchStatementPtr;
}

