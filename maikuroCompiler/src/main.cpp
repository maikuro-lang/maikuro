#include <sysexits.h>
#include <iostream>
#include <MaikuroAst.h>

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

void dumpNodes(MaikuroAst::Tree::AstTreePtr tree, std::string prefix = "") {
    auto source = tree->getHead()->toString();

    if (source.length() > 40) {
        source = "";
    }

//    std::cout << prefix << tree->getHead()->getNodeName() << " # " << source << std::endl;
    std::cout << prefix << tree->getHead()->getNodeName() << std::endl;
    for (auto child : tree->getChildren()) {
        dumpNodes(child, prefix + "  ");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return EX_NOINPUT;
    }

    std::string source = readFile(argv[1]);

    try {
        auto sourceFile = MaikuroAst::Parser::parse(source);

        auto tree = MaikuroAst::Tree::AstTreeBuilder::build(sourceFile);

        dumpNodes(tree);

//        std::cout << sourceFile->toString() << std::endl << std::endl << std::endl;
//        std::cout << MaikuroAst::Token::toString(sourceFile->getTokens()) << std::endl << std::endl << std::endl;
    }
    catch (const char* err) {
        std::cerr << err << std::endl;
    }

    return 0;
}
