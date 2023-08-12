#include "Block.h"

Block::Block(std::shared_ptr<Memory> memory, const std::vector<std::shared_ptr<Statement> > &statements) {
  this->statements = statements;
  this->memory = memory;
}

void Block::execute() {
  for (auto statement : statements) {
    statement->execute();
  }
}
