//
// Created by luox6 on 2019/3/1.
//

#include <iostream>
#include <algorithm>
#include "dictionary.h"

unsigned int SHORTEST_LENGTH = 3;
std::string * EMPTY_STRING = new std::string("");

Dictionary::Dictionary(std::ifstream &file)
{
  std::string str;
  while (file >> str)
  {
    if (str.length() >= SHORTEST_LENGTH) {
      std::string * str_ptr = new std::string(str);
      list.push_back(str_ptr);
    } else {
      std::cerr << "Word " << str << " is too short to add to the dictionary." << std::endl;
    }
  }

  lengths();
}


void Dictionary::print() const
{
  std::cout << "Dict Size: " << size() << std::endl;
  for (unsigned int i = 0; i < size(); i++)
  {
    std::cout << (*list[i]) << std::endl;
  }

  std::cout << std::endl;
}

void Dictionary::lengths()
{
  // Push a zero vector at the front, as a placeholder if no result
  length.push_back(0);
  words.push_back(std::vector<std::string*>(0, EMPTY_STRING));

  for (unsigned int i = 0; i < list.size(); i++) {
    int s = length_index(list[i]->size());
    if (s == -1) {
      length.push_back(list[i]->size());
      words.push_back(std::vector<std::string*>(1, list[i]));
    } else {
      words[s].push_back(list[i]);
    }
  }
}

const std::vector<std::string*> & Dictionary::get_word_by_length(unsigned int i) const
{
  int s = length_index(i);
  if (s == -1) {
    return words[0];
  } else {
    return words[s];
  }
}

bool Dictionary::search(std::string &str) const
{
  if (!str.empty())
  {
    return std::find_if(std::begin(list), std::end(list), [str](const std::string * s1)
    {
        return *s1 == str;
    }) != std::end(list);
  }

  return false;
}


int Dictionary::length_index(unsigned int i) const {
  std::vector<unsigned int>::const_iterator itr = std::find(length.begin(), length.end(), i);

  if (itr == length.end())
  {
    return -1;
  }

  return itr - length.begin();
}

void Dictionary::clear() {
  for (unsigned int i = 0; i < list.size(); i++) {
    delete list[i];
  }

  delete EMPTY_STRING;
}

