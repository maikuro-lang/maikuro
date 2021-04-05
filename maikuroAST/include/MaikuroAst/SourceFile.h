#pragma once

#include "common.h"
#include "Statement.h"
#include "Annotation.h"
#include "Package.h"
#include "AstNode.h"
#include "Token.h"

namespace MaikuroAst {

    class SourceFile : public AstNode {
     public:
        SourceFile(
            AnnotationsPtrVec annotations,
            PackageDeclarationPtr packageDeclaration,
            ImportDeclarationPtrVec importDeclarations,
            StatementPtrVec statements
        );

        explicit SourceFile(MaikuroGrammar::MaikuroParser::SourceFileContext* ctx);

        int getLine() override;

        std::string toString() override;

        TokenPtrVec getTokens() override;

        NodeType getNodeType() override;

        void accept(AstNodeVisitor* visitor) override;

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

    typedef std::shared_ptr<SourceFile> SourceFilePtr;
    typedef std::vector<SourceFilePtr>  SourceFilePtrVec;
}

