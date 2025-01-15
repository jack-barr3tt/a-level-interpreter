#include "Repeat.h"

#include <stdexcept>

Repeat::Repeat(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body) {
    this->condition = condition;
    this->body = body;
}

void Repeat::execute(std::shared_ptr<Memory> memory) {
  while(true) {
    body->execute(memory);

    Data conditionValue = condition->evaluate(memory);
    if(conditionValue.type != DataType::BOOL) {
      throw std::runtime_error("Repeat condition must be a boolean");
    }

    if(conditionValue.data[0] == 1) {
      break;
    }
  }
}
