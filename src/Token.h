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
    Count
  };

private:
  Type type;
  std::string value;

public:
    Token(Type type, double value);

    std::string text();

    std::string pattern();

    bool hasData();

    Type getType();

    std::string getValue();
};
