#include "Memory.h"

#include <stdexcept>

std::vector<int> Memory::getKey(const std::string &identifier, bool create) {
  for (int i = 0; i < identifiers.size(); i++) {
    if (identifiers[i].find(identifier) != identifiers[i].end()) {
      return {i, identifiers[i][identifier]};
    }
  }
  if(!create) {
    throw std::runtime_error(identifier + " is undefined");
  }
  int key = identifiers[identifiers.size() - 1].size();
  identifiers[identifiers.size() - 1][identifier] = key;
  return {int(identifiers.size() - 1), key};
}

void Memory::set(const std::string &identifier, Data data, bool constant) {
  if(has(identifier) && get(identifier).constant) throw std::runtime_error("cannot modify constant value " + identifier);
  std::vector<int> key = getKey(identifier, true);
  data.constant = constant;
  this->data[key[0]][key[1]] = data;
}

Data Memory::get(const std::string &identifier) {
  std::vector<int> key = getKey(identifier);
  return this->data[key[0]][key[1]];
}

bool Memory::has(const std::string &identifier) {
  for (auto & i : identifiers) {
    if (i.find(identifier) != i.end()) {
      return true;
    }
  }
  return false;
}

void Memory::push() {
  identifiers.emplace_back();
  data.emplace_back();
}

void Memory::pop() {
  identifiers.pop_back();
  data.pop_back();
}