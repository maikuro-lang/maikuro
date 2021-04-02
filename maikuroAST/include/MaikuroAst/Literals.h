#pragma once

#include "common.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class Literal : public AstNode {
     public:
        explicit Literal(TokenPtr token);

        explicit Literal(antlr4::tree::TerminalNode* node);

        TokenPtrVec getTokens() override;

        TokenPtr getToken();

        NodeType getNodeType() override;

        string getValue();

        int getLine() override;

        string toString() override;

     private:
        TokenPtr _token;
    };

    typedef shared_ptr<Literal> LiteralPtr;
    typedef vector<LiteralPtr>  LiteralPtrVec;

    class NullLiteral : public Literal {
     public:
        explicit NullLiteral(TokenPtr token);

        explicit NullLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<NullLiteral> NullLiteralPtr;

    class BoolLiteral : public Literal {
     public:
        explicit BoolLiteral(TokenPtr token);

        explicit BoolLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<BoolLiteral> BoolLiteralPtr;

    class NumberLiteral : public Literal {
     public:
        explicit NumberLiteral(TokenPtr token);

        explicit NumberLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<NumberLiteral> NumberLiteralPtr;

    class CharLiteral : public Literal {
     public:
        explicit CharLiteral(TokenPtr token);

        explicit CharLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<CharLiteral> CharLiteralPtr;

    class StringLiteral : public Literal {
     public:
        explicit StringLiteral(TokenPtr token);

        explicit StringLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<StringLiteral> StringLiteralPtr;

    class Identifier : public Literal {
     public:
        explicit Identifier(TokenPtr token);

        explicit Identifier(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<Identifier> IdentifierPtr;
    typedef vector<IdentifierPtr>  IdentifierPtrVec;

    class TypeIdentifier : public Literal {
     public:
        explicit TypeIdentifier(TokenPtr token);

        explicit TypeIdentifier(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<TypeIdentifier> TypeIdentifierPtr;
    typedef vector<TypeIdentifierPtr>  TypeIdentifierPtrVec;

    class VisibilityModifier : public Literal {
     public:
        explicit VisibilityModifier(TokenPtr token);

        explicit VisibilityModifier(MaikuroParser::VisibilityModifierContext* ctx);

        NodeType getNodeType() override;
    };

    typedef shared_ptr<VisibilityModifier> VisibilityModifierPtr;
    typedef vector<VisibilityModifierPtr>  VisibilityModifierPtrVec;
}


