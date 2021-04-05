#pragma once

#include "common.h"
#include "Expression.h"
#include "Argument.h"
#include "Utils.h"

namespace MaikuroAst {
    ExpressionPtr eb_createExpression(MaikuroGrammar::MaikuroParser::ExpressionContext* ctx);

    ExpressionPtrVec eb_createExpressions(std::vector<MaikuroGrammar::MaikuroParser::ExpressionContext*> ctxs);
}