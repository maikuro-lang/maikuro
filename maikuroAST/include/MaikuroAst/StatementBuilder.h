#pragma once

#include "common.h"
#include "Statement.h"
#include "Utils.h"
#include "ExpressionBuilder.h"

namespace MaikuroAst {

    StatementPtr sb_createStatement(MaikuroGrammar::MaikuroParser::StatementContext* ctx);

    StatementPtrVec sb_createStatement(std::vector<MaikuroGrammar::MaikuroParser::StatementContext*> ctx);
}