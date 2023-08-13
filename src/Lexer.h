#pragma once

#include "Token.h"
#include <string>
#include <vector>

/*
 * The Lexer class is responsible for taking a string of input and converting
 * it into a series of tokens.
 */
class Lexer {
public:
  /*
   * Generates a regular expression pattern that matches all tokens.
   */
  static std::string generatePattern();

  /*
   * Tokenizes the input string.
   */
  static std::vector<Token> tokenize(std::string inputString);
};
