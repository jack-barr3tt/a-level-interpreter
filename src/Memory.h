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
};

/*
 * Memory stores all data, their identifiers, their types, and whether or not
 * they are constants.
 */
class Memory {
public:
  /*
   * Adds an integer value to the memory
   */
  void add(const std::string& identifier, int value, bool constant = false);
  /*
   * Adds a string value to the memory
   */
  void add(const std::string& identifier, std::string value, bool constant = false);
  /*
   * Gets an integer value from the memory
   */
  int getInt(const std::string& identifier);
  /*
   * Gets a string value from the memory
   */
  std::string getString(const std::string& identifier);
  /*
   * Gets the type of a value from the memory
   */
  DataType getType(const std::string& identifier);

private:
  std::unordered_map<std::string, int> identifiers;
  std::unordered_map<int, Data> data;

  /*
   * Gets the key associated with an identifier
   */
  int getKey(const std::string& identifier);
};
