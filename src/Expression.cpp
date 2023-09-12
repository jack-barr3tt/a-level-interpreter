#include "Expression.h"

Expression::Expression(std::shared_ptr<std::queue<Token> > tokens) {
  this->storedTokens = tokens;
}

Data Expression::evaluate(std::shared_ptr<Memory> memory) {
  std::stack<Data> values;
  std::queue<Token> tokens(*storedTokens);

  while(!tokens.empty()) {
    Token token = tokens.front();
    tokens.pop();

    if (token.getType() == Token::Type::NUMBER) {
      values.push(Data(INT, false, {stoi(token.getValue())}));
    } else if (token.getType() == Token::Type::STRING) {
      values.push(Data(token.getValue(), false));
    } else if (token.getType() == Token::Type::BOOLEAN) {
      values.push(Data(token.getValue(), false));
    } else if (token.getType() == Token::Type::IDENTIFIER) {
      values.push(memory->get(token.getValue()));
    } else {
      if(token.getType() == Token::Type::NOT) {
        // Not is a special case because it only needs one operand
        Data lhs = values.top();
        values.pop();
        values.push(boolNot(lhs));
        continue;
      }

      if(values.size() < 2) {
        throw std::runtime_error("Missing operand");
      }

      Data rhs = values.top();
      values.pop();
      Data lhs = values.top();
      values.pop();

      switch (token.getType()) {
        case Token::Type::PLUS: {
          values.push(plus(lhs, rhs));
          break;
        }
        case Token::Type::MINUS:
          values.push(minus(lhs, rhs));
          break;
        case Token::Type::MULTIPLY:
          values.push(multiply(lhs, rhs));
          break;
        case Token::Type::DIVIDE:
          values.push(divide(lhs, rhs));
          break;
        case Token::Type::OR:
          values.push(boolOr(lhs, rhs));
          break;
        case Token::Type::AND:
          values.push(boolAnd(lhs, rhs));
          break;
        case Token::Type::EQUALS:
          values.push(equals(lhs, rhs));
          break;
        case Token::Type::LESS_THAN:
          values.push(lessThan(lhs, rhs));
          break;
        case Token::Type::GREATER_THAN:
          values.push(greaterThan(lhs, rhs));
          break;
        case Token::Type::LESS_THAN_OR_EQUAL:
          values.push(lessThanOrEqual(lhs, rhs));
          break;
        case Token::Type::GREATER_THAN_OR_EQUAL:
          values.push(greaterThanOrEqual(lhs, rhs));
          break;
        case Token::Type::NOT_EQUALS:
          values.push(notEqual(lhs, rhs));
          break;
        default:
          throw std::runtime_error("Unexpected token");
      }
    }
  }

  return values.top();
}

Data Expression::plus(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case INT:
      return Data(INT, false, {lhs.data[0] + rhs.data[0]});
    case STRING: {
      std::vector<int> result = lhs.data;
      for(int i : rhs.data) {
        result.push_back(i);
      }
      return Data(STRING, false, result);
    }
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::minus(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case INT:
      return Data(INT, false, {lhs.data[0] - rhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::multiply(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case INT:
      return Data(INT, false, {lhs.data[0] * rhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::divide(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case INT:
      return Data(INT, false, {lhs.data[0] / rhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::boolOr(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case BOOL:
      return Data(BOOL, false, {lhs.data[0] || rhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::boolAnd(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  switch (lhs.type) {
    case BOOL:
      return Data(BOOL, false, {lhs.data[0] && rhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::boolNot(Data lhs) {
  switch (lhs.type) {
    case BOOL:
      return Data(BOOL, false, {!lhs.data[0]});
    default:
      throw std::runtime_error("Missing overload");
  }
}

Data Expression::equals(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  if(lhs.type == BOOL || lhs.type == INT) {
    return Data(BOOL, false, {lhs.data[0] == rhs.data[0]});
  } else if(lhs.type == STRING) {
    return Data(BOOL, false, {lhs.data == rhs.data});
  } else {
    throw std::runtime_error("Missing overload");
  }
}

Data Expression::lessThan(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  if(lhs.type == INT) {
    return Data(BOOL, false, {lhs.data[0] < rhs.data[0]});
  } else {
    throw std::runtime_error("Missing overload");
  }
}

Data Expression::greaterThan(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  if(lhs.type == INT) {
    return Data(BOOL, false, {lhs.data[0] > rhs.data[0]});
  } else {
    throw std::runtime_error("Missing overload");
  }
}

Data Expression::lessThanOrEqual(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  if(lhs.type == INT) {
    return Data(BOOL, false, {lhs.data[0] <= rhs.data[0]});
  } else {
    throw std::runtime_error("Missing overload");
  }
}

Data Expression::greaterThanOrEqual(Data lhs, Data rhs) {
  if(lhs.type != rhs.type) {
    throw std::runtime_error("Type mismatch");
  }

  if(lhs.type == INT) {
    return Data(BOOL, false, {lhs.data[0] >= rhs.data[0]});
  } else {
    throw std::runtime_error("Missing overload");
  }
}

Data Expression::notEqual(Data lhs, Data rhs) {
  auto result = equals(lhs, rhs);
  result.data[0] = !result.data[0];
  return result;
}