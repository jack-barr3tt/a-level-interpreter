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
  Output(std::string outputString);
  /*
   * Output an integer value
   */
  Output(int outputInt);
  /*
   * Output the result of an expression
   */
  Output(std::shared_ptr<Expression> outputExpression);
  void execute();
};
