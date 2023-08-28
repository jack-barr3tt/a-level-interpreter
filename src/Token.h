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
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    R_PAREN,
    L_PAREN,
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
