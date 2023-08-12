#include <iostream>
#include <regex>
#include "Reader.h"
#include "Token.h"
#include "Lexer.h"
#include "Block.h"
#include "Parser.h"

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

  Block block = Parser::parse(tokens);

  block.execute();
}