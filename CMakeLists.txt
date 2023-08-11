# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ALevelInterpreter)

add_executable(ALevelInterpreter src/main.cpp
        src/Reader.cpp
        src/Token.cpp
        src/Token.h
        src/Lexer.cpp
        src/Lexer.h

)