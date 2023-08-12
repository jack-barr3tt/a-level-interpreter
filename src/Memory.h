#pragma once

#include <unordered_map>
#include <string>

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

  Data(DataType type, bool constant, std::vector<int> data) : type(type), constant(constant), data(data) {}
};


class Memory {
public:
  void add(std::string identifier, int value, bool constant = false);
  int getInt(std::string identifier);
private:
  std::unordered_map<std::string, int> identifiers;
  std::unordered_map<int, Data> data;

  int getKey(std::string identifier);
};
