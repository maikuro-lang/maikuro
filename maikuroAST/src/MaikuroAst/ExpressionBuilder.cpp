#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Argument.h"
#include "MaikuroAst/Expression.h"

namespace MaikuroAst {
    using MaikuroGrammar::MaikuroParser;

    ExpressionPtr eb_createExpression(MaikuroParser::ExpressionContext* ctx) {
        if (ctx->primary()) {
            return Utils::create<PrimaryExpression>(ctx->primary());
        }

        if (ctx->variableName()) {
            return Utils::create<VariableNameExpression>(ctx->variableName());
        }

        if (ctx->parExpression() && ctx->MATCH() == nullptr) {
            return Utils::create<ParExpresion>(ctx->parExpression());
        }

        if (ctx->dotExpression()) {
            return Utils::create<DotExpression>(ctx);
        }

        if (ctx->methodCall()) {
            return Utils::create<MethodCallExpression>(ctx);
        }

        if (ctx->newDeclarator()) {
            return Utils::create<NewDeclaratorExpression>(ctx->newDeclarator());
        }

        if (ctx->MATCH()) {
            return Utils::create<MatchExpression>(ctx);
        }

        if (ctx->suffix) {
            return Utils::create<SuffixExpression>(ctx);
        }

        if (ctx->prefix) {
            return Utils::create<SuffixExpression>(ctx);
        }

        if (ctx->COLON()) {
            return Utils::create<TernaryExpression>(ctx);
        }

        if (ctx->bop) {
            return Utils::create<BopExpression>(ctx);
        }

        return nullptr;
    }

    ExpressionPtrVec eb_createExpressions(std::vector<MaikuroParser::ExpressionContext*> ctxs) {
        ExpressionPtrVec expressions;

        for (auto ctx : ctxs) {
            expressions.push_back(eb_createExpression(ctx));
        }

        return expressions;
    }
}