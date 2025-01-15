#pragma once

#include <memory>
#include "../Memory.h"

/*
 * Base class for all statements
 */
class Statement {
  public:
    /*
     * Execute the statement
     */
    virtual void execute(std::shared_ptr<Memory> memory) = 0;
};
