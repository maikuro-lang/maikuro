#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Type.h"
#include "Token.h"

namespace MaikuroAst {
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

     private:
        AnnotationsPtrVec  _annotations;
        TokenPtr           _aliasToken;
        TypePtr            _type;
        TokenPtr           _assignToken;
        TypeDeclarationPtr _typeDeclaration;
    };

typedef shared_ptr<AliasDeclaration> AliasDeclarationPtr;
typedef vector<AliasDeclarationPtr>              AliasDeclarationPtrVec;
}