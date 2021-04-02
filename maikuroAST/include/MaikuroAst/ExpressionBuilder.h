#pragma once

#include "common.h"
#include "Expression.h"
#include "Argument.h"
#include "Utils.h"

namespace MaikuroAst {
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    ExpressionPtr eb_createExpression(MaikuroParser::ExpressionContext* ctx);

    ExpressionPtrVec eb_createExpressions(vector<MaikuroParser::ExpressionContext*> ctxs);
}