#include "Assignment.h"

void Assignment::execute() {
  if(expression->isString()) {
    memory->add(identifier, expression->evaluateString());
  } else {
    memory->add(identifier, expression->evaluateInt());
  }

}
Assignment::Assignment(std::shared_ptr<Memory> memory, std::string identifier, std::shared_ptr<Expression> expression) {
  this->memory = memory;
  this->identifier = identifier;
  this->expression = expression;
}
