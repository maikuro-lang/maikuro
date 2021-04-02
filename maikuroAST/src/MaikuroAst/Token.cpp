#include "MaikuroAst/Token.h"

namespace MaikuroAst {

    Token::Token(Token::Type type, const string& text, int line, int position) :
        _type(type), _text(text), _line(line), _position(position) {
    }

    Token::Type Token::getType() const {
        return _type;
    }

    const char* Token::getTypeString() {
        switch (_type) {
            case Type::PACKAGE:
                return "PACKAGE";
            case Type::IMPORT:
                return "IMPORT";
            case Type::AS:
                return "AS";
            case Type::CLASS:
                return "CLASS";
            case Type::INTERFACE:
                return "INTERFACE";
            case Type::EXTENDS:
                return "EXTENDS";
            case Type::IMPLEMENTS:
                return "IMPLEMENTS";
            case Type::FUN:
                return "FUN";
            case Type::VAR:
                return "VAR";
            case Type::CONST:
                return "CONST";
            case Type::IF:
                return "IF";
            case Type::UNLESS:
                return "UNLESS";
            case Type::ELSE:
                return "ELSE";
            case Type::ELSEIF:
                return "ELSEIF";
            case Type::ENUM:
                return "ENUM";
            case Type::NEW:
                return "NEW";
            case Type::FOR:
                return "FOR";
            case Type::FOREACH:
                return "FOREACH";
            case Type::LOOP:
                return "LOOP";
            case Type::UNTIL:
                return "UNTIL";
            case Type::WHILE:
                return "WHILE";
            case Type::SWITCH:
                return "SWITCH";
            case Type::MATCH:
                return "MATCH";
            case Type::CASE:
                return "CASE";
            case Type::DEFAULT:
                return "DEFAULT";
            case Type::DO:
                return "DO";
            case Type::PUBLIC:
                return "PUBLIC";
            case Type::PROTECTED:
                return "PROTECTED";
            case Type::PRIVATE:
                return "PRIVATE";
            case Type::ABSTRACT:
                return "ABSTRACT";
            case Type::STATIC:
                return "STATIC";
            case Type::FINAL:
                return "FINAL";
            case Type::ALIAS:
                return "ALIAS";
            case Type::THIS:
                return "THIS";
            case Type::SUPER:
                return "SUPER";
            case Type::RETURN:
                return "RETURN";
            case Type::THROW:
                return "THROW";
            case Type::BREAK:
                return "BREAK";
            case Type::CONTINUE:
                return "CONTINUE";
            case Type::TRY:
                return "TRY";
            case Type::CATCH:
                return "CATCH";
            case Type::FINALLY:
                return "FINALLY";
            case Type::NULL_LITERAL:
                return "NULL_LITERAL";
            case Type::BOOL_LITERAL:
                return "BOOL_LITERAL";
            case Type::NUMBER_LITERAL:
                return "NUMBER_LITERAL";
            case Type::CHAR_LITERAL:
                return "CHAR_LITERAL";
            case Type::STRING_LITERAL:
                return "STRING_LITERAL";
            case Type::ESCAPE_SEQUENCE_CHAR:
                return "ESCAPE_SEQUENCE_CHAR";
            case Type::ESCAPE_SEQUENCE_STRING:
                return "ESCAPE_SEQUENCE_STRING";
            case Type::ESCAPE_SEQUENCE:
                return "ESCAPE_SEQUENCE";
            case Type::ATTRIBUTE_PREFIX:
                return "ATTRIBUTE_PREFIX";
            case Type::LPAREN:
                return "LPAREN";
            case Type::RPAREN:
                return "RPAREN";
            case Type::LBRACE:
                return "LBRACE";
            case Type::RBRACE:
                return "RBRACE";
            case Type::LBRACK:
                return "LBRACK";
            case Type::RBRACK:
                return "RBRACK";
            case Type::SEMI:
                return "SEMI";
            case Type::COMMA:
                return "COMMA";
            case Type::DOT:
                return "DOT";
            case Type::ASSIGN:
                return "ASSIGN";
            case Type::GT:
                return "GT";
            case Type::LT:
                return "LT";
            case Type::BANG:
                return "BANG";
            case Type::TILDE:
                return "TILDE";
            case Type::QUESTION:
                return "QUESTION";
            case Type::COLON:
                return "COLON";
            case Type::EQUAL:
                return "EQUAL";
            case Type::LE:
                return "LE";
            case Type::GE:
                return "GE";
            case Type::NOTEQUAL:
                return "NOTEQUAL";
            case Type::AND:
                return "AND";
            case Type::OR:
                return "OR";
            case Type::INC:
                return "INC";
            case Type::DEC:
                return "DEC";
            case Type::LEFT_SHIFT:
                return "LEFT_SHIFT";
            case Type::RIGHT_SHIGT:
                return "RIGHT_SHIFT";
            case Type::URIGHT_SHIGT:
                return "URIGHT_SHIGT";
            case Type::ADD:
                return "ADD";
            case Type::SUB:
                return "SUB";
            case Type::MUL:
                return "MUL";
            case Type::DIV:
                return "DIV";
            case Type::BITAND:
                return "BITAND";
            case Type::BITOR:
                return "BITOR";
            case Type::CARET:
                return "CARET";
            case Type::MOD:
                return "MOD";
            case Type::ADD_ASSIGN:
                return "ADD_ASSIGN";
            case Type::SUB_ASSIGN:
                return "SUB_ASSIGN";
            case Type::MUL_ASSIGN:
                return "MUL_ASSIGN";
            case Type::DIV_ASSIGN:
                return "DIV_ASSIGN";
            case Type::AND_ASSIGN:
                return "AND_ASSIGN";
            case Type::OR_ASSIGN:
                return "OR_ASSIGN";
            case Type::XOR_ASSIGN:
                return "XOR_ASSIGN";
            case Type::MOD_ASSIGN:
                return "MOD_ASSIGN";
            case Type::LSHIFT_ASSIGN:
                return "LSHIFT_ASSIGN";
            case Type::RSHIFT_ASSIGN:
                return "RSHIFT_ASSIGN";
            case Type::URSHIFT_ASSIGN:
                return "URSHIFT_ASSIGN";
            case Type::DOUBLE_ARROW:
                return "DOUBLE_ARROW";
            case Type::ARROW:
                return "ARROW";
            case Type::COLONCOLON:
                return "COLONCOLON";
            case Type::AT:
                return "AT";
            case Type::ELLIPSIS:
                return "ELLIPSIS";
            case Type::WS:
                return "WS";
            case Type::COMMENT:
                return "COMMENT";
            case Type::LINE_COMMENT:
                return "LINE_COMMENT";
            case Type::TYPE_IDENTIFIER:
                return "TYPE_IDENTIFIER";
            case Type::IDENTIFIER:
                return "IDENTIFIER";
        }
    }

