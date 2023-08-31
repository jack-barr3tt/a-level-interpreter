#pragma once

#include <string>
#include <utility>
#include <queue>
#include "Memory.h"
#include "Token.h"

template <typename T>
class Expression {
private:
  std::shared_ptr<std::queue<Token>> tokens;
  std::shared_ptr<Memory> memory;
public:
  Expression(std::shared_ptr<std::queue<Token> > tokens, std::shared_ptr<Memory> memory);
  T evaluate();
};

template<typename T>
Expression<T>::Expression(std::shared_ptr<std::queue<Token> > tokens, std::shared_ptr<Memory> memory) {
  this->tokens = tokens;
  this->memory = memory;
}

template<typename T>
T Expression<T>::evaluate() {
  throw std::runtime_error("Unexpected type");
}

template<> int Expression<int>::evaluate() {
  stack<int> values;

  while(!tokens->empty()) {
    Token token = tokens->front();
    tokens->pop();

    if (token.getType() == Token::Type::NUMBER) {
      values.push(stoi(token.getValue()));
    } else if (token.getType() == Token::Type::IDENTIFIER) {
      values.push(memory->getInt(token.getValue()));
    } else {
      int rhs = values.top();
      values.pop();
      int lhs = values.top();
      values.pop();

      switch (token.getType()) {
        case Token::Type::PLUS:
          values.push(lhs + rhs);
          break;
        case Token::Type::MINUS:
          values.push(lhs - rhs);
          break;
        case Token::Type::MULTIPLY:
          values.push(lhs * rhs);
          break;
        case Token::Type::DIVIDE:
          values.push(lhs / rhs);
          break;
        default:
          throw std::runtime_error("Unexpected token");
      }
    }
  }

  return values.top();
}

template<> std::string Expression<std::string>::evaluate() {
  stack<std::string> values;

  while(!tokens->empty()) {
    Token token = tokens->front();
    tokens->pop();

    if (token.getType() == Token::Type::STRING) {
      values.push(token.getValue());
    } else if (token.getType() == Token::Type::IDENTIFIER) {
      values.push(memory->getString(token.getValue()));
    } else {
      std::string rhs = values.top();
      values.pop();
      std::string lhs = values.top();
      values.pop();

      switch (token.getType()) {
        case Token::Type::PLUS:
          values.push(lhs + rhs);
          break;
        default:
          throw std::runtime_error("Unexpected token");
      }
    }
  }

  return values.top();
}

template<> bool Expression<bool>::evaluate() {
  stack<bool> values;

  while(!tokens->empty()) {
    Token token = tokens->front();
    tokens->pop();

    if (token.getType() == Token::Type::BOOLEAN) {
      values.push(token.getValue() == "True");
    } else if (token.getType() == Token::Type::IDENTIFIER) {
      values.push(memory->getBool(token.getValue()));
    } else {
      switch (token.getType()) {
        case Token::Type::AND: {
          bool rhs = values.top();
          values.pop();
          bool lhs = values.top();
          values.pop();
          values.push(lhs && rhs);
          break;
        }
        case Token::Type::OR: {
          bool rhs = values.top();
          values.pop();
          bool lhs = values.top();
          values.pop();
          values.push(lhs || rhs);
          break;
        }
        case Token::Type::NOT: {
          bool top = values.top();
          values.pop();
          values.push(!top);
          break;
        }
        default:
          throw std::runtime_error("Unexpected token");
      }
    }
  }

  return values.top();
}