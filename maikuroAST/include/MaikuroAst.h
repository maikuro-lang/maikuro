#pragma once

#include "MaikuroAst/common.h"
#include "MaikuroAst/Alias.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Argument.h"
#include "MaikuroAst/AstNode.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Class.h"
#include "MaikuroAst/Expression.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Function.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Package.h"
#include "MaikuroAst/SourceFile.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/StatementBuilder.h"
#include "MaikuroAst/Statements.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/Variable.h"
#include "MaikuroAst/Tree/AstTree.h"
#include "MaikuroAst/Tree/AstTreeBuilder.h"
#include "MaikuroAst/Tree/AstTreeVisitor.h"
#include "MaikuroAst/Tree/AstTreeBaseVisitor.h"

namespace MaikuroAst {

    class Parser {
     public:
        static SourceFilePtr parse(const string& sourceCode);
    };

}