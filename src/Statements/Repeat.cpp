#include "Repeat.h"

Repeat::Repeat(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body) {
    this->condition = condition;
    this->body = body;
}

void Repeat::execute() {
  while(true) {
    body->execute();

    Data conditionValue = condition->evaluate();
    if(conditionValue.type != DataType::BOOL) {
      throw std::runtime_error("Repeat condition must be a boolean");
    }

    if(conditionValue.data[0] == 1) {
      break;
    }
  }
}
