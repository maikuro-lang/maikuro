#pragma once

#include "common.h"
#include "Expression.h"
#include "Argument.h"
#include "Utils.h"

namespace MaikuroAst {
    ExpressionPtr eb_createExpression(MaikuroParser::ExpressionContext* ctx);

    ExpressionPtrVec eb_createExpressions(vector<MaikuroParser::ExpressionContext*> ctxs);
}