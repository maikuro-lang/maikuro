#include "VariableDeclareVisitor.h"

using namespace MaikuroGrammar;

VariableDeclareVisitor::VariableDeclareVisitor(const Parser *parser) {

}

antlrcpp::Any
VariableDeclareVisitor::visitVariableDeclaration(MaikuroParser::VariableDeclarationContext *context) {
    return antlrcpp::Any();
}

