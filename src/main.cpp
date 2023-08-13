#include "Reader.h"
#include "Token.h"
#include "Lexer.h"
#include "Block.h"
#include "Parser.h"
#include "Memory.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 1)
  {
    throw runtime_error("No file specified");
  }

  Reader reader(argv[1]);

  string inputString = reader.read();

  vector<Token> tokens = Lexer::tokenize(inputString);

  auto memory = make_shared<Memory>();

  auto block = Parser::parse(tokens, memory);

  block->execute();
}