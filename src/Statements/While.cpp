#include "While.h"

While::While(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body) {
    this->condition = condition;
    this->body = body;
}

void While::execute() {
  while(true) {
    Data conditionValue = condition->evaluate();
    if(conditionValue.type != DataType::BOOL) {
      throw std::runtime_error("While condition must be a boolean");
    }

    if(conditionValue.data[0] == 1) {
      body->execute();
    } else {
      break;
    }
  }
}
