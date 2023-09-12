#include "Assignment.h"

void Assignment::execute(std::shared_ptr<Memory> memory) {
  memory->add(identifier, expression->evaluate(memory));
}

Assignment::Assignment(std::string identifier, std::shared_ptr<Expression> expression) {
  this->identifier = identifier;
  this->expression = std::move(expression);
}