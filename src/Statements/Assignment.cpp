#include "Assignment.h"

#include <utility>

void Assignment::execute() {
  if(expression->isString()) {
    memory->add(identifier, expression->evaluateString());
  } else {
    memory->add(identifier, expression->evaluateInt());
  }

}
Assignment::Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression> expression) {
  this->memory = std::move(memory);
  this->identifier = std::move(identifier);
  this->expression = std::move(expression);
}
