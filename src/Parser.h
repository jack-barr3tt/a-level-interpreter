#pragma once

#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include "Token.h"
#include "Block.h"
#include "Expression.h"
#include "Memory.h"
#include "Statements/Output.h"
#include "Statements/EmptyStatement.h"
#include "Statements/Assignment.h"

/*
 * Abstract Syntax Tree:
 * <block> ::= <statements>
 * <statements> ::= <statement> | <statement> <statements>
 * <statement> ::= <output> <end-of-line>
 * <output> ::= OUTPUT <value>
 * <value> ::= <integer> | <expression>
 * <expression> ::= <value> <operator> <value>
 * <operator> ::= + | - | * | /
 */

/*
 * The Parser takes in tokens and converts them into an abstract syntax tree
 */
class Parser {
private:
  std::vector<Token> tokens;
  int index = 0;
  std::shared_ptr<Memory> memory;

  Parser(std::vector<Token> tokens, std::shared_ptr<Memory> memory);

  unordered_map<std::string, DataType> typeMap;

  /*
   * See the next token without consuming it
   */
  Token peek();

  /*
   * See the next token
   */
  Token next();

  /*
   * If this overload is called, the expected token has not been found
   * and an error is thrown
   */
  static Token expect();

  template<typename... Args>
  /*
   * Get the next token provided it matches one of the expected types
   */
  Token expect(Token::Type type, Args... args);

  /*
   * Parse a series of tokens enclosed in a block
   */
  std::shared_ptr<Block> parseBlock();

  /*
   * Parse the tokens that make up a statement
   */
  std::shared_ptr<Statement> parseStatement();

  /*
   * Parse the tokens that make up an output statement
   */
  std::shared_ptr<Output> parseOutput();

  /*
   * Parse tokens in a statement that begin with an identifier
   */
  std::shared_ptr<Statement> parseIdentifier(Token token);

  /*
   * Parse the tokens that make up an assignment statement
   */
  std::shared_ptr<Statement> parseAssignment(Token token);

  /*
   * Parse the tokens that make up an expression
   */
  std::shared_ptr<Expression> parseExpression();

public:
  /*
   * Parse a series of tokens
   */
  static std::shared_ptr<Block> parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory);
};

std::shared_ptr<Expression> Parser::parseExpression() {
  index--;
  if (peek().getType() != Token::Type::L_PAREN && peek().getType() != Token::Type::NOT) index++;

  Token current = expect(Token::Type::NUMBER, Token::Type::STRING, Token::Type::BOOLEAN, Token::Type::IDENTIFIER,
                         Token::Type::L_PAREN, Token::Type::NOT);
  std::stack<Token> operators;
  std::shared_ptr<std::queue<Token> > output = std::make_shared<std::queue<Token>>();

  while (current.getType() != Token::Type::END_OF_LINE) {
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

  std::shared_ptr<Expression> expression = std::make_shared<Expression>(output, memory);
  return expression;
}

std::shared_ptr<Block> Parser::parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory) {
  Parser parser(std::move(tokens), std::move(memory));
  return parser.parseBlock();
}

Parser::Parser(std::vector<Token> tokens, std::shared_ptr<Memory> memory) {
  this->tokens = std::move(tokens);
  this->memory = std::move(memory);
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

std::shared_ptr<Block> Parser::parseBlock() {
  std::vector<std::shared_ptr<Statement> > statements;

  while (peek().getType() != Token::Type::END_OF_BLOCK) {
    auto statement = parseStatement();
    if (!dynamic_cast<EmptyStatement *>(statement.get()))
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
    case Token::Type::IDENTIFIER: {
      auto identifier = parseIdentifier(token);
      return identifier;
    }
    default:
      throw std::runtime_error("Unhandled token type");
  }
}

std::shared_ptr<Output> Parser::parseOutput() {

  if (peek().getType() == Token::Type::L_PAREN || peek().getType() == Token::Type::NOT) index++;

  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Output>(value);

}

std::shared_ptr<Statement> Parser::parseAssignment(Token token) {
  index++;


  auto value = parseExpression();
  expect(Token::Type::END_OF_LINE);
  typeMap[token.getValue()] = DataType::INT;
  return std::make_shared<Assignment>(memory, token.getValue(), value);

}

std::shared_ptr<Statement> Parser::parseIdentifier(Token token) {
  switch (peek().getType()) {
    case Token::Type::ASSIGNMENT:
      return parseAssignment(token);
    default:
      throw std::runtime_error("Unexpected identifier");
  }
}

Token Parser::expect() {
  throw std::runtime_error("Unexpected token");
}