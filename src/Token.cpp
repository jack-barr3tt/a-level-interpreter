#include "Token.h"

#include <string>
#include <regex>

Token::Token(Token::Type type, std::string value) {
    this->type = type;
    if(type == Token::STRING) {
      std::regex pattern("\"([^\"]*)\"");
      std::smatch matches;
      std::regex_search(value, matches, pattern);
      this->value = matches[1];
    }else{
      this->value = value;
    }
}

std::string Token::pattern() {
  switch (this->type) {
    case Token::COMMENT:
      return "^#.*";
    case Token::CONSTANT:
      return "CONSTANT\\b";
    case Token::NUMBER:
      return "\\d+\\b";
    case Token::STRING:
      return "\"([^\"]*)\"";
    case Token::BOOLEAN:
      return "True|False";
    case Token::LESS_THAN:
      return "<";
    case Token::GREATER_THAN:
      return ">";
    case Token::EQUALS:
      return "=";
    case Token::NOT_EQUALS:
      return "!=";
    case Token::LESS_THAN_OR_EQUAL:
      return "<=";
    case Token::GREATER_THAN_OR_EQUAL:
      return ">=";
    case Token::AND:
      return "AND\\b";
    case Token::OR:
      return "OR\\b";
    case Token::NOT:
      return "NOT\\b";
    case Token::PLUS:
      return "\\+";
    case Token::MINUS:
      return "-";
    case Token::MULTIPLY:
      return "\\*";
    case Token::DIVIDE:
      return "/";
    case Token::R_PAREN:
      return "\\)";
    case Token::L_PAREN:
      return "\\(";
    case Token::OUTPUT:
      return "OUTPUT\\b";
    case Token::IF:
      return "IF\\b";
    case Token::THEN:
      return "THEN\\b";
    case Token::ELSE:
      return "ELSE\\b";
    case Token::ENDIF:
      return "ENDIF\\b";
    case Token::WHILE:
      return "WHILE\\b";
    case Token::ENDWHILE:
      return "ENDWHILE\\b";
    case Token::REPEAT:
      return "REPEAT\\b";
    case Token::UNTIL:
      return "UNTIL\\b";
    case Token::ASSIGNMENT:
      return "<-";
    case Token::IDENTIFIER:
      return "[a-zA-Z]+\\b";
    case Token::END_OF_LINE:
      return "\\n";
    case END_OF_BLOCK:
      // Temporary since we don't have blocks yet
      return "END_OF_BLOCK\\b";
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
