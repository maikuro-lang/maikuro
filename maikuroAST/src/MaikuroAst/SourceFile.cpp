#include "MaikuroAst/SourceFile.h"
#include "MaikuroAst/Utils.h"
#include "MaikuroAst/StatementBuilder.h"
#include "MaikuroAst/Annotation.h"
#include "MaikuroAst/Package.h"
#include "MaikuroAst/Statement.h"
#include "MaikuroAst/Token.h"

namespace MaikuroAst {
    SourceFile::SourceFile(
        AnnotationsPtrVec annotations,
        PackageDeclarationPtr packageDeclaration,
        ImportDeclarationPtrVec importDeclarations,
        StatementPtrVec statements
    )
        : _annotations(annotations),
          _packageDeclaration(packageDeclaration),
          _importDeclarations(importDeclarations),
          _statements(statements) {
    }

    SourceFile::SourceFile(MaikuroParser::SourceFileContext* ctx) : SourceFile(
        Utils::create<Annotations>(ctx->annotations()),
        ctx->packageDeclaration() ? Utils::create<PackageDeclaration>(ctx->packageDeclaration()) : nullptr,
        Utils::create<ImportDeclaration, MaikuroGrammar::MaikuroParser::ImportDeclarationContext*>(
            ctx->importDeclaration()
        ),
        sb_createStatement(ctx->statement())
    ) {
    }

    TokenPtrVec SourceFile::getTokens() {
        TokenPtrVec tokens;

        Token::mergeTokens(&tokens, Utils::getTokens<Annotations>(_annotations));

        if (_packageDeclaration) {
            Token::mergeTokens(&tokens, _packageDeclaration->getTokens());
        }

        Token::mergeTokens(&tokens, Utils::getTokens<ImportDeclaration>(_importDeclarations));
        Token::mergeTokens(&tokens, Utils::getTokens<Statement>(_statements));

        return tokens;
    }

    int SourceFile::getLine() {
        return 0;
    }

    string SourceFile::toString() {
        string out;

        if (_packageDeclaration) {
            out += _packageDeclaration->toString() + "\n\n";
        }

        out += Utils::nodesToString<ImportDeclaration>(_importDeclarations);
        out += Utils::nodesToString<Statement>(_statements);

        return out;
    }

    const AnnotationsPtrVec& SourceFile::getAnnotations() const {
        return _annotations;
    }

    const PackageDeclarationPtr& SourceFile::getPackageDeclaration() const {
        return _packageDeclaration;
    }

    const ImportDeclarationPtrVec& SourceFile::getImportDeclarations() const {
        return _importDeclarations;
    }

    const StatementPtrVec& SourceFile::getStatements() const {
        return _statements;
    }

    AstNode::NodeType SourceFile::getNodeType() {
        return NodeType::SOURCE_FILE;
    }
}