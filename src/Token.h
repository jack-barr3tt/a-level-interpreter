#pragma once

#include <string>

class Token {
public:
  /*
   * Types are ordered by precedence
   * E.g OUTPUT could be matched as an IDENTIFIER, but it should be matched as OUTPUT
   */

  /*
   * The type of token
   */
  enum Type {
    COMMENT,
    ASSIGNMENT,
    BOOLEAN,
    NOT_EQUALS,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    EQUALS,
    OR,
    AND,
    NOT,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    R_PAREN,
    L_PAREN,
    OUTPUT,
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

    /*
     * The regular expression that matches this token
     */
    std::string pattern();

    /*
     * Whether this token has data
     * E.g. a NUMBER token has data, but a PLUS token does not
     */
    bool hasData();

    /*
     * Get the type of this token
     */
    Type getType();

    /*
     * Get the value of this token
     */
    std::string getValue();
};
