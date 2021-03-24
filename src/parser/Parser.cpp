#include <antlr4-runtime.h>
#include <MaikuroLexer.h>
#include <MaikuroParser.h>
#include "Parser.h"

using namespace MaikuroGrammar;

int Parser::parse(std::string &source) {
    antlr4::ANTLRInputStream input(source);

    MaikuroLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    MaikuroParser parser(&tokens);

    return 0;
}
