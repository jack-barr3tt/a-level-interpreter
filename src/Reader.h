#pragma once

#include <string>
#include <fstream>
using namespace std;

class Reader {
private:
    ifstream file;
public:
    explicit Reader(string filename);

    string read();
};
