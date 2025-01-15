#include "While.h"

#include <stdexcept>

While::While(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body) {
    this->condition = condition;
    this->body = body;
}

void While::execute(std::shared_ptr<Memory> memory) {
  while(true) {
    Data conditionValue = condition->evaluate(memory);
    if(conditionValue.type != DataType::BOOL) {
      throw std::runtime_error("While condition must be a boolean");
    }

    if(conditionValue.data[0] == 1) {
      body->execute(memory);
    } else {
      break;
    }
  }
}
