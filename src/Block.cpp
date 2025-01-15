#include "Block.h"

#include <memory>

Block::Block(const std::vector<std::shared_ptr<Statement> > &statements) {
  this->statements = statements;
}

void Block::execute(std::shared_ptr<Memory> memory) {
  memory->push();
  for (const auto& statement : statements) {
    statement->execute(memory);
  }
  memory->pop();
}
