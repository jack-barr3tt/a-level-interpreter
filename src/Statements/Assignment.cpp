#include "Assignment.h"

void Assignment::execute(std::shared_ptr<Memory> memory) {
  memory->set(identifier, expression->evaluate(memory), constant);
}

Assignment::Assignment(std::string identifier, std::shared_ptr<Expression> expression, bool constant) {
  this->identifier = identifier;
  this->expression = std::move(expression);
  this->constant = constant;
}