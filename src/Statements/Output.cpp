#include "Output.h"

#include <iostream>
#include <utility>

Output::Output(std::string outputString) {
  this->outputString = std::move(outputString);
}

Output::Output(int outputInt) {
  this->outputString = std::to_string(outputInt);
}

void Output::execute() {
  if(this->outputExpression) {
    if(this->outputExpression->isString()) {
      std::cout << this->outputExpression->evaluateString() << std::endl;

    } else {
      std::cout << this->outputExpression->evaluateInt() << std::endl;
    }
    return;
  }
  std::cout << outputString << std::endl;
}

Output::Output(std::shared_ptr<Expression> outputExpression) {
  this->outputExpression = std::move(outputExpression);
}
