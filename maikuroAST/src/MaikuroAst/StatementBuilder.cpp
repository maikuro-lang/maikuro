#include "MaikuroAst/StatementBuilder.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Alias.h"
#include "MaikuroAst/Function.h"
#include "MaikuroAst/Variable.h"
#include "MaikuroAst/Class.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Statements.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Statement.h"

namespace MaikuroAst {
    StatementPtr sb_createStatement(MaikuroParser::StatementContext* ctx) {
        if (ctx->blockLabel) {
            return Utils::create<MaikuroAst::Block>(ctx->blockLabel);
        }

        if (ctx->IF()) {
            return Utils::create<IfStatement>(ctx);
        }

        if (ctx->UNLESS()) {
            return Utils::create<UnlessStatement>(ctx);
        }

        if (ctx->FOR()) {
            return Utils::create<ForStatement>(ctx);
        }

        if (ctx->FOREACH()) {
            return Utils::create<ForeachStatement>(ctx);
        }

        if (ctx->LOOP()) {
            return Utils::create<LoopStatement>(ctx);
        }

        if (ctx->UNTIL()) {
            return Utils::create<UntilStatement>(ctx);
        }

        if (ctx->WHILE() && !ctx->DO()) {
            return Utils::create<WhileStatement>(ctx);
        }

        if (ctx->DO()) {
            return Utils::create<DoWhileStatement>(ctx);
        }

        if (ctx->TRY()) {
            return Utils::create<TryStatement>(ctx);
        }

        if (ctx->SWITCH()) {
            return Utils::create<SwitchStatement>(ctx);
        }

        if (ctx->RETURN()) {
            return Utils::create<ReturnStatement>(ctx);
        }

        if (ctx->THROW()) {
            return Utils::create<ThrowStatement>(ctx);
        }

        if (ctx->BREAK()) {
            return Utils::create<BreakStatement>(ctx);
        }

        if (ctx->CONTINUE()) {
            return Utils::create<ContinueStatement>(ctx);
        }

        if (ctx->statementExpression) {
            return Utils::create<ExpressionStatement>(ctx);
        }

        if (ctx->variableDeclaration()) {
            return Utils::create<VariableDeclaration>(ctx->variableDeclaration());
        }

        if (ctx->classDeclaration()) {
            return Utils::create<MaikuroAst::ClassDeclaration>(ctx->classDeclaration());
        }

        if (ctx->functionDeclaration()) {
            return Utils::create<MaikuroAst::FunctionDeclaration>(ctx->functionDeclaration());
        }

        if (ctx->aliasDeclaration()) {
            return Utils::create<MaikuroAst::AliasDeclaration>(ctx->aliasDeclaration());
        }

        return nullptr;
    }

    StatementPtrVec sb_createStatement(vector<MaikuroParser::StatementContext*> ctx) {
        StatementPtrVec statements;

        for (auto statement : ctx) {
            statements.push_back(sb_createStatement(statement));
        }

        return statements;
    }
}