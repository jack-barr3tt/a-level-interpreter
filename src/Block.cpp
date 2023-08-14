#include "Block.h"

#include <utility>

Block::Block(std::shared_ptr<Memory> memory, const std::vector<std::shared_ptr<Statement> > &statements) {
  this->statements = statements;
  this->memory = std::move(memory);
}

void Block::execute() {
  for (const auto& statement : statements) {
    statement->execute();
  }
}
