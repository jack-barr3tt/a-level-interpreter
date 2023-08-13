#pragma once

#include <string>
#include <fstream>
using namespace std;

/**
 * Read a text file
 */
class Reader {
private:
    ifstream file;
public:
    explicit Reader(string filename);

    /**
     * Read the whole file
     */
    string read();
};
