#include "Lexer.h"

#include <string>
#include <vector>
#include <regex>

std::string Lexer::generatePattern() {
  std::string pattern = "(";

  for(int i = 0; i < Token::Type::Count; i++) {
    Token temp((Token::Type)i, "");
    pattern += temp.pattern();
    if(i != Token::Type::Count - 1) {
      pattern += ")|(";
    }
  }
  pattern += ")";

  return pattern;
}

std::vector<Token> Lexer::tokenize(std::string inputString) {
  std::vector<Token> tokens;

  std::regex regexObj(generatePattern());

  std::smatch match;

  while (std::regex_search(inputString, match, regexObj)) {
    if(match.empty()) continue;

    std::string matchString = match[0];

    for(int i = 0; i < Token::Type::Count; i++) {
      Token temp((Token::Type)i, matchString);
      if(std::regex_match(matchString, std::regex(temp.pattern()))) {
        tokens.push_back(temp);
        break;
      }
    }

    inputString = match.suffix();
  }

  return tokens;
}
