#include "Memory.h"

#include <utility>

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

DataType Memory::getType(const std::string& identifier) {
  int key = getKey(identifier);

  return this->data[key].type;
}

bool Memory::getBool(const std::string &identifier) {
  int key = getKey(identifier);

  Data data = this->data[key];

  if(data.type != BOOL) {
    throw std::runtime_error("Type mismatch");
  }

  return data.data[0] == 1;
}

void Memory::add(const std::string &identifier, Data data, bool constant) {
  int key = getKey(identifier);

  this->data[key] = data;
}

Data Memory::getRaw(const std::string &identifier) {
  int key = getKey(identifier);

  return this->data[key];
}