    int Token::getLine() {
        return _line;
    }

    int Token::getPosition() const {
        return _position;
    }

    const string& Token::getValue() const {
        return _text;
    }

    string Token::toString() {
        return _text;
    }

    void Token::mergeTokens(vector<shared_ptr<Token>>* left, vector<shared_ptr<Token>> right) {
        for (const auto& node : right) {
            if (!node) { continue; }

            left->push_back(node);
        }
    }

    shared_ptr<Token> Token::createToken(antlr4::tree::TerminalNode* token) {
        if (!token) {
            return nullptr;
        }

        return createToken(token->getSymbol());
    }

    shared_ptr<Token> Token::createToken(antlr4::Token* token) {
        if (!token) {
            return nullptr;
        }

        return make_shared<Token>(
            static_cast<Type>(token->getType()),
            token->getText(),
            token->getLine(),
            token->getCharPositionInLine()
        );
    }

    shared_ptr<Token> Token::createToken(antlr4::tree::ParseTree* token) {
        if (!token) {
            return nullptr;
        }

        if (antlrcpp::is<antlr4::tree::TerminalNode*>(token)) {
            return Token::createToken(
                dynamic_cast<antlr4::tree::TerminalNode*>(token)
            );
        }

        return nullptr;
    }

    vector<shared_ptr<Token>> Token::createTokens(vector<antlr4::tree::TerminalNode*> tokens) {
        vector<shared_ptr<Token>> result;

        result.reserve(tokens.size());
        for (auto token : tokens) {
            result.push_back(Token::createToken(token));
        }

        return result;
    }

    vector<shared_ptr<Token>> Token::createTokens(vector<antlr4::Token*> tokens) {
        vector<shared_ptr<Token>> result;

        result.reserve(tokens.size());
        for (auto token : tokens) {
            result.push_back(Token::createToken(token));
        }

        return result;
    }

    vector<shared_ptr<Token>> Token::createFromChildren(vector<antlr4::tree::ParseTree*> children) {
        vector<shared_ptr<Token>> tokens;
        for (auto* o : children) {
            if (antlrcpp::is<antlr4::tree::TerminalNode*>(o)) {
                tokens.push_back(
                    Token::createToken(
                        dynamic_cast<antlr4::tree::TerminalNode*>(o)
                    )
                );
            }
        }

        return tokens;
    }

    string Token::toString(
        std::initializer_list<shared_ptr<Token>>

        tokens
    ) {
        vector<shared_ptr<Token>> vector{ tokens };

        return
            Token::toString(vector);
    }

    string Token::toString(vector<shared_ptr<Token>> tokens) {
        string out;
        for (const auto& token : tokens) {
            out += token->toString() + " ";
        }

        out.pop_back();

        return out;
    }

    AstNode::NodeType Token::getNodeType() {
        return NodeType::TOKEN;
    }

    TokenPtrVec Token::getTokens() {
        return TokenPtrVec({shared_from_this()});
    }

    string Token::getNodeName() {
//        string nodeName = "TOKEN[";
//        nodeName += getTypeString();
//        nodeName += "]";

        return AstNode::getNodeName();
    }
}