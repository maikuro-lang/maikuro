#include <sysexits.h>
#include <iostream>
#include "MaikuroAst.h"

std::string readFile(const char* path) {
    std::ifstream in(path);

    std::string content;
    in.seekg(0, std::ios::end);

    content.resize(in.tellg());

    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();

    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return EX_NOINPUT;
    }

    std::string source = readFile(argv[1]);

    try {
        auto sourceFile = MaikuroAst::Parser::parse(source);

        std::cout << sourceFile->toString() << std::endl << std::endl << std::endl;
        std::cout << MaikuroAst::Token::toString(sourceFile->getTokens()) << std::endl << std::endl << std::endl;
    }
    catch (const char* err) {
        std::cerr << err << std::endl;
    }

    return 0;
}
