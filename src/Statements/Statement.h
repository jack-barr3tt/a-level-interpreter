#pragma once

/*
 * Base class for all statements
 */
class Statement {
  public:
    /*
     * Execute the statement
     */
    virtual void execute() = 0;
};
