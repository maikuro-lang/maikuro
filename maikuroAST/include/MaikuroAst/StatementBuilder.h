#pragma once

#include "common.h"
#include "Statement.h"
#include "Utils.h"
#include "ExpressionBuilder.h"

namespace MaikuroAst {
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    StatementPtr sb_createStatement(MaikuroParser::StatementContext* ctx);

    StatementPtrVec sb_createStatement(vector<MaikuroParser::StatementContext*> ctx);
}