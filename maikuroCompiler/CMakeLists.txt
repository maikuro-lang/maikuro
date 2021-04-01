cmake_minimum_required(VERSION 3.17)
project(maikuroCompiler)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(
        maikuroCompiler
        src/main.cpp
)

target_link_libraries(maikuroCompiler maikuroAST)