#include "Parser.h"
#include "Statements/Output.h"
#include "Statements/EmptyStatement.h"
#include "Statements/Assignment.h"

#include <memory>

std::shared_ptr<Block> Parser::parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory) {
  Parser parser(tokens, memory);
  return parser.parseBlock();
}

Parser::Parser(std::vector<Token> tokens, std::shared_ptr<Memory> memory) {
  this->tokens = tokens;
  this->memory = memory;
}

Token Parser::peek() {
  return tokens[index];
}

Token Parser::next() {
  return tokens[index++];
}

template<typename... Args>
Token Parser::expect(Token::Type type, Args... args) {
  if(index >= tokens.size()) {
    throw std::runtime_error("No more tokens");
  }

  if(peek().getType() == type) {
    return next();
  }

  return expect(args...);
}

std::shared_ptr<Block> Parser::parseBlock() {
  std::vector<std::shared_ptr<Statement> > statements;

  while(peek().getType() != Token::Type::END_OF_BLOCK) {
    auto statement = parseStatement();
    if(!dynamic_cast<EmptyStatement*>(statement.get()))
      statements.push_back(statement);
  }

  auto block = std::make_shared<Block>(memory, statements);
  return block;
}

std::shared_ptr<Statement> Parser::parseStatement() {
  Token token = next();

  switch (token.getType()) {
    case Token::COMMENT:
      expect(Token::END_OF_LINE);
      return std::make_shared<EmptyStatement>();
    case Token::Type::OUTPUT:
      return parseOutput();
    case Token::Type::IDENTIFIER:
      return parseIdentifier(token);
    default:
      throw std::runtime_error("Unhandled token type");
  }
}

std::shared_ptr<Statement> Parser::parseOutput() {
  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Output>(value);
}

std::shared_ptr<Expression> Parser::parseExpression() {
  Token lhsToken = expect(Token::Type::NUMBER, Token::Type::STRING, Token::Type::IDENTIFIER);
  std::shared_ptr<Expression> lhs;
  if(lhsToken.getType() == Token::Type::NUMBER) {
    lhs = std::make_shared<Expression>(std::stoi(lhsToken.getValue()));
  }else if(lhsToken.getType() == Token::Type::STRING) {
    lhs = std::make_shared<Expression>(lhsToken.getValue());
  }else {
    lhs = std::make_shared<Expression>(memory, lhsToken.getValue());
  }
  if(peek().getType() == Token::Type::END_OF_LINE) {
    return lhs;
  }

  std::string op = next().getValue();
  auto rhs = parseExpression();
  auto expression = make_shared<Expression>(op, lhs, rhs);
  return expression;
}

std::shared_ptr<Statement> Parser::parseAssignment(Token token) {
  index++;
  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Assignment>(memory, token.getValue(), value);
}

std::shared_ptr<Statement> Parser::parseIdentifier(Token token) {
  switch(peek().getType()) {
    case Token::Type::ASSIGNMENT:
      return parseAssignment(token);
    default:
      throw std::runtime_error("Unexpected identifier");
  }
}

Token Parser::expect() {
  throw std::runtime_error("Unexpected token");
}
