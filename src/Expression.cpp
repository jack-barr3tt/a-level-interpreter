#include "Expression.h"

#include <iostream>
#include <utility>

Expression::Expression(int value) {
  this->type = ExpressionType::NUMBER;
  this->value = value;
  this->left = nullptr;
  this->right = nullptr;
}

Expression::Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
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

std::string Expression::evaluateString() {
  switch (this->type) {
    case ExpressionType::NUMBER:
      return std::to_string(this->value);
    case ExpressionType::STRING:
      return this->stringValue;
    case ExpressionType::IDENTIFIER:
      return this->memory->getString(this->identifier);
    case ExpressionType::ADDITION:
      return this->left->evaluateString() + this->right->evaluateString();
    case ExpressionType::SUBTRACTION:
      throw std::runtime_error("Wrong evaluation type");
    case ExpressionType::MULTIPLICATION:
      throw std::runtime_error("Wrong evaluation type");
    case ExpressionType::DIVISION:
      throw std::runtime_error("Wrong evaluation type");
  }

  return "123";
}

int Expression::evaluateInt() {
  switch (this->type) {
    case ExpressionType::NUMBER:
      return this->value;
    case ExpressionType::STRING:
      throw std::runtime_error("Wrong evaluation type");
    case ExpressionType::IDENTIFIER:
      return this->memory->getInt(this->identifier);
    case ExpressionType::ADDITION:
      return this->left->evaluateInt() + this->right->evaluateInt();
    case ExpressionType::SUBTRACTION:
      return this->left->evaluateInt() - this->right->evaluateInt();
    case ExpressionType::MULTIPLICATION:
      return this->left->evaluateInt() * this->right->evaluateInt();
    case ExpressionType::DIVISION:
      return this->left->evaluateInt() / this->right->evaluateInt();
    default:
      throw std::runtime_error("Unhandled expression type");
  }
}

Expression::Expression(std::shared_ptr<Memory> memory, std::string identifier) {
  this->type = ExpressionType::IDENTIFIER;
  this->memory = std::move(memory);
  this->identifier = std::move(identifier);
  this->left = nullptr;
  this->right = nullptr;
}

Expression::Expression(std::string value) {
  this->type = ExpressionType::STRING;
  this->stringValue = std::move(value);
  this->left = nullptr;
  this->right = nullptr;
}

bool Expression::isString() {
  if(this->type == ExpressionType::STRING) {
    return true;
  } else if(this->type == ExpressionType::IDENTIFIER) {
    return this->memory->getType(this->identifier) == DataType::STRING;
  } else if(this->left && this->right) {
    return this->left->isString() || this->right->isString();
  }
  return false;
}
