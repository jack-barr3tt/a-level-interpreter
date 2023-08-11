#include <iostream>
#include <regex>
#include "Reader.h"
#include "Token.h"
#include "Lexer.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 1)
  {
    throw runtime_error("No file specified");
  }

  Reader reader(argv[1]);

  string inputString = reader.read();

  cout << inputString << endl;

  cout << Lexer::generatePattern() << endl;

  vector<Token> tokens = Lexer::tokenize(inputString);

  for (Token token : tokens)
  {
    cout << token.getType() << " : " << token.getValue() << endl;
  }

}