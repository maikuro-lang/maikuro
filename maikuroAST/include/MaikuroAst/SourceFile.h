#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Package.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    class SourceFile : public MaikuroAst::AstNode {
     public:
        SourceFile(
            AnnotationsPtrVec annotations,
            PackageDeclarationPtr packageDeclaration,
            ImportDeclarationPtrVec importDeclarations,
            StatementPtrVec statements
        );

        explicit SourceFile(MaikuroParser::SourceFileContext* ctx);

        TokenPtrVec getTokens() override;

        int getLine() override;

        string toString() override;

     private:
        AnnotationsPtrVec       _annotations;
        PackageDeclarationPtr   _packageDeclaration;
        ImportDeclarationPtrVec _importDeclarations;
        StatementPtrVec                     _statements;
    };

    typedef shared_ptr<SourceFile> SourceFilePtr;
    typedef vector<SourceFilePtr>  SourceFilePtrVec;
}

