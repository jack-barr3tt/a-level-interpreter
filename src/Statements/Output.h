#pragma once

#include <string>
#include <iostream>
#include "Statement.h"
#include "../Expression.h"

template <typename T>
class Output : public Statement {
private:
  /*
   * The value to be outputted
   */
  std::optional<T> outputValue;
  /*
   * The expression to be evaluated and outputted
   */
  std::shared_ptr<Expression<T> > outputExpression;
public:
  /*
   * Output a value
   */
  explicit Output(T outputValue);
  /*
   * Output the result of an expression
   */
  explicit Output(std::shared_ptr<Expression<T> > outputExpression);
  void execute() override;
};

template <typename T>
void Output<T>::execute() {
  if(outputValue.has_value()) {
    std::cout << outputValue.value() << std::endl;
    return;
  }
  std::cout << this->outputExpression->evaluate() << std::endl;
}

template<typename T>
Output<T>::Output(std::shared_ptr<Expression<T> > outputExpression) {
  this->outputExpression = std::move(outputExpression);
}

template<typename T>
Output<T>::Output(T outputValue) {
  this->outputValue = outputValue;
}