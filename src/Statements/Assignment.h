#pragma once

#include "Statement.h"
#include "../Memory.h"
#include "../Expression.h"

class Assignment : public Statement {
private:
  std::string identifier;
  std::shared_ptr<Expression> expression;
  bool constant;
public:
  Assignment(std::string identifier, std::shared_ptr<Expression> expression, bool constant);
  void execute(std::shared_ptr<Memory> memory) override;
};