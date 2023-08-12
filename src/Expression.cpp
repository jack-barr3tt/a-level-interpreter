#include "Expression.h"

#include <iostream>

Expression::Expression(int value) {
  this->type = ExpressionType::NUMBER;
  this->value = value;
  this->left = nullptr;
  this->right = nullptr;
}

Expression::Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) {
  this->left = left;
  this->right = right;

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
    case Expression::ExpressionType::NUMBER:
      return std::to_string(this->value);
    case Expression::ExpressionType::STRING:
      return this->stringValue;
    case Expression::ExpressionType::IDENTIFIER:
      return this->memory->getString(this->identifier);
    case Expression::ExpressionType::ADDITION:
      return this->left->evaluateString() + this->right->evaluateString();
    case Expression::ExpressionType::SUBTRACTION:
      throw std::runtime_error("Wrong evaluation type");
    case Expression::ExpressionType::MULTIPLICATION:
      throw std::runtime_error("Wrong evaluation type");
    case Expression::ExpressionType::DIVISION:
      throw std::runtime_error("Wrong evaluation type");
  }

  return "123";
}

int Expression::evaluateInt() {
  switch (this->type) {
    case Expression::ExpressionType::NUMBER:
      return this->value;
    case Expression::ExpressionType::STRING:
      throw std::runtime_error("Wrong evaluation type");
    case Expression::ExpressionType::IDENTIFIER:
      return this->memory->getInt(this->identifier);
    case Expression::ExpressionType::ADDITION:
      return this->left->evaluateInt() + this->right->evaluateInt();
    case Expression::ExpressionType::SUBTRACTION:
      return this->left->evaluateInt() - this->right->evaluateInt();
    case Expression::ExpressionType::MULTIPLICATION:
      return this->left->evaluateInt() * this->right->evaluateInt();
    case Expression::ExpressionType::DIVISION:
      return this->left->evaluateInt() / this->right->evaluateInt();
    default:
      throw std::runtime_error("Unhandled expression type");
  }
}

Expression::Expression(std::shared_ptr<Memory> memory, std::string identifier) {
  this->type = ExpressionType::IDENTIFIER;
  this->memory = memory;
  this->identifier = identifier;
  this->left = nullptr;
  this->right = nullptr;
}

Expression::Expression(std::string value) {
  this->type = ExpressionType::STRING;
  this->stringValue = value;
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
