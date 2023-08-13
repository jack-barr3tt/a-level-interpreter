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
  std::shared_ptr<Memory> memory;
public:
  Block(std::shared_ptr<Memory> memory, const std::vector<std::shared_ptr<Statement> >& statements);
  void execute();
};
