#pragma once

#include <string>
#include "Statement.h"
#include "../Expression.h"

class Output : public Statement {
private:
  /*
   * The string to be outputted
   */
  std::string outputString;
  /*
   * The expression to be evaluated and outputted
   */
  std::shared_ptr<Expression> outputExpression;
public:
  /*
   * Output a string value
   */
  explicit Output(std::string outputString);
  /*
   * Output an integer value
   */
  explicit Output(int outputInt);
  /*
   * Output the result of an expression
   */
  explicit Output(std::shared_ptr<Expression> outputExpression);
  void execute() override;
};