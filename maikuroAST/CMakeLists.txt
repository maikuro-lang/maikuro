cmake_minimum_required(VERSION 3.17)
project(maikuroAST)


LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(ANTLR4_TAG 4.9.2)

# ANTLR JAR Executable Downloader
set(ANTLR4CPP_JAR_URL https://www.antlr.org/download/antlr-${ANTLR4_TAG}-complete.jar)
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-${ANTLR4_TAG}-complete.jar)

if (NOT EXISTS "${ANTLR_EXECUTABLE}")
    file(DOWNLOAD "${ANTLR4CPP_JAR_URL}" "${ANTLR_EXECUTABLE}")
endif ()

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(MaikuroLexer MaikuroLexer.g4 LEXER
             PACKAGE MaikuroGrammar)
antlr_target(MaikuroParser MaikuroParser.g4 PARSER
             PACKAGE MaikuroGrammar
             DEPENDS_ANTLR MaikuroLexer
             COMPILE_FLAGS -lib ${ANTLR_MaikuroLexer_OUTPUT_DIR}
             )

# include generated files in project environment
include_directories(${ANTLR_MaikuroLexer_OUTPUT_DIR})
include_directories(${ANTLR_MaikuroParser_OUTPUT_DIR})

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(
        maikuroAST
        src/MaikuroAst.cpp
        include/MaikuroAst.h
        ${ANTLR_MaikuroLexer_CXX_OUTPUTS}
        ${ANTLR_MaikuroParser_CXX_OUTPUTS}
        include/MaikuroAst/Token.h
        src/MaikuroAst/Token.cpp
        include/MaikuroAst/Literals.h
        src/MaikuroAst/Literals.cpp
        include/MaikuroAst/AstNode.h
        include/MaikuroAst/Package.h
        src/MaikuroAst/Package.cpp
        include/MaikuroAst/SourceFile.h
        src/MaikuroAst/SourceFile.cpp
        include/MaikuroAst/Type.h
        src/MaikuroAst/Type.cpp
        include/MaikuroAst/Annotation.h
        src/MaikuroAst/Annotation.cpp
        include/MaikuroAst/Argument.h
        src/MaikuroAst/Argument.cpp
        include/MaikuroAst/Expression.h
        src/MaikuroAst/Expression.cpp
        include/MaikuroAst/Variable.h
        src/MaikuroAst/Variable.cpp
        include/MaikuroAst/Function.h
        src/MaikuroAst/Function.cpp
        include/MaikuroAst/Statement.h
        src/MaikuroAst/Statement.cpp
        include/MaikuroAst/Alias.h
        src/MaikuroAst/Alias.cpp
        include/MaikuroAst/StatementBuilder.h
        src/MaikuroAst/StatementBuilder.cpp
        include/MaikuroAst/Block.h
        src/MaikuroAst/Block.cpp
        include/MaikuroAst/Utils.h
        include/MaikuroAst/common.h
        include/MaikuroAst/Class.h
        src/MaikuroAst/Class.cpp
        include/MaikuroAst/ExpressionBuilder.h
        src/MaikuroAst/ExpressionBuilder.cpp
        src/MaikuroAst/Statements.cpp
        include/MaikuroAst/Statements.h
        include/MaikuroAst/Tree/AstTree.h
        include/MaikuroAst/Tree/AstTreeBuilder.h
        src/MaikuroAst/Tree/AstTreeBuilder.cpp
        include/MaikuroAst/Tree/AstTreeVisitor.h
        include/MaikuroAst/Tree/AstTreeBaseVisitor.h
        include/MaikuroAst/Tree/AstTreeCodeGenerator.h
        src/MaikuroAst/Tree/AstTreeCodeGenerator.cpp
)

target_include_directories(maikuroAST PUBLIC ${ANTLR4_INCLUDE_DIRS} ${ANTLR_MaikuroLexer_OUTPUT_DIR} ${ANTLR_MaikuroParser_OUTPUT_DIR} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(maikuroAST antlr4_static)