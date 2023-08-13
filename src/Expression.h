#pragma once

#include <string>
#include "Memory.h"

/*
 * Expressions are used to evaluate values
 */
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
  /*
   * Left hand side of the expression
   */
  std::shared_ptr<Expression> left;
  /*
   * Right hand side of the expression
   */
  std::shared_ptr<Expression> right;

public:
  /*
   * Create an expression from a number
   */
  Expression(int value);
  /*
   * Create an expression from a string
   */
  Expression(std::string value);
  /*
   * Create an expression from an identifier
   */
  Expression(std::shared_ptr<Memory> memory, std::string identifier);
  /*
   * Create an expression from an operation
   */
  Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

  /*
   * Check if the expression will evaluate to a string
   */
  bool isString();
  /*
   * Evaluate a string expression
   */
  std::string evaluateString();
  /*
   * Evaluate an integer expression
   */
  int evaluateInt();
};
