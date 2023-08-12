#pragma once

#include <string>

class Token {
public:
  /*
   * Types are ordered by precedence
   * E.g OUTPUT could be matched as an IDENTIFIER, but it should be matched as OUTPUT
   */
  enum Type {
    COMMENT,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OUTPUT,
    ASSIGNMENT,
    END_OF_BLOCK,
    END_OF_LINE,
    STRING,
    IDENTIFIER,
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
