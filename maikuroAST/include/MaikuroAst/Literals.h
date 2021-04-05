#pragma once

#include "common.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {

    class Literal : public AstNode, public EnableSharedFromThisVirtual<Literal> {
     public:
        explicit Literal(TokenPtr token);

        explicit Literal(antlr4::tree::TerminalNode* node);

        TokenPtrVec getTokens() override;

        TokenPtr getToken();

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        std::string getValue();

        int getLine() override;

        std::string toString() override;

     private:
        TokenPtr _token;
    };

    typedef std::shared_ptr<Literal> LiteralPtr;
    typedef std::vector<LiteralPtr>  LiteralPtrVec;

    class NullLiteral : public Literal, public EnableSharedFromThisVirtual<NullLiteral> {
     public:
        explicit NullLiteral(TokenPtr token);

        explicit NullLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<NullLiteral> NullLiteralPtr;

    class BoolLiteral : public Literal, public EnableSharedFromThisVirtual<BoolLiteral> {
     public:
        explicit BoolLiteral(TokenPtr token);

        explicit BoolLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<BoolLiteral> BoolLiteralPtr;

    class NumberLiteral : public Literal, public EnableSharedFromThisVirtual<NumberLiteral> {
     public:
        explicit NumberLiteral(TokenPtr token);

        explicit NumberLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<NumberLiteral> NumberLiteralPtr;

    class CharLiteral : public Literal, public EnableSharedFromThisVirtual<CharLiteral> {
     public:
        explicit CharLiteral(TokenPtr token);

        explicit CharLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<CharLiteral> CharLiteralPtr;

    class StringLiteral : public Literal, public EnableSharedFromThisVirtual<StringLiteral> {
     public:
        explicit StringLiteral(TokenPtr token);

        explicit StringLiteral(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<StringLiteral> StringLiteralPtr;

    class Identifier : public Literal, public EnableSharedFromThisVirtual<Identifier> {
     public:
        explicit Identifier(TokenPtr token);

        explicit Identifier(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<Identifier> IdentifierPtr;
    typedef std::vector<IdentifierPtr>  IdentifierPtrVec;

    class TypeIdentifier : public Literal, public EnableSharedFromThisVirtual<TypeIdentifier> {
     public:
        explicit TypeIdentifier(TokenPtr token);

        explicit TypeIdentifier(antlr4::tree::TerminalNode* node);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<TypeIdentifier> TypeIdentifierPtr;
    typedef std::vector<TypeIdentifierPtr>  TypeIdentifierPtrVec;

    class VisibilityModifier : public Literal, public EnableSharedFromThisVirtual<VisibilityModifier> {
     public:
        explicit VisibilityModifier(TokenPtr token);

        explicit VisibilityModifier(MaikuroGrammar::MaikuroParser::VisibilityModifierContext* ctx);

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;
    };

    typedef std::shared_ptr<VisibilityModifier> VisibilityModifierPtr;
    typedef std::vector<VisibilityModifierPtr>  VisibilityModifierPtrVec;
}


