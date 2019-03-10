//
// Created by luox6 on 2019/3/8.
//

#include <iostream>
#include <algorithm>
#include "sort.h"

sort::sort(const std::list<word> &w) {
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

std::list<solution> sort::combination(const std::list<unsigned int> &constraints) const {
  std::list<solution> s;

  // First, we need to know how many combinations should each constraint has
  std::list<unsigned int>::const_iterator cit = constraints.begin();
  std::vector<unsigned int> index;
  std::vector<unsigned int> number;

  while (cit != constraints.end()) {
    std::vector<unsigned int>::const_iterator it = std::find(std::begin(index), std::end(index), *cit);
    if (it != index.end())
    {
      number[it - index.begin()] += 1;
    } else {
      index.push_back(*cit);
      number.push_back(1);
    }
    cit++;
  }

  std::vector<std::vector<std::vector<word>>> all_chosen;
  // Choose
  for (unsigned int i = 0; i < index.size(); i++)
  {
    std::vector<std::vector<word>> temp;
    // First, we need to find given fields
    int field = found_length(index[i]);
    if (field != -1)
    {
      unsigned int choose_num = number[i];
      if (choose_num <= words[field].size()){
        std::vector<word> tmp;
        std::vector<std::vector<word>> res;
        n_choose_m(0, choose_num, words[field], tmp, res);

        all_chosen.push_back(res);
      } else {
        // No result
        return std::list<solution>();
      }
    } else {
      // Word with given length has no found, solution does not exist.
      return std::list<solution>();
    }
  }

  // Mix All Solutions
  mixed_solutions(all_chosen, s);


  return s;
}

void sort::n_choose_m(unsigned int offset,
                      unsigned int m,
                      const std::vector<word> &ls,
                      std::vector<word> &tmp,
                      std::vector<std::vector<word>> &result) const
{
  if (m == 0) {
    result.push_back(tmp);
    return;
  }

  for (unsigned int i = offset; i <= ls.size() - m; i++) {
    tmp.push_back(ls[i]);
    n_choose_m(i+1, m-1, ls, tmp, result);
    tmp.pop_back();
  }
}

void sort::mixed_solutions(const std::vector<std::vector<std::vector<word>>> &all_chosen,
                           std::list<solution> &s) const
{
  int size = all_chosen.size();
  std::vector<int> index(size, 0);

  while (true) {

    std::list<word> tmp;
    // current combination
    for (int i = 0; i < index.size(); i++)
     for (int j = 0; j < all_chosen[i][index[i]].size(); j++)
       tmp.push_back(all_chosen[i][index[i]][j]);

    s.push_back(solution(tmp));

    // find the rightmost array that has more
    // elements left after the current element
    // in that array
    int next = size - 1;
    while (next >= 0 &&
           (index[next] + 1 >= all_chosen[next].size()))
      next--;

    // no such array is found so no more
    // combinations left
    if (next < 0)
      return;

    // if found move to next element in that
    // array
    index[next]++;

    // for all arrays to the right of this
    // array current index again points to
    // first element
    for (int i = next + 1; i < size; i++)
      index[i] = 0;
  }
}

// -1 if no found
// else return index
int sort::found_length(unsigned int i) const {
  std::vector<unsigned int>::const_iterator it = std::find(std::begin(length), std::end(length), i);
  if (it != length.end()) {
    return it - length.begin();
  }

  return -1;
}


void sort::print() const {
  std::cout << "Lengths: " << std::endl;
  for (unsigned int i = 0; i < length.size(); i++) {
    std::cout << length[i] << ": ";
    for (unsigned int j = 0; j < words[i].size(); j++) {
      std::cout << words[i][j].getWord() << " ";
    }
    std::cout << std::endl;
  }
}
