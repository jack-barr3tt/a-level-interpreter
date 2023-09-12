#pragma once

#include "Statement.h"
#include "../Expression.h"
#include "../Block.h"

class While : public Statement {
private:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Block> body;
public:
    While(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body);

    void execute(std::shared_ptr<Memory> memory) override;
};
