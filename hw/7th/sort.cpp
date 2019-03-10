//
// Created by luox6 on 2019/3/8.
//

#include <iostream>
#include <algorithm>
#include "sort.h"
#include "word.h"

sort::sort(const std::list<word> &w)
{
  std::list<word>::const_iterator wb = w.begin();
  while (wb != w.end()) {
    int l = found_length((*wb).length());
    if (l != -1) {
      words[l].push_back(*wb);
    } else {
      length.push_back((*wb).length());
      words.push_back(std::vector<word>(1, *wb));
    }
    wb++;
  }
}

std::list<solution> sort::combination(std::list<unsigned int> &constraints) const
{
  std::list<solution> s;

  // First, we need to know how many combinations should each constraint has
}

void sort::print() const
{
  std::cout << "Lengths: " << std::endl;
  for (unsigned int i = 0; i < length.size(); i++) {
    std::cout << length[i] << ": ";
    for (unsigned int j = 0; j < words[i].size(); j++) {
      std::cout << words[i][j].getWord() << " ";
    }
    std::cout << std::endl;
  }
}

// -1 if no found
// else return index
int sort::found_length(unsigned int i) const
{
  std::vector<unsigned int>::const_iterator it = std::find(std::begin(length), std::end(length), i);
  if (it != length.end()) {
    return it - length.begin();
  }

  return -1;
}