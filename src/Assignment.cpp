#include "Assignment.h"

void Assignment::execute() {
  memory->add(identifier, expression->evaluate());
}
Assignment::Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression> expression) {
  this->memory = memory;
  this->identifier = identifier;
  this->expression = expression;
}
