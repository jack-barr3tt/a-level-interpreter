#pragma once

#include "../Expression.h"
#include "../Block.h"

class If : public Statement {
private:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Block> ifBody;
    std::shared_ptr<Block> elseBody;
public:
    If(std::shared_ptr<Expression> condition, std::shared_ptr<Block> ifBody, std::shared_ptr<Block> elseBody = nullptr);

    void execute() override;
};
