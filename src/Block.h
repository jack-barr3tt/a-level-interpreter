#pragma once

#include <vector>
#include "Statements/Statement.h"
#include "Memory.h"

/*
 * Blocks are a container of multiple statements
 */
class Block {
private:
  std::vector<std::shared_ptr<Statement> > statements;
public:
  Block(const std::vector<std::shared_ptr<Statement> >& statements);
  void execute(std::shared_ptr<Memory> memory);
};
