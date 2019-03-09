//
// Created by luox6 on 2019/3/1.
//

#include <iostream>
#include <algorithm>
#include "dictionary.h"

unsigned int SHORTEST_LENGTH = 3;

Dictionary::Dictionary(std::ifstream &file)
{
  std::string str;
  while (file >> str)
  {
    if (str.length() >= SHORTEST_LENGTH) {
      list.push_back(str);
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
    std::cout << list[i] << std::endl;
  }

  std::cout << std::endl;
}

void Dictionary::lengths()
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
      alphabet[list[i][0] - 65].push_back(list[i].size());
    }

    // Remove Duplicate
    for (unsigned int i = 0; i < alphabet.size(); i++)
    {
      std::sort( alphabet[i].begin(), alphabet[i].end() );
      alphabet[i].erase( unique( alphabet[i].begin(), alphabet[i].end() ), alphabet[i].end() );
    }
}

const std::vector<unsigned int> & Dictionary::getLength(char x) const
{
  // A => 65
  int i = x - 65;
  return alphabet[i];
}

bool Dictionary::search(std::string &str) const
{
  for (unsigned int i = 0; i < list.size(); i++)
  {
    if (list[i] == str)
    {
      return true;
    }
  }

  return false;
}

