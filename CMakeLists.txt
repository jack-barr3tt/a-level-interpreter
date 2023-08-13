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
        src/Statements/Statement.h
        src/Statements/Output.cpp
        src/Statements/Output.h
        src/Statements/Statement.cpp
        src/Statements/Statement.h
        src/Statements/EmptyStatement.cpp
        src/Statements/EmptyStatement.h
        src/Expression.cpp
        src/Expression.h
        src/Memory.cpp
        src/Memory.h
        src/Statements/Assignment.cpp
        src/Statements/Assignment.h

)