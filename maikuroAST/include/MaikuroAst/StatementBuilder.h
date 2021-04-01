#pragma once

#include "common.h"
#include "Statement.h"
#include "Utils.h"
#include "ExpressionBuilder.h"

namespace MaikuroAst {
    MaikuroAst::StatementPtr sb_createStatement(MaikuroParser::StatementContext* ctx);

    MaikuroAst::StatementPtrVec sb_createStatement(vector<MaikuroParser::StatementContext*> ctx);
}