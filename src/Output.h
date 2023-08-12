#pragma once

#include <string>
#include "Statement.h"
#include "Expression.h"

class Output : public Statement {
private:
  std::string outputString;
  std::shared_ptr<Expression> outputExpression;
public:
  Output(std::string outputString);
  Output(int outputInt);
  Output(std::shared_ptr<Expression> outputExpression);
  void execute();
};
