#pragma once

#include "MaikuroParserVisitor.h"
#include "../Parser.h"

using namespace MaikuroGrammar;

class VariableDeclareVisitor : public MaikuroParserVisitor {
public:
    VariableDeclareVisitor(const Parser *parser);

    antlrcpp::Any visitVariableDeclaration(MaikuroParser::VariableDeclarationContext *context) override;

private:

};