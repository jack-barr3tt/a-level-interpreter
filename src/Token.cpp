#include "Token.h"

Token::Token(Token::Type type, double value) {
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
    case Token::OUTPUT:
      return "OUTPUT";
  }
}

std::string Token::pattern() {
  switch (this->type) {
    case Token::COMMENT:
      return "#.+\\b";
    case Token::NUMBER:
      return "\\d\\b";
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
