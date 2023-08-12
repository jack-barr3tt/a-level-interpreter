#include "Block.h"

Block::Block(const std::vector<std::shared_ptr<Statement> > &statements) {
  this->statements = statements;
}

void Block::execute() {
  for (auto statement : statements) {
    statement->execute();
  }
}
