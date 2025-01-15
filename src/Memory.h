#pragma once

#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

enum DataType {
  INT,
  REAL,
  STRING,
  CODE,
  CHAR,
  BOOL
};

struct Data {
  Data() {

  }

  DataType type;
  bool constant;
  std::vector<int> data;

  Data(DataType type, bool constant, std::vector<int> data) : type(type), constant(constant), data(std::move(data)) {}

  Data(std::string value, bool constant) : constant(constant) {
    if (value == "True" || value == "False") {
      type = BOOL;
      data = {value == "True"};
    } else {
      type = STRING;
      for (char c : value) {
        data.push_back(c);
      }
    }
  }

  Data(int value, bool constant) : type(INT), constant(constant), data({value}) {}
};

/*
 * Memory stores all data, their identifiers, their types, and whether or not
 * they are constants.
 */
class Memory {
public:
  void set(const std::string& identifier, Data data, bool constant = false);
  /*
   * Gets the raw data from the memory
   */
  Data get(const std::string& identifier);
  /*
   * Checks if this memory has the given identifier
   */
  bool has(const std::string& identifier);
  /*
   * Pushes a new scope onto the memory
   */
  void push();
  /*
   * Pops the current scope off the memory
   */
  void pop();
private:
  std::vector<std::unordered_map<std::string, int> > identifiers;
  std::vector<std::unordered_map<int, Data> > data;

  /*
   * Gets the key associated with an identifier
   */
  std::vector<int> getKey(const std::string& identifier, bool create = false);
};
