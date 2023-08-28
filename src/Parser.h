#pragma once

#include <utility>
#include <vector>
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

  template<typename T>
  std::shared_ptr<Output<T> > parseOutputGeneric();
  /*
   * Parse the tokens that make up an output statement
   */
  std::shared_ptr<Statement> parseOutput();
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
  template<typename T>
  std::shared_ptr<Expression<T> > parseExpression();
public:
  /*
   * Parse a series of tokens
   */
  static std::shared_ptr<Block> parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory);
};


template<typename T>
std::shared_ptr<Expression<T> > Parser::parseExpression() {
  throw std::runtime_error("Invalid type");
}

template<> inline std::shared_ptr<Expression<int> > Parser::parseExpression() {
  Token lhsToken = expect(Token::Type::NUMBER, Token::Type::IDENTIFIER);
  std::shared_ptr<Expression<int> > lhs;
  if(lhsToken.getType() == Token::Type::NUMBER) {
    lhs = std::make_shared<Expression<int> >(std::stoi(lhsToken.getValue()));
  }else{
    lhs = std::make_shared<Expression<int> >(memory, lhsToken.getValue());
  }

  if(peek().getType() == Token::Type::END_OF_LINE) {
    return lhs;
  }

  std::string op = next().getValue();
  auto rhs = parseExpression<int>();
  auto expression = std::make_shared<Expression<int> >(op, lhs, rhs);
  return expression;
}

template<> inline std::shared_ptr<Expression<std::string> > Parser::parseExpression() {
  Token lhsToken = expect(Token::Type::STRING, Token::Type::IDENTIFIER);
  std::shared_ptr<Expression<std::string> > lhs;
  if(lhsToken.getType() == Token::Type::STRING) {
    lhs = std::make_shared<Expression<std::string> >(lhsToken.getValue());
  }else{
    lhs = std::make_shared<Expression<std::string> >(memory, lhsToken.getValue());
  }

  if(peek().getType() == Token::Type::END_OF_LINE) {
    return lhs;
  }

  std::string op = next().getValue();
  auto rhs = parseExpression<std::string>();
  auto expression = std::make_shared<Expression<std::string> >(op, lhs, rhs);
  return expression;
}

template <typename T>
std::shared_ptr<Output<T> > Parser::parseOutputGeneric() {
  auto value = parseExpression<T>();
  expect(Token::Type::END_OF_LINE);
  return std::make_shared<Output<T> >(value);
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
    case Token::Type::IDENTIFIER: {
      auto identifier = parseIdentifier(token);
      return identifier;
    }
    default:
      throw std::runtime_error("Unhandled token type");
  }
}

std::shared_ptr<Statement> Parser::parseOutput() {
  switch(peek().getType()) {
    case Token::Type::NUMBER:
      return parseOutputGeneric<int>();
    case Token::Type::STRING:
      return parseOutputGeneric<std::string>();
    case Token::Type::IDENTIFIER: {
      std::string identifier = peek().getValue();
      if (typeMap[identifier] == DataType::INT)
        return parseOutputGeneric<int>();
      else if (typeMap[identifier] == DataType::STRING)
        return parseOutputGeneric<std::string>();
    }
    default:
      throw std::runtime_error("Unexpected token");
  }
}

std::shared_ptr<Statement> Parser::parseAssignment(Token token) {
  index++;

  switch (peek().getType()) {
    case Token::Type::NUMBER: {
      auto value = parseExpression<int>();
      expect(Token::Type::END_OF_LINE);
      typeMap[token.getValue()] = DataType::INT;
      return std::make_shared<Assignment<int> >(memory, token.getValue(), value);;
    }
    case Token::Type::STRING: {
      auto value = parseExpression<std::string>();
      expect(Token::Type::END_OF_LINE);
      typeMap[token.getValue()] = DataType::STRING;
      return std::make_shared<Assignment<std::string> >(memory, token.getValue(), value);
    }
    default:
      throw std::runtime_error("Unexpected token");
  }
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