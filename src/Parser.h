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

struct ParseBlockResult {
  std::shared_ptr<Block> block;
  Token::Type matched;
};

/*
 * Abstract Syntax Tree:
 * <block> ::= <statements>
 * <statements> ::= <statement> | <statement> <statements>
 * <statement> ::= <output> <end-of-line>
 * <output> ::= OUTPUT <value>
 * <value> ::= <integer> | <expression>
 * <expression> ::= <expression> <operator> <expression> | <value>
 * <operator> ::= + | - | * | / | OR | AND | < | > | <= | >= | == | !=
 */

/*
 * The Parser takes in tokens and converts them into an abstract syntax tree
 */
class Parser {
private:
  std::vector<Token> tokens;
  int index = 0;

  Parser(std::vector<Token> tokens);
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
  ParseBlockResult parseBlock(std::vector<Token::Type> targets = { Token::END_OF_BLOCK });

  /*
   * Parse the tokens that make up a statement
   */
  std::shared_ptr<Statement> parseStatement();

  /*
   * Parse the tokens that make up an output statement
   */
  std::shared_ptr<Output> parseOutput();

  /*
   * Parse the tokens that make up an if statement
   */
  std::shared_ptr<Statement> parseIf();

  /*
   * Parse the tokens that make up a while statement
   */
  std::shared_ptr<Statement> parseWhile();

  /*
   * Parse the tokens that make up a repeat statement
   */
  std::shared_ptr<Statement> parseRepeat();

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
  std::shared_ptr<Expression> parseExpression(Token::Type target = Token::Type::END_OF_LINE);

public:
  /*
   * Parse a series of tokens
   */
  static std::shared_ptr<Block> parse(std::vector<Token> tokens);
};