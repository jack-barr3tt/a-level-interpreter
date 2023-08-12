#include "Token.h"

#include <string>

Token::Token(Token::Type type, std::string value) {
    this->type = type;
    this->value = value;
}

std::string Token::text() {
  switch (this->type) {
    case Token::COMMENT:
      return "comment";
    case Token::NUMBER:
      return "number";
    case Token::PLUS:
      return "+";
    case Token::MINUS:
      return "-";
    case Token::MULTIPLY:
      return "*";
    case Token::DIVIDE:
      return "/";
    case Token::OUTPUT:
      return "OUTPUT";
    case Token::END_OF_LINE:
      return "end of line";
    case END_OF_BLOCK:
      return "end of block";
    case Token::IDENTIFIER:
      return "identifier";
    case ASSIGNMENT:
      return "assignment";
    case Count:
      break;
  }
}

std::string Token::pattern() {
  switch (this->type) {
    case Token::COMMENT:
      return "#.+\\b";
    case Token::NUMBER:
      return "\\d+\\b";
    case Token::PLUS:
      return "\\+";
    case Token::MINUS:
      return "-";
    case Token::MULTIPLY:
      return "\\*";
    case Token::DIVIDE:
      return "/";
    case Token::OUTPUT:
      return "OUTPUT\\b";
    case Token::ASSIGNMENT:
      return "<-";
    case Token::IDENTIFIER:
      return "[a-zA-Z]+\\b";
    case Token::END_OF_LINE:
      return "\\n";
    case END_OF_BLOCK:
      // Temporary since we don't have blocks yet
      return "END_OF_BLOCK\\b";
    case Count:
      break;
  }
}

bool Token::hasData() {
  return this->type == Token::NUMBER;
}

Token::Type Token::getType() {
  return this->type;
}

std::string Token::getValue() {
  return this->value;
}
