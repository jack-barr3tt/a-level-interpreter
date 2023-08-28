#pragma once

#include <string>
#include <utility>
#include "Memory.h"

template <typename T>
class Expression {
public:
  enum ExpressionType {
    NUMBER,
    STRING,
    IDENTIFIER,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
  };
private:
  ExpressionType type;
  T value;
  std::optional<std::string> identifier;
  std::optional<std::shared_ptr<Memory> > memory;
  /*
   * Left hand side of the expression
   */
  std::shared_ptr<Expression> left;
  /*
   * Right hand side of the expression
   */
  std::shared_ptr<Expression> right;
public:
  Expression(T value);
  Expression(std::shared_ptr<Memory> memory, std::string identifier);
  Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

  T evaluate();
};

template<typename T>
inline Expression<T>::Expression(T _value) {
  throw std::runtime_error("Invalid type");
}

template<> inline Expression<int>::Expression(int value) {
  this->type = ExpressionType::NUMBER;
  this->value = value;
}

template<> inline Expression<std::string>::Expression(std::string value) {
  this->type = ExpressionType::STRING;
  this->value = std::move(value);
}

template<typename T>
inline Expression<T>::Expression(std::shared_ptr<Memory> memory, std::string identifier) {
  this->type = ExpressionType::IDENTIFIER;
  this->memory = std::move(memory);
  this->identifier = std::move(identifier);
}

template<typename T>
inline Expression<T>::Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
  this->left = std::move(left);
  this->right = std::move(right);

  if(op == "+") {
    this->type = ExpressionType::ADDITION;
  } else if(op == "-") {
    this->type = ExpressionType::SUBTRACTION;
  } else if(op == "*") {
    this->type = ExpressionType::MULTIPLICATION;
  } else if(op == "/") {
    this->type = ExpressionType::DIVISION;
  } else {
    throw std::runtime_error("Invalid operator");
  }
}

template<> inline int Expression<int>::evaluate() {
  switch (this->type) {
    case ExpressionType::NUMBER:
      return this->value;
    case ExpressionType::IDENTIFIER:
      if(!this->memory.has_value()) throw std::runtime_error("Memory not set");
      return this->memory->get()->getInt(this->identifier.value());
    case ExpressionType::ADDITION:
      return this->left->evaluate() + this->right->evaluate();
    case ExpressionType::SUBTRACTION:
      return this->left->evaluate() - this->right->evaluate();
    case ExpressionType::MULTIPLICATION:
      return this->left->evaluate() * this->right->evaluate();
    case ExpressionType::DIVISION:
      return this->left->evaluate() / this->right->evaluate();
    default:
      throw std::runtime_error("Unhandled expression type");
  }
}

template<> inline std::string Expression<std::string>::evaluate() {
  switch (this->type) {
    case ExpressionType::STRING:
      return this->value;
    case ExpressionType::IDENTIFIER:
      if(!this->memory.has_value()) throw std::runtime_error("Memory not set");
      return this->memory->get()->getString(this->identifier.value());
    case ExpressionType::ADDITION:
      return this->left->evaluate() + this->right->evaluate();
    default:
      throw std::runtime_error("Wrong evaluation type");
  }
}