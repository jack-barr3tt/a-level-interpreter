#pragma once

#include <vector>
#include "Token.h"
#include "Block.h"
#include "Expression.h"
#include "Memory.h"

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
  std::shared_ptr<Expression> parseExpression();
public:
  /*
   * Parse a series of tokens
   */
  static std::shared_ptr<Block> parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory);
};
