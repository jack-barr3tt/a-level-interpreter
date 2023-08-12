#pragma once

#include <string>
#include "Memory.h"

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
  int value;
  std::string stringValue;
  std::string identifier;
  std::shared_ptr<Memory> memory;
  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;

public:
  Expression(int value);
  Expression(std::string value);
  Expression(std::shared_ptr<Memory> memory, std::string identifier);
  Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

  bool isString();
  std::string evaluateString();
  int evaluateInt();
};
