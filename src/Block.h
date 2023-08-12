#pragma once

#include <vector>
#include "Statement.h"

class Block {
private:
  std::vector<std::shared_ptr<Statement> > statements;
public:
  Block(const std::vector<std::shared_ptr<Statement> >& statements);
  void execute();
};
