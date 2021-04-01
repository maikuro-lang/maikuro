#include "MaikuroAst.h"
#include "MaikuroAst/Utils.h"

namespace MaikuroAst {

    SourceFilePtr Parser::parse(const string& sourceCode) {
        antlr4::ANTLRInputStream input(sourceCode);

        MaikuroGrammar::MaikuroLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);

        MaikuroParser parser(&tokens);

        auto *sourceFileTree = parser.sourceFile();

        return Utils::create<SourceFile>(sourceFileTree);
    }
}