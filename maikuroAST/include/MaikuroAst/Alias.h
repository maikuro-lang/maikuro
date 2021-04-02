#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Type.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class AliasDeclaration : public Statement {
     public:
        AliasDeclaration(
            AnnotationsPtrVec annotations,
            TokenPtr aliasToken,
            TypePtr type,
            TokenPtr assignToken,
            TypeDeclarationPtr typeDeclaration,
            TokenPtr semiColon
        );

        explicit AliasDeclaration(MaikuroParser::AliasDeclarationContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

        NodeType getNodeType() override;

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

    typedef shared_ptr<AliasDeclaration> AliasDeclarationPtr;
    typedef vector<AliasDeclarationPtr>  AliasDeclarationPtrVec;
}