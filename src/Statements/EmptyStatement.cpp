#include "EmptyStatement.h"

#include <stdexcept>

void EmptyStatement::execute(std::shared_ptr<Memory> memory) {
  throw std::runtime_error("EmptyStatement::execute() should never be called");
}
