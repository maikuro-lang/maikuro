#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    Token::Token(Token::Type type, const string& text, int line, int position) :
        _type(type), _text(text), _line(line), _position(position) {
    }

    Token::Type Token::getType() const {
        return _type;
    }

    const char* Token::getTokenName() {
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
        return TokenPtrVec({ EnableSharedFromThisVirtual<Token>::shared_from_this() });
    }

    Token::TokenType Token::getTokenType() {
        switch (getType()) {
            case Token::Type::PACKAGE:
            case Token::Type::IMPORT:
            case Token::Type::AS:
            case Token::Type::CLASS:
            case Token::Type::INTERFACE:
            case Token::Type::EXTENDS:
            case Token::Type::IMPLEMENTS:
            case Token::Type::FUN:
            case Token::Type::VAR:
            case Token::Type::CONST:
            case Token::Type::IF:
            case Token::Type::UNLESS:
            case Token::Type::ELSE:
            case Token::Type::ELSEIF:
            case Token::Type::ENUM:
            case Token::Type::NEW:
            case Token::Type::FOR:
            case Token::Type::FOREACH:
            case Token::Type::LOOP:
            case Token::Type::UNTIL:
            case Token::Type::WHILE:
            case Token::Type::SWITCH:
            case Token::Type::MATCH:
            case Token::Type::CASE:
            case Token::Type::DEFAULT:
            case Token::Type::DO:
            case Token::Type::PUBLIC:
            case Token::Type::PROTECTED:
            case Token::Type::PRIVATE:
            case Token::Type::ABSTRACT:
            case Token::Type::STATIC:
            case Token::Type::FINAL:
            case Token::Type::ALIAS:
            case Token::Type::THIS:
            case Token::Type::SUPER:
            case Token::Type::RETURN:
            case Token::Type::THROW:
            case Token::Type::BREAK:
            case Token::Type::CONTINUE:
            case Token::Type::TRY:
            case Token::Type::CATCH:
            case Token::Type::FINALLY:
                return TokenType::T_KEYWORD;

            case Token::Type::NULL_LITERAL:
            case Token::Type::BOOL_LITERAL:
            case Token::Type::NUMBER_LITERAL:
            case Token::Type::CHAR_LITERAL:
            case Token::Type::STRING_LITERAL:
            case Token::Type::ESCAPE_SEQUENCE_CHAR:
            case Token::Type::ESCAPE_SEQUENCE_STRING:
            case Token::Type::ESCAPE_SEQUENCE:
                return TokenType::T_LITERAL;

            case Token::Type::ATTRIBUTE_PREFIX:
            case Token::Type::LPAREN:
            case Token::Type::RPAREN:
            case Token::Type::LBRACE:
            case Token::Type::RBRACE:
            case Token::Type::LBRACK:
            case Token::Type::RBRACK:
            case Token::Type::SEMI:
            case Token::Type::COMMA:
            case Token::Type::DOT:
                return TokenType::T_SEPARATOR;

            case Token::Type::ASSIGN:
            case Token::Type::GT:
            case Token::Type::LT:
            case Token::Type::BANG:
            case Token::Type::TILDE:
            case Token::Type::QUESTION:
            case Token::Type::COLON:
            case Token::Type::EQUAL:
            case Token::Type::LE:
            case Token::Type::GE:
            case Token::Type::NOTEQUAL:
            case Token::Type::AND:
            case Token::Type::OR:
            case Token::Type::INC:
            case Token::Type::DEC:
            case Token::Type::LEFT_SHIFT:
            case Token::Type::RIGHT_SHIGT:
            case Token::Type::URIGHT_SHIGT:
            case Token::Type::ADD:
            case Token::Type::SUB:
            case Token::Type::MUL:
            case Token::Type::DIV:
            case Token::Type::BITAND:
            case Token::Type::BITOR:
            case Token::Type::CARET:
            case Token::Type::MOD:
            case Token::Type::ADD_ASSIGN:
            case Token::Type::SUB_ASSIGN:
            case Token::Type::MUL_ASSIGN:
            case Token::Type::DIV_ASSIGN:
            case Token::Type::AND_ASSIGN:
            case Token::Type::OR_ASSIGN:
            case Token::Type::XOR_ASSIGN:
            case Token::Type::MOD_ASSIGN:
            case Token::Type::LSHIFT_ASSIGN:
            case Token::Type::RSHIFT_ASSIGN:
            case Token::Type::URSHIFT_ASSIGN:
            case Token::Type::DOUBLE_ARROW:
            case Token::Type::ARROW:
            case Token::Type::COLONCOLON:
            case Token::Type::AT:
            case Token::Type::ELLIPSIS:
                return TokenType::T_OPERATOR;

            case Token::Type::WS:
            case Token::Type::COMMENT:
            case Token::Type::LINE_COMMENT:
                return TokenType::T_WHITESPACE;

            case Token::Type::IDENTIFIER:
            case Token::Type::TYPE_IDENTIFIER:
                return TokenType::T_IDENTIFIER;

            default:
                return T_UNKNOWN;
        }
    }

    void Token::accept(AstNodeVisitor* visitor) {
        visitor->visit(EnableSharedFromThisVirtual<Token>::shared_from_this());
    }
}