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

class Parser {
private:
  std::vector<Token> tokens;
  int index = 0;
  std::shared_ptr<Memory> memory;

  Parser(std::vector<Token> tokens, std::shared_ptr<Memory> memory);

  Token peek();
  Token next();
  Token expect();
  template<typename... Args>
  Token expect(Token::Type type, Args... args);

  Block parseBlock();
  std::vector<std::shared_ptr<Statement> > parseStatements();
  std::shared_ptr<Statement> parseStatement();
  std::shared_ptr<Statement> parseOutput();
  std::shared_ptr<Statement> parseIdentifier(Token token);
  std::shared_ptr<Statement> parseAssignment(Token token);
  std::shared_ptr<Expression> parseExpression();
public:
  static Block parse(std::vector<Token> tokens, std::shared_ptr<Memory> memory);
};
