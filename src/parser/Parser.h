#pragma once

#include "ast.h"

namespace

class Parser {
public:
    Parser() {
        this->emitDebugInfo = false;
        this->ast = std::make_shared<AST>();
    }

    int parse(std::string &source);

    void setEmitDebugInfo(bool enable) { emitDebugInfo = enable; }

private:
    bool emitDebugInfo;
    std::shared_ptr<AST> ast;
};
