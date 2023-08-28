#pragma once

#include "Statement.h"
#include "../Memory.h"
#include "../Expression.h"

template <typename T>
class Assignment : public Statement {
private:
  std::shared_ptr<Memory> memory;
  std::string identifier;
  std::shared_ptr<Expression<T> > expression;
public:
  Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression<T> > expression);
  void execute() override;
};

template <typename T>
void Assignment<T>::execute() {
  memory->add(identifier, expression->evaluate());
}

template<typename T>
Assignment<T>::Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression<T> > expression) {
  this->memory = memory;
  this->identifier = identifier;
  this->expression = std::move(expression);
}