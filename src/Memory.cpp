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
