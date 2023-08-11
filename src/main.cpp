#include <iostream>
#include "Reader.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 1)
  {
    throw runtime_error("No file specified");
  }

  Reader reader(argv[1]);

  cout << reader.read() << endl;
}