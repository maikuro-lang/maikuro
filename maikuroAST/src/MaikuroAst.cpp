#include "MaikuroAst.h"
#include "MaikuroAst/Utils.h"

namespace MaikuroAst {
    using MaikuroGrammar::MaikuroParser;

    SourceFilePtr Parser::parse(const std::string& sourceCode) {
        antlr4::ANTLRInputStream input(sourceCode);

        MaikuroGrammar::MaikuroLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);

        MaikuroParser parser(&tokens);

        auto *sourceFileTree = parser.sourceFile();

        return Utils::create<SourceFile>(sourceFileTree);
    }
}