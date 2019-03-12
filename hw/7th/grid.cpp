//
// Created by luox6 on 2019/3/1.
//

#include <iostream>
#include <list>
#include <algorithm>
#include "grid.h"

const char NOTE_SYMBOL = '!';
const char CONSTRAINT_SYMBOL = '+';
const char PLACEHOLDER_SYMBOL = '#';

grid::grid(std::vector<std::vector<char>> *m,
           std::list<unsigned int> * c):map(m), total_constraints(c) {
  constraints = (*c);
}

void grid::print() const {
  std::cout << "Map: " << row() << " x " << col() << std::endl;
  std::cout << "Constraint: " << num_const() << std::endl;
  std::list<unsigned int>::const_iterator cb = constraints.begin();
  while (cb != constraints.end()) {
    std::cout << *cb << " ";
    cb++;
  }
  std::cout << std::endl;

  for (unsigned int i = 0; i < map->size(); i++) {
    for (unsigned int j = 0; j < map[i].size(); j++) {
      std::cout << (*map)[i][j];
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

std::string grid::getString(unsigned int x, unsigned int y, int type, unsigned int length) const {
  // Type 0: across, Type 1: Down
  std::string str;
  if (isLegalIndex(x, y)) {
    unsigned int end_x = x, end_y = y;
    if (type == 0) {
      end_x += length - 1;
    } else {
      end_y += length - 1;
    }

    if (isLegalIndex(end_x, end_y)) {
      if (type == 0) {
        for (unsigned int i = x; i <= end_x; i++) {
          if ((*map)[y][i] != PLACEHOLDER_SYMBOL) {
            str.push_back((*map)[y][i]);
          } else {
            return std::string();
          }
        }
      } else {
        for (unsigned int i = y; i <= end_y; i++) {
          if ((*map)[i][x] != PLACEHOLDER_SYMBOL) {
            str.push_back((*map)[i][x]);
          } else {
            return std::string();
          }
        }
      }
    }
  }

  return str;
}


char grid::getChar(unsigned int x, unsigned int y) const {
  if (isLegalIndex(x, y)) { return (*map)[y][x]; }
  return '\0';
}

grid &grid::operator=(const grid &grid1) {
  if (this != &grid1) {
    clear();
    copy(grid1);
  }

  return *this;
}

void grid::clear() {
  constraints.clear();
//  if (current_word != nullptr){
//    std::list<word*>::iterator i = searched.begin();
//    while(i != searched.end()) {
//      delete *i;
//      i++;
//    }
//  } else {
    delete current_word;
//  }
}

bool grid::isAllBlocked() const {
  for (int i = 0; i < map->size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if ((*map)[i][j] != '#') {
        return false;
      }
    }
  }

  return true;
}

grid::grid(const grid &grid1) {copy(grid1);}

void grid::copy(const grid &grid1) {
  map = grid1.map;
  total_constraints = grid1.total_constraints;
  constraints = grid1.constraints;
  searched = grid1.searched;
  // No Copy of current word
}

bool grid::search_word(unsigned int l,
                       const Dictionary &dict,
                       std::list<grid> &result) const {
  // If found the word, create a new grid and put that word into current, and return true
  bool flag = false;
  found_recursive(0, 0, l, dict, flag, result);
  // If no found, return false

  return flag;
}


bool grid::is_valid(const Dictionary &d) const
{
  return no_same_word() && no_collapse() && no_invalid_words();
}

void grid::generate_overlay()
{
  std::vector<std::vector<char>>overlay = std::vector<std::vector<char>>(g.row(), std::vector<char>(g.col(), '#'));

  for (std::list<word*>::const_iterator i = word_list.begin(); i != word_list.end(); i++)
  {
    unsigned int x1 = (*i)->start_x();
    unsigned int x2 = (*i)->end_x();
    unsigned int y1 = (*i)->start_y();
    unsigned int y2 = (*i)->end_y();

    if (y1 == y2)
    {
      // x axis
      for (unsigned int j = x1; j <= x2; j++)
      {
        overlay[y1][j] = (*i)->getWord()[j - x1];
      }
    } else {
      // y axis
      for (unsigned int j = y1; j <= y2; j++)
      {
        overlay[j][x1] = (*i)->getWord()[j - y1];
      }
    }
  }

  map = grid(overlay);
}

bool grid::no_collapse() const
{
  std::list<word*>::const_iterator cit = getSearched().begin();
  while(cit != getSearched().end()) {
    std::list<word*>::const_iterator tmp(cit);
    tmp++;
    while (tmp != getSearched().end()) {
      if (word::collapse(**cit, **tmp)) {
        return false;
      }
      tmp++;
    }
    cit++;
  }

  return true;
}

bool grid::no_same_word() const
{
  std::list<word*>::const_iterator cit = getSearched().begin();
  while(cit != getSearched().end()) {
    std::list<word*>::const_iterator tmp(cit);
    tmp++;
    while (tmp != getSearched().end()) {
      if (word::same_word(**cit, **tmp)) {
        return false;
      }
      tmp++;
    }
    cit++;
  }

  return true;
}

bool grid::no_invalid_words() const
{
  std::list<word*>::const_iterator cit = getSearched().begin();
  while(cit != getSearched().end()) {
    // Iterate over the path of words
    unsigned int length = 0;

    if ((*cit)->position() == 0) {
      for (unsigned int i = (*cit)->start_x(); i <= (*cit)->end_x(); i++) {
        length = word_recursive(i, (*cit)->start_y() - 1, 1, -1) +
                 word_recursive(i, (*cit)->start_y() + 1, 1, 1) + 1;
      }
    } else {
      for (unsigned int i = (*cit)->start_y(); i <= (*cit)->end_y(); i++) {
        length = word_recursive((*cit)->start_x() - 1, i, 0, -1) +
                 word_recursive((*cit)->start_x() + 1, i, 0, +1) + 1;
      }
    }

    // Single word is OK
    if (length != 1){
      if (length < 3) {
        return false;
      } else if (!is_constraints(length)) {
        return false;
      }
    }
    cit++;
  }

  return true;
}

// Offset: proceed with different direction (1, -1)
unsigned int grid::word_recursive(unsigned int x,
                                      unsigned int y,
                                      int position,
                                      int offset) const
{
  char current = getChar(x, y);
  if (current && current != '#') {
    if (position == 0)
      return word_recursive(x + offset, y, position, offset) + 1;
    else
      return word_recursive(x, y + offset, position, offset) + 1;
  } else {
    return 0;
  }
}

bool grid::is_constraints(unsigned int c) const {
  std::list<unsigned int>::const_iterator itr =
          std::find((*total_constraints).begin(), (*total_constraints).end(), c);
  return itr != (*total_constraints).end();
}

void grid::search_recursive(const Dictionary &dict, std::list<grid> &result) const {
  // First grid
  if (current_word != nullptr) {
    // Try validating current grid
    if (!is_valid(dict)) {
      // Wrong answer, exit...
      return;
    }
  }

  // Current grid is OK to go, push to words and remove the constraints
  if (constraints.size() != 0) {
    unsigned int current_con = constraints.front();
    // Find words matched constraints

    if (!search_word(current_con, dict, result)) {
      // Bad solution: unable to meet constraints
      // Do cleanup: This is the last node
      return;
    };
  }

  // Hey, this is the end/right answers
  result.push_back(*this);
}


void grid::found_recursive(unsigned int x,
                           unsigned int y,
                           unsigned int length,
                           const Dictionary &dict,
                           bool &flag,
                           std::list<grid> &result) const {
  // Current Letter
  if (isLegalIndex(x, y)) {
    // start char should be legal
    if ((*map)[y][x] != PLACEHOLDER_SYMBOL) {
      std::vector<std::string*> d = dict.get_word_by_length(length);
      // Check each of them
      for (unsigned int i = 0; i < d.size(); i++) {
        // Get Word in grid
        // Across?
        std::string c = getString(x, y, 0, length);
        // Down?
        std::string down = getString(x, y, 1, length);

        // New Branch
        if (c == (*d[i])) {
          flag = true;
          grid g = *this;
          g.getSearched().push_back(g.current_word);
          g.setCurrent(new word(x, x + length, y, y, d[i]));
          g.pop_const();
          g.search_recursive(dict, result);
        }

        if (down == (*d[i])) {
          flag = true;
          grid g = *this;
          g.getSearched().push_back(g.current_word);
          g.setCurrent(new word(x, x, y, y + length, d[i]));
          g.pop_const();
          g.search_recursive(dict, result);
        }
      }
    } // Not a legal character

    // Proceed with one letter
    found_recursive(x + 1, y, length, dict, flag, result);
  } else {
    // cross out of bound
    if (x >= col() && y < row()) {
      found_recursive(0, y + 1, length, dict, flag, result);
    } else if (y >= row()) {
      // The end of the grid
    }
  }
}
