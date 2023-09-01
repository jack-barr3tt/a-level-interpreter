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

void Output::execute() {
  if (outputValue.has_value()) {
    write(outputValue.value());
    return;
  }
  write(this->outputExpression->evaluate());
}

Output::Output(std::shared_ptr<Expression> outputExpression) {
  this->outputExpression = std::move(outputExpression);
}

Output::Output(Data outputValue) {
  this->outputValue = outputValue;
}