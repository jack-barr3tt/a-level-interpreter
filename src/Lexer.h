#pragma once

#include "Token.h"
#include <string>
#include <vector>

class Lexer {
public:
  static std::string generatePattern();

  static std::vector<Token> tokenize(std::string inputString);
};
