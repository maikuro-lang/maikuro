#pragma once

#include <vector>

namespace Maikuro::Parser {

    class Token {
    public:
        enum TYPE {
            PACKAGE = 1,
            IMPORT = 2,
            AS = 3,
            CLASS = 4,
            INTERFACE = 5,
            EXTENDS = 6,
            IMPLEMENTS = 7,
            FUN = 8,
            VAR = 9,
            CONST = 10,
            IF = 11,
            UNLESS = 12,
            ELSE = 13,
            ELSEIF = 14,
            ENUM = 15,
            NEW = 16,
            FOR = 17,
            FOREACH = 18,
            LOOP = 19,
            UNTIL = 20,
            WHILE = 21,
            SWITCH = 22,
            MATCH = 23,
            CASE = 24,
            DEFAULT = 25,
            DO = 26,
            PUBLIC = 27,
            PROTECTED = 28,
            PRIVATE = 29,
            ABSTRACT = 30,
            STATIC = 31,
            FINAL = 32,
            ALIAS = 33,
            THIS = 34,
            SUPER = 35,
            RETURN = 36,
            THROW = 37,
            BREAK = 38,
            CONTINUE = 39,
            TRY = 40,
            CATCH = 41,
            FINALLY = 42,
            NULL_LITERAL = 43,
            BOOL_LITERAL = 44,
            NUMBER_LITERAL = 45,
            CHAR_LITERAL = 46,
            STRING_LITERAL = 47,
            ESCAPE_SEQUENCE_CHAR = 48,
            ESCAPE_SEQUENCE_STRING = 49,
            ESCAPE_SEQUENCE = 50,
            ARRAY_TYPE = 51,
            ATTRIBUTE_PREFIX = 52,
            LPAREN = 53,
            RPAREN = 54,
            LBRACE = 55,
            RBRACE = 56,
            LBRACK = 57,
            RBRACK = 58,
            SEMI = 59,
            COMMA = 60,
            DOT = 61,
            ASSIGN = 62,
            GT = 63,
            LT = 64,
            BANG = 65,
            TILDE = 66,
            QUESTION = 67,
            COLON = 68,
            EQUAL = 69,
            LE = 70,
            GE = 71,
            NOTEQUAL = 72,
            AND = 73,
            OR = 74,
            INC = 75,
            DEC = 76,
            ADD = 77,
            SUB = 78,
            MUL = 79,
            DIV = 80,
            BITAND = 81,
            BITOR = 82,
            CARET = 83,
            MOD = 84,
            ADD_ASSIGN = 85,
            SUB_ASSIGN = 86,
            MUL_ASSIGN = 87,
            DIV_ASSIGN = 88,
            AND_ASSIGN = 89,
            OR_ASSIGN = 90,
            XOR_ASSIGN = 91,
            MOD_ASSIGN = 92,
            LSHIFT_ASSIGN = 93,
            RSHIFT_ASSIGN = 94,
            URSHIFT_ASSIGN = 95,
            DOUBLE_ARROW = 96,
            ARROW = 97,
            COLONCOLON = 98,
            AT = 99,
            ELLIPSIS = 100,
            WS = 101,
            COMMENT = 102,
            LINE_COMMENT = 103,
            TYPE_IDENTIFIER = 104,
            IDENTIFIER = 105,
        };

        Token(Type type, const std::string &text) : _type(type), _text(text) {}

        Type getType() const { return _type; }

        [[nodiscard]] const std::string &getValue() const { return _text; }

        const std::string &toString() const { return _text; }

    private:
        Type _type;
        std::string _text;
    };

    class Node {
    public:
        Node(int line, const Token &token) : _line(line), _token(token) {}

        int getLine() const { return _line; }

        Token::Type getType() const { return _token.getType(); }

        const std::string &getValue() const { return _token.getValue(); }

        virtual std::string toString() { return _token.toString(); }

        int addNode(std::shared_ptr<Node> node) { nodes.push_back(node); }

        const std::vector<std::shared_ptr<Node>> &getNodes() const { return nodes; }

//    virtual llvm::Value *accept(Generator *v, void *param = nullptr) = 0;
    private:
        int _line;
        Token _token;
        std::vector<std::shared_ptr<Node>> nodes;
    };

    class Expression : public Node {
    public:
        Expression(int line, const Token &token) : Node(line, token) {}

//    llvm::Value *accept(Generator *v, void *param = nullptr) override {  }
    };

    class Statement : public Node {
    public:
        Statement(int line, const Token &token) : Node(line, token) {}
//    llvm::Value *accept(Generator *v, void *param = nullptr) override { return  v->visit(this,param); }
    };

    class AST {
    public:
        AST() {}

        void add(std::shared_ptr<Node> node) {
            nodes.push_back(node);
        }

        const std::vector<std::shared_ptr<Node>> &getNodes() const {
            return nodes;
        }

    private:
        std::vector<std::shared_ptr<Node>> nodes;
    };

}