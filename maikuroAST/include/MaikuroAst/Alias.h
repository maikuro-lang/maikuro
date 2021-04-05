#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Type.h"
#include "Token.h"

namespace MaikuroAst {
    class AliasDeclaration : public Statement, public EnableSharedFromThisVirtual<AliasDeclaration> {
     public:
        AliasDeclaration(
            AnnotationsPtrVec annotations,
            TokenPtr aliasToken,
            TypePtr type,
            TokenPtr assignToken,
            TypeDeclarationPtr typeDeclaration,
            TokenPtr semiColon
        );

        explicit AliasDeclaration(MaikuroGrammar::MaikuroParser::AliasDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        std::string toString() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

        const AnnotationsPtrVec& getAnnotations() const;

        const TokenPtr& getAliasToken() const;

        const TypePtr& getType() const;

        const TokenPtr& getAssignToken() const;

        const TypeDeclarationPtr& getTypeDeclaration() const;

     private:
        AnnotationsPtrVec  _annotations;
        TokenPtr           _aliasToken;
        TypePtr            _type;
        TokenPtr           _assignToken;
        TypeDeclarationPtr _typeDeclaration;
    };

    typedef std::shared_ptr<AliasDeclaration> AliasDeclarationPtr;
    typedef std::vector<AliasDeclarationPtr>  AliasDeclarationPtrVec;
}