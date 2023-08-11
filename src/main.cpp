#include <iostream>
#include <regex>
#include "Reader.h"
#include "Token.h"

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

  string pattern = "(";

  for(int i = 0; i < Token::Type::Count; i++) {
    Token temp((Token::Type)i, 0);
    pattern += temp.pattern();
    if(i != Token::Type::Count - 1) {
      pattern += ")|(";
    }
  }
  pattern += ")";

  cout << pattern << endl;

  std::regex regexObj(pattern);

  std::smatch match;

  while (std::regex_search(inputString, match, regexObj)) {
    if(match.empty()) continue;
    string matchString = match[0];

    for(int i = 0; i < Token::Type::Count; i++) {
      Token temp((Token::Type)i, 0);
      if(std::regex_match(matchString, std::regex(temp.pattern()))) {
        cout << temp.text() << endl;
        break;
      }
    }


    inputString = match.suffix();
  }

}