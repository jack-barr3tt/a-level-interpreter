#include "Expression.h"

#include <iostream>

Expression::Expression(std::string value) {
  this->type = ExpressionType::NUMBER;
  this->value = std::stoi(value);
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

int Expression::evaluate() {
  switch (this->type) {
    case Expression::ExpressionType::NUMBER:
      return this->value;
    case Expression::ExpressionType::ADDITION:
      return this->left->evaluate() + this->right->evaluate();
    case Expression::ExpressionType::SUBTRACTION:
      return this->left->evaluate() - this->right->evaluate();
    case Expression::ExpressionType::MULTIPLICATION:
      return this->left->evaluate() * this->right->evaluate();
    case Expression::ExpressionType::DIVISION:
      return this->left->evaluate() / this->right->evaluate();
  }

  return 123;
}
