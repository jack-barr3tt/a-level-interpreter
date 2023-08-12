#include "Memory.h"

void Memory::add(std::string identifier, int value, bool constant) {
  int key = getKey(identifier);

  Data data(INT, constant, {value});

  this->data[key] = data;
}

int Memory::getKey(std::string identifier) {
  if(identifiers.find(identifier) == identifiers.end()) {
    int key = identifiers.size();
    identifiers[identifier] = key;
    return key;
  } else {
    return identifiers[identifier];
  }
}

int Memory::getInt(std::string identifier) {
  int key = getKey(identifier);

  Data data = this->data[key];

  if(data.type != INT) {
    throw std::runtime_error("Type mismatch");
  }

  return data.data[0];
}

std::string Memory::getString(std::string identifier) {
  int key = getKey(identifier);

  Data data = this->data[key];

  if(data.type != STRING) {
    throw std::runtime_error("Type mismatch");
  }

  std::string result = "";

  for(int i = 0; i < data.data.size(); i++) {
    result += (char)data.data[i];
  }

  return result;
}

void Memory::add(std::string identifier, std::string value, bool constant) {
  int key = getKey(identifier);

  Data data(STRING, constant, {});

  for(int i = 0; i < value.size(); i++) {
    data.data.push_back(value[i]);
  }

  this->data[key] = data;
}

DataType Memory::getType(std::string identifier) {
  int key = getKey(identifier);

  return this->data[key].type;
}
