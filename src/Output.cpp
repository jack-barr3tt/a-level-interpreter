#include "Output.h"

#include <iostream>

Output::Output(std::string outputString) {
  this->outputString = outputString;
}

Output::Output(int outputInt) {
  this->outputString = std::to_string(outputInt);
}

void Output::execute() {
  if(this->outputExpression) {
    std::cout << this->outputExpression->evaluate() << std::endl;
    return;
  }
  std::cout << outputString << std::endl;
}

Output::Output(std::shared_ptr<Expression> outputExpression) {
  this->outputExpression = outputExpression;
}
