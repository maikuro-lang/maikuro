#pragma once

#include "MaikuroAst/SourceFile.h"

namespace MaikuroAst {

    class Parser {
     public:
        static SourceFilePtr parse(const string& sourceCode);
    };

}