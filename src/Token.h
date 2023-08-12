#pragma once

#include <string>

class Token {
public:
  enum Type {
    COMMENT,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OUTPUT,
    END_OF_BLOCK,
    END_OF_LINE,
    Count
  };

private:
  Type type;
  std::string value;

public:
    Token(Type type, std::string value);

    std::string text();

    std::string pattern();

    bool hasData();

    Type getType();

    std::string getValue();
};
