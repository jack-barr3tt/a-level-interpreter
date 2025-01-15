#include "Parser.h"
#include "Statements/If.h"
#include "Statements/While.h"
#include "Statements/Repeat.h"
#include <algorithm>

std::shared_ptr<Expression> Parser::parseExpression(Token::Type target) {
  Token current = expect(Token::Type::NUMBER, Token::Type::STRING, Token::Type::BOOLEAN, Token::Type::IDENTIFIER,
                         Token::Type::L_PAREN, Token::Type::NOT);
  std::stack<Token> operators;
  std::shared_ptr<std::queue<Token> > output = std::make_shared<std::queue<Token>>();

  while (current.getType() != target) {
    if (current.getType() == Token::Type::NUMBER || current.getType() == Token::Type::STRING ||
        current.getType() == Token::Type::BOOLEAN || current.getType() == Token::Type::IDENTIFIER) {
      output->push(current);
    } else if (current.getType() == Token::Type::L_PAREN) {
      operators.push(current);
    } else if (current.getType() == Token::Type::R_PAREN) {
      while (!operators.empty() && operators.top().getType() != Token::Type::L_PAREN) {
        output->push(operators.top());
        operators.pop();
      }
      operators.pop();
    } else {
      while (!operators.empty() && current.getType() <= operators.top().getType() &&
             operators.top().getType() != Token::Type::L_PAREN) {
        output->push(operators.top());
        operators.pop();
      }
      operators.push(current);
    }
    current = next();
  }

  while (!operators.empty()) {
    output->push(operators.top());
    operators.pop();
  }

  index--;

  std::shared_ptr<Expression> expression = std::make_shared<Expression>(output);
  return expression;
}

std::shared_ptr<Block> Parser::parse(std::vector<Token> tokens) {
  Parser parser(std::move(tokens));
  return parser.parseBlock().block;
}

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = std::move(tokens);
}

Token Parser::peek() {
  return tokens[index];
}

Token Parser::next() {
  return tokens[index++];
}

template<typename... Args>
Token Parser::expect(Token::Type type, Args... args) {
  if (index >= tokens.size()) {
    throw std::runtime_error("No more tokens");
  }

  if (peek().getType() == type) {
    return next();
  }

  return expect(args...);
}

ParseBlockResult Parser::parseBlock(std::vector<Token::Type> targets) {
  if (targets.empty()) {
    throw std::runtime_error("No targets provided");
  }

  std::vector<std::shared_ptr<Statement> > statements;

  while (std::find(targets.begin(), targets.end(), peek().getType()) == targets.end()) {
    auto statement = parseStatement();
    if (!dynamic_cast<EmptyStatement *>(statement.get()))
      statements.push_back(statement);
  }

  std::shared_ptr<Block> block = std::make_shared<Block>(statements);
  return {block, peek().getType()};
}

std::shared_ptr<Statement> Parser::parseStatement() {
  Token token = next();

  switch (token.getType()) {
    case Token::COMMENT:
      expect(Token::END_OF_LINE);
      return std::make_shared<EmptyStatement>();
    case Token::Type::OUTPUT:
      return parseOutput();
    case Token::Type::IF:
      return parseIf();
    case Token::Type::WHILE:
      return parseWhile();
    case Token::Type::REPEAT:
      return parseRepeat();
    case Token::Type::IDENTIFIER:
      return parseIdentifier(token);
    case Token::Type::CONSTANT: {
      Token identifier = peek();
      index--;
      return parseIdentifier(identifier);
    }
    default:
      throw std::runtime_error("Unhandled token type");
  }
}

std::shared_ptr<Output> Parser::parseOutput() {
  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Output>(value);

}

std::shared_ptr<Statement> Parser::parseAssignment(Token token) {
  bool constant = peek().getType() == Token::Type::CONSTANT;
  index++;
  if(constant) index+=2;
  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Assignment>(token.getValue(), value, constant);
}

std::shared_ptr<Statement> Parser::parseIdentifier(Token token) {
  switch (peek().getType()) {
    case Token::Type::ASSIGNMENT:
      return parseAssignment(token);
    case Token::Type::CONSTANT:
      return parseAssignment(token);
    default:
      throw std::runtime_error("Unexpected identifier");
  }
}

Token Parser::expect() {
  throw std::runtime_error("Unexpected token");
}

std::shared_ptr<Statement> Parser::parseIf() {
  auto condition = parseExpression(Token::Type::THEN);
  expect(Token::Type::THEN);
  expect(Token::Type::END_OF_LINE);
  auto result1 = parseBlock({Token::Type::ENDIF, Token::Type::ELSE});
  if(result1.matched == Token::Type::ELSE) {
    expect(Token::Type::ELSE);
    expect(Token::Type::END_OF_LINE);
    auto result2 = parseBlock({Token::Type::ENDIF});
    expect(Token::Type::ENDIF);
    expect(Token::Type::END_OF_LINE);
    return std::make_shared<If>(condition, result1.block, result2.block);
  } else {
    expect(Token::Type::ENDIF);
    expect(Token::Type::END_OF_LINE);
    return std::make_shared<If>(condition, result1.block, nullptr);
  }
}

std::shared_ptr<Statement> Parser::parseWhile() {
  auto condition = parseExpression();
  expect(Token::Type::END_OF_LINE);
  auto result = parseBlock({Token::Type::ENDWHILE});
  expect(Token::Type::ENDWHILE);
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<While>(condition, result.block);
}

std::shared_ptr<Statement> Parser::parseRepeat() {
  expect(Token::Type::END_OF_LINE);
  auto result = parseBlock({Token::Type::UNTIL});
  expect(Token::Type::UNTIL);
  auto condition = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Repeat>(condition, result.block);
}
