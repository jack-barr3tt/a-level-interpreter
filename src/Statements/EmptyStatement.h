#pragma once


#include "Statement.h"

/*
 * Used as a placeholder for lines that have no executable code
 */
class EmptyStatement: public Statement {
public:
  void execute(std::shared_ptr<Memory> memory) override;
};
