#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Package.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {
    using std::string;
    using std::shared_ptr;
    using std::vector;
    using MaikuroGrammar::MaikuroParser;

    class SourceFile : public AstNode {
     public:
        SourceFile(
            AnnotationsPtrVec annotations,
            PackageDeclarationPtr packageDeclaration,
            ImportDeclarationPtrVec importDeclarations,
            StatementPtrVec statements
        );

        explicit SourceFile(MaikuroParser::SourceFileContext* ctx);

        int getLine() override;

        string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        const AnnotationsPtrVec& getAnnotations() const;

        const PackageDeclarationPtr& getPackageDeclaration() const;

        const ImportDeclarationPtrVec& getImportDeclarations() const;

        const StatementPtrVec& getStatements() const;

     private:
        AnnotationsPtrVec       _annotations;
        PackageDeclarationPtr   _packageDeclaration;
        ImportDeclarationPtrVec _importDeclarations;
        StatementPtrVec         _statements;
    };

    typedef shared_ptr<SourceFile> SourceFilePtr;
    typedef vector<SourceFilePtr>  SourceFilePtrVec;
}

