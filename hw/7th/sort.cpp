//
// Created by luox6 on 2019/3/8.
//

#include <iostream>
#include <algorithm>
#include "sort.h"

// Receive all possible words and calculate constraints
sort::sort(const std::list<word*> &w, grid * grid2) {
  grid1 = grid2;
  std::list<word*>::const_iterator wb = w.begin();
  while (wb != w.end()) {
    int l = found_length((*wb)->length());
    if (l != -1) {
      words[l].push_back(*wb);
    } else {
      length.push_back((*wb)->length());
      words.push_back(std::vector<word*>(1, *wb));
    }
    wb++;
  }
}

// Combine and test if given set is a solution
void sort::combination(std::list<solution*> &result) const {
  std::list<unsigned int> constraints = grid1->getConstraints();

  // First, we need to know how many combinations should each constraint has
  std::list<unsigned int>::const_iterator cit = constraints.begin();
  std::vector<unsigned int> constraint_index = std::vector<unsigned int>();
  std::vector<unsigned int> number;

  while (cit != constraints.end()) {
    std::vector<unsigned int>::const_iterator it = std::find(std::begin(constraint_index), std::end(constraint_index), *cit);
    if (it != constraint_index.end())
    {
      number[it - constraint_index.begin()] += 1;
    } else {
      // No such number, push back
      constraint_index.push_back(*cit);
      number.push_back(1);
    }
    cit++;
  }

  std::vector<std::list<std::list<word*>>> all_chosen;
  // Start Choosing n from constraints m
  for (unsigned int i = 0; i < constraint_index.size(); i++)
  {
    std::vector<std::vector<word*>> temp;
    // First, we need to find given constraints
    int field = found_length((constraint_index)[i]);
    if (field != -1)
    {
      unsigned int choose_num = number[i];
      if (choose_num <= words[field].size()){
        std::vector<word*> tmp;
        std::list<std::list<word*>> res;
        n_choose_m(0, choose_num, words[field], tmp, res);

        all_chosen.push_back(res);
      } else {
        // No result
        return;
      }
    } else {
      // Word with given length has no found, solution does not exist
      // Unable to fit constraints
      return;
    }
  }

  // Mix All Solutions
  mixed_solutions(all_chosen, result);
}

// Pop all possible combinations from m
void sort::n_choose_m(unsigned int offset,
                      unsigned int m,
                      const std::vector<word*> &ls,
                      std::vector<word*> &tmp,
                      std::list<std::list<word*>> &result) const
{
  if (m == 0) {
    // Maybe a solution?
    std::list<word*> j(tmp.begin(), tmp.end());
    if (tmp.size() > 1) {
      if (solution::is_valid(j, grid1)) {
        result.push_back(j);
      }
    } else {
      result.push_back(j);
    }
    return;
  }

  for (unsigned int i = offset; i <= ls.size() - m; i++) {
    tmp.push_back(ls[i]);
    n_choose_m(i+1, m-1, ls, tmp, result);
    tmp.pop_back();
  }
}

// Mix all result given by n_choose_m process
void sort::mixed_solutions(const std::vector<std::list<std::list<word*>>> &all_chosen,
                                   std::list<solution*> &s) const
{
  if (all_chosen.size() > 1) {
    // If more then one n_choose_m given by constraints
    std::vector<std::list<word*>> j(all_chosen[0].begin(), all_chosen[0].end());
    solution_recursive(1, j, all_chosen, s);
  } else {
    // Only one kind of Solution: solve directly
    std::list<std::list<word*>>::const_iterator itr = all_chosen.front().begin();
    while (itr != all_chosen.front().end()) {
      if (solution::is_valid_last(*itr, grid1, giant)) {
        solution * so = new solution(*itr, grid1);
        s.push_back(so);
      }
      itr++;
    }
  }
}

// Combine and validate solution set (n_choose_m) one by one
void sort::solution_recursive(unsigned int index,
                              const std::vector<std::list<word*>> &tmp,
                              const std::vector<std::list<std::list<word *>>> &all_chosen,
                              std::list<solution *> &s) const {
  if (index < all_chosen.size()) {
    // Last index need post-check
    bool last = index == all_chosen.size() - 1;
    std::vector<std::list<word*>> current;

    for (unsigned int i = 0; i < tmp.size(); i++) {
      for (std::list<std::list<word *>>::const_iterator j = all_chosen[index].begin();
           j != all_chosen[index].end(); j++) {
        std::list<word*> c;
        // Combine two different solutions
        c.insert( c.end(), tmp[i].begin(), tmp[i].end() );
        c.insert( c.end(), j->begin(), j->end() );
        // Limit memory usage, check one when create one.
        if (last) {
          if (solution::is_valid_last(c, grid1, giant)) {
            solution * so = new solution(c, grid1);
            s.push_back(so);
          }
        } else {
          if (solution::is_valid(c, grid1)) {
              current.push_back(c);
          }
        }
      }
    }

    solution_recursive(index + 1, current, all_chosen, s);
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

// Set search flag
void sort::setFlags(bool solution_mode, bool count_mode, bool is_giant) {
  one_solution = solution_mode;
  count_only = count_mode;
  giant = is_giant;
}

// Debug
void sort::print() const {
  std::cout << "Lengths: " << std::endl;
  for (unsigned int i = 0; i < length.size(); i++) {
    std::cout << length[i] << ": ";
    for (unsigned int j = 0; j < words[i].size(); j++) {
      std::cout << words[i][j]->getWord() << " ";
    }
    std::cout << std::endl;
  }
}