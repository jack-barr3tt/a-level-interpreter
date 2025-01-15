#include "Output.h"

#include <iostream>

void Output::write(Data data) {
  if (data.type == DataType::BOOL) {
    std::cout << (data.data[0] ? "True" : "False") << std::endl;
    return;
  }
  if (data.type == DataType::INT) {
    std::cout << data.data[0] << std::endl;
    return;
  }
  if (data.type == DataType::STRING) {
    std::string result;

    for (int i: data.data) {
      result += (char) i;
    }

    std::cout << result << std::endl;
    return;
  }
}

void Output::execute(std::shared_ptr<Memory> memory) {
  if (outputValue.has_value()) {
    write(outputValue.value());
    return;
  }
  write(this->outputExpression->evaluate(memory));
}

Output::Output(std::shared_ptr<Expression> outputExpression) {
  this->outputExpression = std::move(outputExpression);
}

Output::Output(Data outputValue) {
  this->outputValue = outputValue;
}