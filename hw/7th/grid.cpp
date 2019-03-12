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
           std::list<unsigned int> *c) : map(m), total_constraints(c) {
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
  searched.clear();
  if (current_word != nullptr) {
    delete current_word;
  }
}



void grid::clearWords() {
  std::list<word*>::const_iterator i = searched.begin();
  while(i != searched.end()) {
    delete *i;
    i++;
  }
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

grid::grid(const grid &grid1) { copy(grid1); }

void grid::copy(const grid &grid1) {
  map = grid1.map;
  total_constraints = grid1.total_constraints;
  constraints = grid1.constraints;
  searched = grid1.searched;
  // No Copy of current word
}

bool grid::is_valid(const Dictionary &d) const {
  return no_same_word() && no_collapse() && no_invalid_words();
}

bool grid::no_collapse() const {
  std::list<word *>::const_iterator cit = searched.begin();
  while (cit != searched.end()) {
    if (word::collapse(**cit, *current_word)) {
      return false;
    }
    cit++;
  }

  return true;
}

bool grid::no_same_word() const {
  std::list<word *>::const_iterator cit = searched.begin();
  while (cit != searched.end()) {
    if (word::same_word(**cit, *current_word)) {
      return false;
    }
    cit++;
  }

  return true;
}

bool grid::no_invalid_words() const {
  // Iterate over current
  if (special_begin_end()) {
    // Foreach in the middle, no side by side unless different position.
    if (current_word->position() == 0) {
      for (unsigned int i = current_word->start_x(); i <= current_word->end_x(); i++) {
        if (!surrounding(i, current_word->start_y(), current_word->position())) {
          return false;
        }
      }
      return true;
    } else {
      for (unsigned int i = current_word->start_y(); i <= current_word->end_y(); i++) {
        if (!surrounding(current_word->start_x(), i, current_word->position())) {
          return false;
        }
      }
      return true;
    }
  }

  return false;
}

bool grid::is_constraints(unsigned int c) const {
  std::list<unsigned int>::const_iterator itr =
          std::find((*total_constraints).begin(), (*total_constraints).end(), c);
  return itr != (*total_constraints).end();
}


bool grid::search_word(unsigned int l,
                       const Dictionary &dict,
                       std::list<grid> &result) {
  // If found the word, create a new grid and put that word into current, and return true
  bool flag = false;
  found_recursive(0, 0, l, dict, flag, result);
  // If no found, return false

  keep_current = flag;
  return flag;
}


bool grid::search_recursive(const Dictionary &dict, std::list<grid> &result) {
  // First grid
  if (current_word != nullptr) {
    // Try validating current grid
    if (!is_valid(dict)) {
      // Wrong answer, exit...
      return false;
    }
  }

  // Current grid is OK to go, push to words and remove the constraints
  if (!constraints.empty()) {
    unsigned int current_con = constraints.front();
    // Find words matched constraints

    if (!search_word(current_con, dict, result)) {
      // Bad solution: unable to meet constraints
      // Do cleanup: This is the last node
      return false;
    };
  }

  // Hey, this is the end/right answers
  result.push_back(*this);

  return true;
}


void grid::found_recursive(unsigned int x,
                           unsigned int y,
                           unsigned int length,
                           const Dictionary &dict,
                           bool &flag,
                           std::list<grid> &result) {
  // Current Letter
  if (isLegalIndex(x, y)) {
    // start char should be legal
    if ((*map)[y][x] != PLACEHOLDER_SYMBOL) {
      std::vector<std::string *> d = dict.get_word_by_length(length);
      // Check each of them
      for (unsigned int i = 0; i < d.size(); i++) {
        // Get Word in grid
        // Across?
        std::string c = getString(x, y, 0, length);
        // Down?
        std::string down = getString(x, y, 1, length);

        bool condition = false;
        // New Branch
        if (c == (*d[i])) {
          grid g = *this;
          g.getSearched().push_back(g.current_word);
          g.setCurrent(new word(x, x + length, y, y, d[i]));
          g.pop_const();
          condition = g.search_recursive(dict, result);
        }

        if (down == (*d[i])) {
          grid g = *this;
          g.getSearched().push_back(g.current_word);
          g.setCurrent(new word(x, x, y, y + length, d[i]));
          g.pop_const();
          condition = g.search_recursive(dict, result);
        }

        flag  = condition;
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

void grid::num_of_words(int x, int y, std::list<word *> &w) const {
  if (isLegalIndex(x, y)) {
    std::list<word *>::const_iterator cit = searched.begin();
    while (cit != searched.end()) {
      // Iterate over the words
      if ((*cit)->is_between(x, y)) {
        w.push_back(*cit);
      }
    }
  }
}

bool grid::surrounding(unsigned int x, unsigned int y, int position) const {
  int _x, _y;
  std::list<word *> checks;
  if (position == 0) {
    // Up
    _y = (int) y - 1;
    _x = (int) x;
    num_of_words(_x, _y, checks);

    // Down
    _y = (int) y + 1;
    num_of_words(_x, _y, checks);
  } else {
    // Left
    _y = (int) y;
    _x = (int) x - 1;
    num_of_words(_x, _y, checks);

    // Right
    _y = (int) y;
    _x = (int) x + 1;
    num_of_words(_x, _y, checks);
  }

  std::list<word *>::const_iterator itr = checks.begin();

  while (itr != checks.end()) {
    if ((*itr)->position() == position) {
      return false;
    }
  }

  return true;
}

bool grid::special_begin_end() const {
  // After beginning/ending: no word allowed
  std::list<word *> special;
  if (current_word->position() == 0) {
    // Left
    int _y = (int) current_word->start_y();
    int _x = (int) current_word->start_x() - 1;
    num_of_words(_x, _y, special);

    // Right
    _x = (int) current_word->end_x() + 1;
    num_of_words(_x, _y, special);
  } else {
    // Top
    int _y = (int) current_word->start_y() - 1;
    int _x = (int) current_word->start_x();
    num_of_words(_x, _y, special);

    // Down
    _y = (int) current_word->end_y() + 1;
    num_of_words(_x, _y, special);
  }

  return special.empty();
}

void grid::generate_overlay(std::vector<std::vector<char>> &result) const {
  result = std::vector<std::vector<char>>(row(), std::vector<char>(col(), '#'));

  for (std::list<word *>::const_iterator i = searched.begin(); i != searched.end(); i++) {
    overlay_by_words(*i, result);
  }

  overlay_by_words(current_word, result);
}

void grid::overlay_by_words(word *i, std::vector<std::vector<char>> &result)
{
  unsigned int x1 = i->start_x();
  unsigned int x2 = i->end_x();
  unsigned int y1 = i->start_y();
  unsigned int y2 = i->end_y();

  if (y1 == y2) {
    // x axis
    for (unsigned int j = x1; j <= x2; j++) {
      result[y1][j] = (*i->getWord())[j - x1];
    }
  } else {
    // y axis
    for (unsigned int j = y1; j <= y2; j++) {
      result[j][x1] = (*i->getWord())[j - y1];
    }
  }
}

void grid::run(const Dictionary &dict, std::list<grid> &result) {
  if (search_recursive(dict, result)) {
    keep_current = true;
  }
}
