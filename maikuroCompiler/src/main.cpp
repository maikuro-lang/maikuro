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
std::string encode(std::string data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        switch(data[pos]) {
            case '&':  buffer.append("&amp;");       break;
            case '\"': buffer.append("&quot;");      break;
            case '\'': buffer.append("&apos;");      break;
            case '<':  buffer.append("&lt;");        break;
            case '>':  buffer.append("&gt;");        break;
            default:   buffer.append(&data[pos], 1); break;
        }
    }

    return buffer;
}


void generateAstDotNode(MaikuroAst::Tree::AstTreePtr tree, std::string *file, int *i, int parent = -1) {
    int current = *i;
    std::string node;
    if (tree->getHead()->getNodeType() == MaikuroAst::AstNode::NodeType::TOKEN) {
        node = "n" + std::to_string(*i) + " [label=< <B> " + tree->getHead()->getNodeName() + "</B><BR/><BR/> " + encode(tree->getHead()->toString()) +" >]\n";
    } else {
        node = "n" + std::to_string(*i) + " [label=< <B>" + tree->getHead()->getNodeName() + "</B> >]\n";
    }

    if (parent > -1) {
        node += "n" + std::to_string(parent) + "->n" + std::to_string(*i) + "\n";
    }

    file->append(node);

    for (auto child : tree->getChildren()) {
        *i = *i + 1;
        generateAstDotNode(child, file, i, current);
    }
}

std::string generateAstDot(MaikuroAst::Tree::AstTreePtr tree) {
    std::string file = "digraph AST{\nnode[shape=rectangle]\n";

    int i = 0;
    generateAstDotNode(tree, &file, &i);

    file += "}";

    return file;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return EX_NOINPUT;
    }

    std::string source = readFile(argv[1]);

    try {
        auto sourceFile = MaikuroAst::Parser::parse(source);

        auto tree = MaikuroAst::Tree::AstTreeBuilder::build(sourceFile);

        for (auto node : tree->getNodes()) {
            std::cout << node->getNodeName() << " # " << node->toString() << std::endl;
        }

//        std::cout << generateAstDot(tree) << std::endl;

//        std::cout << MaikuroAst::Tree::AstTreeCodeGenerator::build(sourceFile) << std::endl;

//        std::cout << sourceFile->toString() << std::endl << std::endl << std::endl;
//        std::cout << MaikuroAst::Token::toString(sourceFile->getTokens()) << std::endl << std::endl << std::endl;
    }
    catch (const char* err) {
        std::cerr << err << std::endl;
    }

    return 0;
}
