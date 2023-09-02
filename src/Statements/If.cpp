#include "If.h"

If::If(std::shared_ptr<Expression> condition, std::shared_ptr<Block> ifBody, std::shared_ptr<Block> elseBody) {
    this->condition = std::move(condition);
    this->ifBody = std::move(ifBody);
    this->elseBody = std::move(elseBody);
}

void If::execute() {
  Data conditionValue = condition->evaluate();
  if(conditionValue.type != DataType::BOOL) {
    throw std::runtime_error("If condition must be a boolean");
  }

  if(conditionValue.data[0] == 1) {
    ifBody->execute();
  } else if(elseBody != nullptr) {
    elseBody->execute();
  }
}
