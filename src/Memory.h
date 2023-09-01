#pragma once

#include <unordered_map>
#include <string>
#include <utility>

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
  void add(const std::string& identifier, Data data, bool constant = false);
  /*
   * Gets an integer value from the memory
   */
  int getInt(const std::string& identifier);
  /*
   * Gets a string value from the memory
   */
  std::string getString(const std::string& identifier);
  /*
   * Gets a boolean value from the memory
   */
  bool getBool(const std::string& identifier);
  /*
   * Gets the type of a value from the memory
   */
  DataType getType(const std::string& identifier);
  /*
   * Gets the raw data from the memory
   */
  Data getRaw(const std::string& identifier);
private:
  std::unordered_map<std::string, int> identifiers;
  std::unordered_map<int, Data> data;

  /*
   * Gets the key associated with an identifier
   */
  int getKey(const std::string& identifier);
};
