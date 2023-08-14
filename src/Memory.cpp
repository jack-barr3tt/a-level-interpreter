#include "Memory.h"

#include <utility>

void Memory::add(const std::string& identifier, int value, bool constant) {
  int key = getKey(identifier);

  Data data(INT, constant, {value});

  this->data[key] = data;
}

int Memory::getKey(const std::string& identifier) {
  if(identifiers.find(identifier) == identifiers.end()) {
    int key = identifiers.size();
    identifiers[identifier] = key;
    return key;
  } else {
    return identifiers[identifier];
  }
}

int Memory::getInt(const std::string& identifier) {
  int key = getKey(identifier);

  Data data = this->data[key];

  if(data.type != INT) {
    throw std::runtime_error("Type mismatch");
  }

  return data.data[0];
}

std::string Memory::getString(const std::string& identifier) {
  int key = getKey(identifier);

  Data data = this->data[key];

  if(data.type != STRING) {
    throw std::runtime_error("Type mismatch");
  }

  std::string result;

  for(int i : data.data) {
    result += (char)i;
  }

  return result;
}

void Memory::add(const std::string& identifier, std::string value, bool constant) {
  int key = getKey(identifier);

  Data data(STRING, constant, {});

  for(char i : value) {
    data.data.push_back(i);
  }

  this->data[key] = data;
}

DataType Memory::getType(const std::string& identifier) {
  int key = getKey(identifier);

  return this->data[key].type;
}
