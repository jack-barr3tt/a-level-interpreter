#pragma once

#include "Statement.h"
#include "../Expression.h"
#include "../Block.h"

class Repeat : public Statement {
private:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Block> body;
public:
    Repeat(std::shared_ptr<Expression> condition, std::shared_ptr<Block> body);

    void execute() override;
};
