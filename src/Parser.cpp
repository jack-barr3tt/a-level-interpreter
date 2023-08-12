#include "Parser.h"
#include "Output.h"
#include "EmptyStatement.h"

#include <memory>
#include <iostream>

Block Parser::parse(std::vector<Token> tokens) {
  Parser parser(tokens);
  return parser.parseBlock();
}

Parser::Parser(std::vector<Token> tokens) {
  this->tokens = tokens;
}

Token Parser::peek() {
  return tokens[index];
}

Token Parser::next() {
  return tokens[index++];
}

Token Parser::expect(Token::Type type) {
  if(index >= tokens.size()) {
    throw std::runtime_error("No more tokens");
  }

  Token token = next();

  if(token.getType() != type) {
    throw std::runtime_error("Unexpected token");
  }

  return token;
}

Block Parser::parseBlock() {
  Block block(parseStatements());
  return block;
}

std::vector<std::shared_ptr<Statement> > Parser::parseStatements() {
  std::vector<std::shared_ptr<Statement> > statements;

  while(peek().getType() != Token::Type::END_OF_BLOCK) {
    statements.push_back(parseStatement());
  }

  return statements;
}

std::shared_ptr<Statement> Parser::parseStatement() {
  Token token = next();

  switch (token.getType()) {
    case Token::Type::OUTPUT:
      return parseOutput(token);
    case Token::COMMENT:
      expect(Token::END_OF_LINE);
      return std::make_shared<EmptyStatement>();
    default:
      throw std::runtime_error("Unhandled token type");
  }
}

std::shared_ptr<Statement> Parser::parseOutput(Token token) {
  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Output>(value);
}

std::shared_ptr<Expression> Parser::parseExpression() {
  Token lhsToken = expect(Token::Type::NUMBER);
  auto lhs = std::make_shared<Expression>(lhsToken.getValue());
  if(peek().getType() == Token::Type::END_OF_LINE) {
    return lhs;
  }

  std::string op = next().getValue();
  auto rhs = parseExpression();
  auto expression = make_shared<Expression>(op, lhs, rhs);
  return expression;
}
