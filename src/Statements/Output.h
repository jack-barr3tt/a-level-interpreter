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

  void write(T data);
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

template<> void Output<bool>::write(bool data) {
  std::cout << (data ? "True" : "False") << std::endl;
}

template<typename T>
void Output<T>::write(T data) {
  std::cout << data << std::endl;
}

template <typename T>
void Output<T>::execute() {
  if(outputValue.has_value()) {
    write(outputValue.value());
    return;
  }
  write(this->outputExpression->evaluate());
}

template<typename T>
Output<T>::Output(std::shared_ptr<Expression<T> > outputExpression) {
  this->outputExpression = std::move(outputExpression);
}

template<typename T>
Output<T>::Output(T outputValue) {
  this->outputValue = outputValue;
}