#pragma once

#include "Statement.h"
#include "../Memory.h"
#include "../Expression.h"

class Assignment : public Statement {
private:
  std::shared_ptr<Memory> memory;
  std::string identifier;
  std::shared_ptr<Expression> expression;
public:
  Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression> expression);
  void execute() override;
};

void Assignment::execute() {
  memory->add(identifier, expression->evaluate());
}

Assignment::Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression> expression) {
  this->memory = memory;
  this->identifier = identifier;
  this->expression = std::move(expression);
}