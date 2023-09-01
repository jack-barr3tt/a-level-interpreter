#pragma once

#include <string>
#include <iostream>
#include "Statement.h"
#include "../Expression.h"

class Output : public Statement {
private:
  /*
   * The value to be outputted
   */
  std::optional<Data> outputValue;
  /*
   * The expression to be evaluated and outputted
   */
  std::shared_ptr<Expression> outputExpression;

  void write(Data data);

public:
  /*
   * Output a value
   */
  explicit Output(Data outputValue);

  /*
   * Output the result of an expression
   */
  explicit Output(std::shared_ptr<Expression> outputExpression);

  void execute() override;
};