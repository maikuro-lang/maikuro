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
    class TokenExpressionStatement : public MaikuroAst::Statement {
     public:
        TokenExpressionStatement(TokenPtr token, ExpressionPtr expression, TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr                  _token;
        ExpressionPtr _expression;
    };

    class ReturnStatement : public TokenExpressionStatement {
     public:
        ReturnStatement(const TokenPtr& token, const ExpressionPtr& expression, const TokenPtr& semicolon);

        explicit ReturnStatement(MaikuroParser::StatementContext* ctx);
    };

    class ThrowStatement : public TokenExpressionStatement {
     public:
        ThrowStatement(const TokenPtr& token, const ExpressionPtr& expression, const TokenPtr& semicolon);

        explicit ThrowStatement(MaikuroParser::StatementContext* ctx);
    };

    class TokenNumberLiteralStatement : public MaikuroAst::Statement {
     public:
        TokenNumberLiteralStatement(TokenPtr token, NumberLiteralPtr numberLiteral, TokenPtr semicolon);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr                     _token;
        NumberLiteralPtr _numberLiteral;
    };

    class BreakStatement : public TokenNumberLiteralStatement {
     public:
        BreakStatement(const TokenPtr& token, const NumberLiteralPtr& numberLiteral, const TokenPtr& semicolon);

        explicit BreakStatement(MaikuroParser::StatementContext* ctx);
    };

    class ContinueStatement : public TokenNumberLiteralStatement {
     public:
        ContinueStatement(const TokenPtr& token, const NumberLiteralPtr& numberLiteral, const TokenPtr& semicolon);

        explicit ContinueStatement(MaikuroParser::StatementContext* ctx);
    };

    class IfStatement : public MaikuroAst::Statement {
     public:
        IfStatement(
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const StatementPtr& statement,
            const TokenPtr& elseToken,
            const StatementPtr& elseStatement
        );

        explicit IfStatement(MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr                    _token;
        ParExpresionPtr _expresion;
        StatementPtr    _statement;
        TokenPtr                    _elseToken;
        StatementPtr    _elseStatement;
    };

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
    };

    class WhileStatement : public MaikuroAst::Statement {
     public:
        WhileStatement(
            const TokenPtr& token,
            const ParExpresionPtr& expresion,
            const BlockPtr& block
        );

        explicit WhileStatement(MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     protected:
        TokenPtr                    _token;
        ParExpresionPtr _expresion;
        BlockPtr        _block;
    };

    class UntilStatement : public WhileStatement {
     public:
        UntilStatement(const TokenPtr& token, const ParExpresionPtr& expresion, const BlockPtr& block);

        explicit UntilStatement(MaikuroParser::StatementContext* ctx);
    };

    class LoopStatement : public WhileStatement {
     public:
        LoopStatement(const TokenPtr& token, const ParExpresionPtr& expresion, const BlockPtr& block);

        explicit LoopStatement(MaikuroParser::StatementContext* ctx);
    };

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

        TokenPtrVec getTokens() override;

        int getLine() override;

     private:
        TokenPtr _doToken;
    };

    class ForControl : public MaikuroAst::AstNode {
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

        TokenPtrVec getTokens() override;

        string toString() override;

     private:
        VariableDeclarationPtr        _variableDeclaration;
        ExpressionListPtr _expressionList;
        ExpressionPtr     _expression;
        ExpressionListPtr _updateExpressionList;
        TokenPtrVec                   _semicolons;
    };

    typedef shared_ptr<ForControl>                ForControlPtr;

    class ForStatement : public MaikuroAst::Statement {
     public:
        ForStatement(
            const TokenPtr& forToken,
            const TokenPtr& leftPar,
            const ForControlPtr& control,
            const TokenPtr& rightPar,
            const StatementPtr& statement
        );

        explicit ForStatement(MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr      _forToken;
        TokenPtr      _leftPar;
        ForControlPtr _control;
        TokenPtr                 _rightPar;
        StatementPtr _statement;
    };

    class ForeachControl : public MaikuroAst::AstNode {
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

     private:
        ExpressionPtr _expression;
        TokenPtr                     _asToken;
        IdentifierPtrVec _identifiers;
        TokenPtr                     _doubleArrow;
    };

    typedef shared_ptr<ForeachControl>            ForeachControlPtr;

    class ForeachStatement : public MaikuroAst::Statement {
     public:
        ForeachStatement(
            const TokenPtr& foreachToken,
            const TokenPtr& leftPar,
            const ForeachControlPtr& control,
            const TokenPtr& rightPar,
            const StatementPtr& statement
        );

        explicit ForeachStatement(MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr          _foreachToken;
        TokenPtr          _leftPar;
        ForeachControlPtr _control;
        TokenPtr                 _rightPar;
        StatementPtr _statement;
    };

    class CatchClause : public MaikuroAst::AstNode {
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

     private:
        TokenPtr             _catchToken;
        TokenPtr                         _leftPar;
        TypeIdentifierPtrVec _typeIdentifiers;
        TokenPtrVec                      _pipes;
        IdentifierPtr        _identifier;
        TokenPtr                         _rightPar;
        BlockPtr _block;
    };

    typedef shared_ptr<CatchClause>               CatchClausePtr;
    typedef vector<CatchClausePtr>                CatchClausePtrVec;

    class FinallyBlock : public MaikuroAst::AstNode {
     public:
        FinallyBlock(const TokenPtr& finallyToken, const BlockPtr& block);

        explicit FinallyBlock(MaikuroParser::FinallyBlockContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        TokenPtr             _finallyToken;
        BlockPtr _block;
    };

    typedef shared_ptr<FinallyBlock>              FinallyBlockPtr;
    typedef vector<FinallyBlockPtr>               FinallyBlockPtrVec;

    class TryStatement : public MaikuroAst::Statement {
     public:
        TryStatement(
            const TokenPtr& tryToken,
            const BlockPtr& block,
            const CatchClausePtrVec& catches,
            const FinallyBlockPtr& finallyBlock
        );

        explicit TryStatement(MaikuroParser::StatementContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr             _tryToken;
        BlockPtr _block;
        CatchClausePtrVec    _catches;
        FinallyBlockPtr   _finallyBlock;
    };

    class SwitchLabel : public MaikuroAst::AstNode {
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

     private:
        TokenPtr      _caseToken;
        TokenPtr                  _defaultToken;
        ExpressionPtr _expression;
        IdentifierPtr _identifier;
        TokenPtr                  _colon;
    };

    typedef shared_ptr<SwitchLabel>               SwitchLabelPtr;
    typedef vector<SwitchLabelPtr>                SwitchLabelPtrVec;

    class SwitchBlockStatementGroup : public MaikuroAst::AstNode {
     public:
        SwitchBlockStatementGroup(const SwitchLabelPtrVec& switchLabels, const StatementPtrVec& statements);

        explicit SwitchBlockStatementGroup(MaikuroParser::SwitchBlockStatementGroupContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

     private:
        SwitchLabelPtrVec           _switchLabels;
        StatementPtrVec _statements;
    };

    typedef shared_ptr<SwitchBlockStatementGroup> SwitchBlockStatementGroupPtr;
    typedef vector<SwitchBlockStatementGroupPtr>  SwitchBlockStatementGroupPtrVec;

    class SwitchStatement : public MaikuroAst::Statement {
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

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        TokenPtr                    _switchToken;
        ParExpresionPtr _expresion;
        TokenPtr                    _leftBra;
        SwitchBlockStatementGroupPtrVec _switchBlockStatementGroups;
        SwitchLabelPtrVec               _switchLabels;
        TokenPtr                        _rightBra;
    };
}

