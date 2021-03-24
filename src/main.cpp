#include <iostream>
#include <antlr4-runtime.h>
#include "MaikuroLexer.h"
#include "MaikuroParser.h"
#include "MaikuroParserBaseListener.h"
#include <sysexits.h>

using namespace antlr4;
using namespace MaikuroGrammar;

class Listener : public MaikuroParserBaseListener {
public:
    void enterImportDeclaration(MaikuroParser::ImportDeclarationContext *context) override {
        bool a = true;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EX_NOINPUT;
    }

    std::ifstream source;
    source.open(argv[1]);

    ANTLRInputStream input(source);
    MaikuroLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    // Only if you want to list the tokens
     for (auto token : tokens.getTokens()) {
      std::cout << lexer.getTokenNames()[token->getType()] << " " << token->toString() << std::endl;
     }

    MaikuroParser parser(&tokens);

    tree::ParseTree *tree = parser.sourceFile();
    Listener listener;
//    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    std::cout << tree->toStringTree(true) << std::endl;
    return 0;
}
