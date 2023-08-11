#include "Reader.h"

#include <iostream>
#include <fstream>

Reader::Reader(string filename) {
    ifstream fileCheck(filename);

    if (!fileCheck.good()) {
        throw runtime_error("Could not open file");
    }

    this->file = ifstream(filename);
}

string Reader::read() {
    string contents;
    string line;

     while (getline(file, line))
     {
       contents += line + "\n";
     }

     return contents;
}
