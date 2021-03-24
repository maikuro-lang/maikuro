cmake_minimum_required(VERSION 3.17)
project(maikuro)

set(CMAKE_CXX_STANDARD 17)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(ANTLR4_TAG 4.9.2)

# ANTLR JAR Executable Downloader
set(ANTLR4CPP_JAR_URL https://www.antlr.org/download/antlr-${ANTLR4_TAG}-complete.jar)
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-${ANTLR4_TAG}-complete.jar)

if (NOT EXISTS "${ANTLR_EXECUTABLE}")
    file(DOWNLOAD "${ANTLR4CPP_JAR_URL}" "${ANTLR_EXECUTABLE}")
endif()

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
        LISTENER true
        VISITOR true
        )

# include generated files in project environment
include_directories(${ANTLR_MaikuroLexer_OUTPUT_DIR})
include_directories(${ANTLR_MaikuroParser_OUTPUT_DIR})

add_executable(
        maikuro
        src/main.cpp
        ${ANTLR_MaikuroLexer_CXX_OUTPUTS}
        ${ANTLR_MaikuroParser_CXX_OUTPUTS}
        src/parser/visitors/VariableDeclareVisitor.cpp src/parser/visitors/VariableDeclareVisitor.h src/parser/ast.h src/parser/Parser.cpp src/parser/Parser.h)

message(STATUS "aaaa         ${ANTLR_MaikuroLexer_OUTPUT_DIR}")

target_link_libraries(maikuro antlr4_static)