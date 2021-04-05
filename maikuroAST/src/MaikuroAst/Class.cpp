#include "MaikuroAst/Class.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/ExpressionBuilder.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Block.h"
#include "MaikuroAst/Function.h"
#include "MaikuroAst/Literals.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"
#include "MaikuroAst/Type.h"

namespace MaikuroAst {
    using std::string;
    using std::vector;
    using std::shared_ptr;
    using MaikuroGrammar::MaikuroParser;

    SuperClass::SuperClass(TokenPtr extendsToken, TypeIdentifierPtr className)
        : _extendsToken(extendsToken), _className(className) {
    }

    SuperClass::SuperClass(MaikuroParser::SuperClassContext* ctx) : SuperClass(
        Token::createToken(ctx->EXTENDS()),
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER())) {
    }

    int SuperClass::getLine() {
        return _extendsToken->getLine();
    }

    string SuperClass::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec SuperClass::getTokens() {
        TokenPtrVec tokens = { _extendsToken };

        Token::mergeTokens(&tokens, _className->getTokens());

        return tokens;
    }

    const TokenPtr& SuperClass::getExtendsToken() const {
        return _extendsToken;
    }

    const TypeIdentifierPtr& SuperClass::getClassName() const {
        return _className;
    }

    AstNode::NodeType SuperClass::getNodeType() {
        return NodeType::SUPER_CLASS;
    }

    void SuperClass::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    SuperInterfaces::SuperInterfaces(
        TokenPtr implementsToken,
        TypeIdentifierPtrVec interfaceNames,
        TokenPtrVec commas
    )
        : _implementsToken(implementsToken), _interfaceNames(interfaceNames), _commas(commas) {
    }

    SuperInterfaces::SuperInterfaces(MaikuroParser::SuperInterfacesContext* ctx)
        : SuperInterfaces(
        Token::createToken(ctx->IMPLEMENTS()),
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()),
        Token::createTokens(ctx->COMMA())
    ) {
    }

    int SuperInterfaces::getLine() {
        return _implementsToken->getLine();
    }

    string SuperInterfaces::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec SuperInterfaces::getTokens() {
        TokenPtrVec tokens = { _implementsToken };

        int i = 0;
        for (const auto& name : _interfaceNames) {
            Token::mergeTokens(&tokens, name->getTokens());

            if (_commas.size() > i) {
                tokens.push_back(_commas[i++]);
            }
        }

        return tokens;
    }

    const TokenPtr& SuperInterfaces::getImplementsToken() const {
        return _implementsToken;
    }

    const TypeIdentifierPtrVec& SuperInterfaces::getInterfaceNames() const {
        return _interfaceNames;
    }

    const TokenPtrVec& SuperInterfaces::getCommas() const {
        return _commas;
    }

    AstNode::NodeType SuperInterfaces::getNodeType() {
        return NodeType::SUPER_INTERFACES;
    }

    void SuperInterfaces::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    PropertyDeclaration::PropertyDeclaration(
        AnnotationsPtrVec annotations,
        VisibilityModifierPtr visibility,
        TypeDeclarationPtr typeDeclaration,
        IdentifierPtr identifier,
        TokenPtr assignToken,
        ExpressionPtr expression,
        TokenPtr colon
    )
        : _annotations(annotations),
          _visibility(visibility),
          _typeDeclaration(typeDeclaration),
          _identifier(identifier),
          _assignToken(assignToken),
          _expression(expression),
          _colon(colon), ClassMember() {
    }

    PropertyDeclaration::PropertyDeclaration(MaikuroParser::PropertyDeclarationContext* ctx)
        : PropertyDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        ctx->visibilityModifier() ? Utils::create<VisibilityModifier>(ctx->visibilityModifier()) : nullptr,
        Utils::create<TypeDeclaration>(ctx->typeDeclaration()),
        Utils::create<Identifier>(ctx->IDENTIFIER()),
        Token::createToken(ctx->ASSIGN()),
        eb_createExpression(ctx->expression()),
        Token::createToken(ctx->SEMI())
    ) {
    }

    int PropertyDeclaration::getLine() {
        return _identifier->getLine();
    }

    string PropertyDeclaration::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec PropertyDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        if (_visibility) {
            Token::mergeTokens(&tokens, _visibility->getTokens());
        }

        if (_typeDeclaration) {
            Token::mergeTokens(&tokens, _typeDeclaration->getTokens());
        }

        Token::mergeTokens(&tokens, _identifier->getTokens());

        if (_assignToken) {
            tokens.push_back(_assignToken);

            Token::mergeTokens(&tokens, _expression->getTokens());
        }

        tokens.push_back(_colon);

        return tokens;
    }

    const AnnotationsPtrVec& PropertyDeclaration::getAnnotations() const {
        return _annotations;
    }

    const VisibilityModifierPtr& PropertyDeclaration::getVisibility() const {
        return _visibility;
    }

    const TypeDeclarationPtr& PropertyDeclaration::getTypeDeclaration() const {
        return _typeDeclaration;
    }

    const IdentifierPtr& PropertyDeclaration::getIdentifier() const {
        return _identifier;
    }

    const TokenPtr& PropertyDeclaration::getAssignToken() const {
        return _assignToken;
    }

    const ExpressionPtr& PropertyDeclaration::getExpression() const {
        return _expression;
    }

    const TokenPtr& PropertyDeclaration::getColon() const {
        return _colon;
    }

    AstNode::NodeType PropertyDeclaration::getNodeType() {
        return NodeType::PROPERTY_DECLARATION;
    }

    void PropertyDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    MethodDeclaration::MethodDeclaration(
        AnnotationsPtrVec annotations,
        VisibilityModifierPtr visibility,
        FunctionHeaderPtr functionHeader,
        BlockPtr block
    )
        : _annotations(annotations),
          _visibility(visibility),
          _functionHeader(functionHeader),
          _block(block),
          ClassMember() {
    }

    MethodDeclaration::MethodDeclaration(MaikuroParser::MethodDeclarationContext* ctx)
        : MethodDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        ctx->visibilityModifier() ? Utils::create<VisibilityModifier>(ctx->visibilityModifier()) : nullptr,
        Utils::create<FunctionHeader>(ctx->functionHeader()),
        Utils::create<Block>(ctx->block())
    ) {
    }

    int MethodDeclaration::getLine() {
        return _functionHeader->getLine();
    }

    string MethodDeclaration::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec MethodDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        if (_visibility) {
            Token::mergeTokens(&tokens, _visibility->getTokens());
        }

        Token::mergeTokens(&tokens, _functionHeader->getTokens());
        Token::mergeTokens(&tokens, _block->getTokens());

        return tokens;
    }

    const AnnotationsPtrVec& MethodDeclaration::getAnnotations() const {
        return _annotations;
    }

    const VisibilityModifierPtr& MethodDeclaration::getVisibility() const {
        return _visibility;
    }

    const FunctionHeaderPtr& MethodDeclaration::getFunctionHeader() const {
        return _functionHeader;
    }

    const BlockPtr& MethodDeclaration::getBlock() const {
        return _block;
    }

    AstNode::NodeType MethodDeclaration::getNodeType() {
        return NodeType::METHOD_DECLARATION;
    }

    void MethodDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    AnnotationMember::AnnotationMember(AnnotationsPtr annotations)
        : _annotations(annotations), ClassMember() {
    }

    AnnotationMember::AnnotationMember(MaikuroParser::AnnotationsContext* ctx)
        : AnnotationMember(
        Utils::create<Annotations>(ctx)
    ) {
    }

    int AnnotationMember::getLine() {
        return _annotations->getLine();
    }

    string AnnotationMember::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec AnnotationMember::getTokens() {
        return _annotations->getTokens();
    }

    const AnnotationsPtr& AnnotationMember::getAnnotations() const {
        return _annotations;
    }

    AstNode::NodeType AnnotationMember::getNodeType() {
        return NodeType::ANNOTATION_MEMBER;
    }

    void AnnotationMember::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    ClassBody::ClassBody(TokenPtr leftBra, ClassMemberPtrVec classMembers, TokenPtr rightBra)
        : _leftBra(leftBra), _classMembers(classMembers), _rightBra(rightBra) {
    }

    ClassBody::ClassBody(MaikuroParser::ClassBodyContext* ctx) : ClassBody(
        Token::createToken(ctx->LBRACE()),
        ClassMemberPtrVec{},
        Token::createToken(ctx->RBRACE())
    ) {
        for (auto member : ctx->classMember()) {
            if (member->annotations()) {
                _classMembers.push_back(Utils::create<AnnotationMember>(member->annotations()));

                continue;
            }

            if (member->propertyDeclaration()) {
                _classMembers.push_back(Utils::create<PropertyDeclaration>(member->propertyDeclaration()));

                continue;
            }

            if (member->methodDeclaration()) {
                _classMembers.push_back(Utils::create<MethodDeclaration>(member->methodDeclaration()));

                continue;
            }
        }
    }

    int ClassBody::getLine() {
        return _leftBra->getLine();
    }

    string ClassBody::toString() {
        return Token::toString(getTokens());
    }

    TokenPtrVec ClassBody::getTokens() {
        TokenPtrVec tokens = { _leftBra };

        Token::mergeTokens(&tokens, Utils::getTokens<ClassMember>(_classMembers));

        tokens.push_back(_rightBra);

        return tokens;
    }

    const TokenPtr& ClassBody::getLeftBra() const {
        return _leftBra;
    }

    const ClassMemberPtrVec& ClassBody::getClassMembers() const {
        return _classMembers;
    }

    const TokenPtr& ClassBody::getRightBra() const {
        return _rightBra;
    }

    AstNode::NodeType ClassBody::getNodeType() {
        return NodeType::CLASS_BODY;
    }

    void ClassBody::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    ClassDeclaration::ClassDeclaration(
        AnnotationsPtrVec annotations,
        TokenPtr classToken,
        TypeIdentifierPtr typeIdentifier,
        SuperClassPtr superClass,
        SuperInterfacesPtr superInterfaces,
        ClassBodyPtr classBody
    )
        : _annotations(annotations),
          _classToken(classToken),
          _className(typeIdentifier),
          _superClass(superClass),
          _superInterfaces(superInterfaces),
          _classBody(classBody),
          Statement(nullptr) {
    }

    ClassDeclaration::ClassDeclaration(MaikuroParser::ClassDeclarationContext* ctx)
        : ClassDeclaration(
        Utils::create<Annotations>(ctx->annotations()),
        Token::createToken(ctx->CLASS()),
        Utils::create<TypeIdentifier>(ctx->TYPE_IDENTIFIER()),
        ctx->superClass() ? Utils::create<SuperClass>(ctx->superClass()) : nullptr,
        ctx->superInterfaces() ? Utils::create<SuperInterfaces>(ctx->superInterfaces()) : nullptr,
        Utils::create<ClassBody>(ctx->classBody())
    ) {
    }

    TokenPtrVec ClassDeclaration::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        tokens.push_back(_classToken);

        Token::mergeTokens(&tokens, _className->getTokens());

        if (_superClass) {
            Token::mergeTokens(&tokens, _superClass->getTokens());
        }

        if (_superInterfaces) {
            Token::mergeTokens(&tokens, _superInterfaces->getTokens());
        }

        Token::mergeTokens(&tokens, _classBody->getTokens());

        Token::mergeTokens(&tokens, Statement::getTokens());

        return tokens;
    }

    int ClassDeclaration::getLine() {
        return _classToken->getLine();
    }

    string ClassDeclaration::toString() {
        return Token::toString(getTokens());
    }

    const AnnotationsPtrVec& ClassDeclaration::getAnnotations() const {
        return _annotations;
    }

    const TokenPtr& ClassDeclaration::getClassToken() const {
        return _classToken;
    }

    const TypeIdentifierPtr& ClassDeclaration::getClassName() const {
        return _className;
    }

    const SuperClassPtr& ClassDeclaration::getSuperClass() const {
        return _superClass;
    }

    const SuperInterfacesPtr& ClassDeclaration::getSuperInterfaces() const {
        return _superInterfaces;
    }

    const ClassBodyPtr& ClassDeclaration::getClassBody() const {
        return _classBody;
    }

    AstNode::NodeType ClassDeclaration::getNodeType() {
        return NodeType::CLASS_DECLARATION;
    }

    void ClassDeclaration::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }

    void ClassMember::accept(AstNodeVisitor* visitor) {
        visitor->visit(this);
    }
}