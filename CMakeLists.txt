# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ALevelInterpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(ALevelInterpreter src/main.cpp
        src/Reader.cpp
        src/Token.cpp
        src/Token.h
        src/Lexer.cpp
        src/Lexer.h
        src/Parser.cpp
        src/Parser.h
        src/Block.cpp
        src/Block.h
        src/Statement.h
        src/Output.cpp
        src/Output.h
        src/Statement.cpp
        src/Statement.h
        src/EmptyStatement.cpp
        src/EmptyStatement.h
        src/Expression.cpp
        src/Expression.h
        src/Memory.cpp
        src/Memory.h
        src/Assignment.cpp
        src/Assignment.h

)