#pragma once

#include "common.h"
#include "AstNode.h"

namespace MaikuroAst {

    class Token;

    typedef std::shared_ptr<Token> TokenPtr;
    typedef std::vector<TokenPtr>  TokenPtrVec;

    class Token : public AstNode, public EnableSharedFromThisVirtual<Token> {
     public:
        enum Type {
            PACKAGE                = 1,
            IMPORT                 = 2,
            AS                     = 3,
            CLASS                  = 4,
            INTERFACE              = 5,
            EXTENDS                = 6,
            IMPLEMENTS             = 7,
            FUN                    = 8,
            VAR                    = 9,
            CONST                  = 10,
            IF                     = 11,
            UNLESS                 = 12,
            ELSE                   = 13,
            ELSEIF                 = 14,
            ENUM                   = 15,
            NEW                    = 16,
            FOR                    = 17,
            FOREACH                = 18,
            LOOP                   = 19,
            UNTIL                  = 20,
            WHILE                  = 21,
            SWITCH                 = 22,
            MATCH                  = 23,
            CASE                   = 24,
            DEFAULT                = 25,
            DO                     = 26,
            PUBLIC                 = 27,
            PROTECTED              = 28,
            PRIVATE                = 29,
            ABSTRACT               = 30,
            STATIC                 = 31,
            FINAL                  = 32,
            ALIAS                  = 33,
            THIS                   = 34,
            SUPER                  = 35,
            RETURN                 = 36,
            THROW                  = 37,
            BREAK                  = 38,
            CONTINUE               = 39,
            TRY                    = 40,
            CATCH                  = 41,
            FINALLY                = 42,
            NULL_LITERAL           = 43,
            BOOL_LITERAL           = 44,
            NUMBER_LITERAL         = 45,
            CHAR_LITERAL           = 46,
            STRING_LITERAL         = 47,
            ESCAPE_SEQUENCE_CHAR   = 48,
            ESCAPE_SEQUENCE_STRING = 49,
            ESCAPE_SEQUENCE        = 50,
            ATTRIBUTE_PREFIX       = 51,
            LPAREN                 = 52,
            RPAREN                 = 53,
            LBRACE                 = 54,
            RBRACE                 = 55,
            LBRACK                 = 56,
            RBRACK                 = 57,
            SEMI                   = 58,
            COMMA                  = 59,
            DOT                    = 60,
            ASSIGN                 = 61,
            GT                     = 62,
            LT                     = 63,
            BANG                   = 64,
            TILDE                  = 65,
            QUESTION               = 66,
            COLON                  = 67,
            EQUAL                  = 68,
            LE                     = 69,
            GE                     = 70,
            NOTEQUAL               = 71,
            AND                    = 72,
            OR                     = 73,
            INC                    = 74,
            DEC                    = 75,
            LEFT_SHIFT             = 76,
            RIGHT_SHIGT            = 77,
            URIGHT_SHIGT           = 78,
            ADD                    = 79,
            SUB                    = 80,
            MUL                    = 81,
            DIV                    = 82,
            BITAND                 = 83,
            BITOR                  = 84,
            CARET                  = 85,
            MOD                    = 86,
            ADD_ASSIGN             = 87,
            SUB_ASSIGN             = 88,
            MUL_ASSIGN             = 89,
            DIV_ASSIGN             = 90,
            AND_ASSIGN             = 91,
            OR_ASSIGN              = 92,
            XOR_ASSIGN             = 93,
            MOD_ASSIGN             = 94,
            LSHIFT_ASSIGN          = 95,
            RSHIFT_ASSIGN          = 96,
            URSHIFT_ASSIGN         = 97,
            DOUBLE_ARROW           = 98,
            ARROW                  = 99,
            COLONCOLON             = 100,
            AT                     = 101,
            ELLIPSIS               = 102,
            WS                     = 103,
            COMMENT                = 104,
            LINE_COMMENT           = 105,
            TYPE_IDENTIFIER        = 106,
            IDENTIFIER             = 107
        };

        enum TokenType {
            T_KEYWORD,
            T_LITERAL,
            T_SEPARATOR,
            T_OPERATOR,
            T_WHITESPACE,
            T_IDENTIFIER,
            T_UNKNOWN,
        };

        Token(
            Type type,
            const std::string& text,
            int line,
            int position
        );

        Type getType() const;

        const char* getTokenName();

        int getPosition() const;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        TokenType getTokenType();

        std::string toString() override;

        TokenPtrVec getTokens() override;

        const std::string& getValue() const;

        int getLine() override;

        static void mergeTokens(TokenPtrVec* left, TokenPtrVec right);

        static TokenPtr createToken(antlr4::tree::TerminalNode* token);

        static TokenPtr createToken(antlr4::Token* token);

        static TokenPtr createToken(antlr4::tree::ParseTree* token);

        static TokenPtrVec createTokens(std::vector<antlr4::tree::TerminalNode*> tokens);

        static TokenPtrVec createTokens(std::vector<antlr4::Token*> tokens);

        static TokenPtrVec createFromChildren(std::vector<antlr4::tree::ParseTree*> children);

        static std::string toString(std::initializer_list<std::shared_ptr<Token>> tokens);

        static std::string toString(TokenPtrVec tokens);

     private:
        Type        _type;
        std::string _text;
        int         _line;
        int         _position;
    };

}

