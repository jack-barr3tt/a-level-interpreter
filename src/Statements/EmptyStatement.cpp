#include "EmptyStatement.h"

#include <stdexcept>

void EmptyStatement::execute() {
  throw std::runtime_error("EmptyStatement::execute() should never be called");
}
