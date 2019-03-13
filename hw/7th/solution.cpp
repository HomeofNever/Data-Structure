//
// Created by luox6 on 2019/3/10.
//

#include "solution.h"
#include <algorithm>
#include <iostream>

bool solution::is_valid(const std::list<word *> &word_list, grid *g) {
  return no_same_word(word_list) && no_collapse(word_list) && special_begin_end(word_list, g);
}


bool solution::is_valid_last(const std::list<word *> &word_list, grid *g, bool giant) {
  if (no_collapse(word_list) && special_begin_end(word_list, g) && no_invalid_words(word_list, g)) {
    // std::cout << "Reach end" << std::endl;
    if (giant) {
      return is_giant_components(word_list);
    }
    return true;
  }

  return false;
}


bool solution::no_collapse(const std::list<word *> &word_list) {
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    std::list<word *>::const_iterator tmp(cit);
    tmp++;
    while (tmp != word_list.end()) {
      if (word::collapse(**cit, **tmp)) {
        return false;
      }
      tmp++;
    }
    cit++;
  }

  return true;
}

bool solution::no_same_word(const std::list<word *> &word_list) {
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    std::list<word *>::const_iterator tmp(cit);
    tmp++;
    while (tmp != word_list.end()) {
      if (word::same_word(**cit, **tmp)) {
        return false;
      }
      tmp++;
    }
    cit++;
  }

  return true;
}

bool solution::no_invalid_words(const std::list<word *> &word_list, grid *g) {
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    // Foreach in the middle, no side by side unless different position.
    if ((*cit)->position() == 0) {
      for (unsigned int i = (*cit)->start_x(); i <= (*cit)->end_x(); i++) {
        if (!surrounding(i, (*cit)->start_y(), (*cit)->position(), word_list, g)) {
          return false;
        }
      }
    } else {
      for (unsigned int i = (*cit)->start_y(); i <= (*cit)->end_y(); i++) {
        if (!surrounding((*cit)->start_x(), i, (*cit)->position(), word_list, g)) {
          return false;
        }
      }
    }
    cit++;
  }

  return true;
}

bool solution::special_begin_end(const std::list<word *> &word_list,
                                 grid *g) {
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    // After beginning/ending: no word allowed
    std::list<word *> special;
    unsigned _x, _y;
    if ((*cit)->position() == 0) {
      // Left
      _y = (*cit)->start_y();
      _x = (*cit)->start_x() - 1;
      num_of_words(_x, _y, special, word_list, g);

      // Right
      _x = (*cit)->end_x() + 1;
      num_of_words(_x, _y, special, word_list, g);
    } else {
      // Top
      _y = (*cit)->start_y() - 1;
      _x = (*cit)->start_x();
      num_of_words(_x, _y, special, word_list, g);

      // Down
      _y = (*cit)->end_y() + 1;
      num_of_words(_x, _y, special, word_list, g);
    }

    if (!special.empty()) {
      return false;
    }
    cit++;
  }

  return true;
}

bool solution::surrounding(unsigned int x, unsigned int y, int position,
                           const std::list<word *> &word_list,
                           grid *g) {
  std::list<word *> checks;
  unsigned int _x, _y;
  if (position == 0) {
    // Up
    _y = y - 1;
    _x = x;
    num_of_words(_x, _y, checks, word_list, g);
    if (!position_secured(position, checks)) {
      return false;
    }

    // Down
    checks = {};
    _y = y + 1;
    num_of_words(_x, _y, checks, word_list, g);
    if (!position_secured(position, checks)) {
      return false;
    }
  } else {
    // Left
    _y = y;
    _x = x - 1;
    num_of_words(_x, _y, checks, word_list, g);
    if (!position_secured(position, checks)) {
      return false;
    }

    // Right
    checks = {};
    _x = x + 1;
    num_of_words(_x, _y, checks, word_list, g);
    if (!position_secured(position, checks)) {
      return false;
    }
  }

  return true;
}

bool solution::position_secured(int position, const std::list<word *> &word_list) {
  std::list<word *>::const_iterator itr = word_list.begin();
  bool across = false;
  bool down = false;

  while (itr != word_list.end()) {
    if ((*itr)->position() == 0) {
      across = true;
    } else if ((*itr)->position() == 1) {
      down = true;
    }
    itr++;
  }

  itr = word_list.begin();
  while (itr != word_list.end()) {
    if ((*itr)->position() == position) {
      if (!(across && down)) {
        return false;
      }
    }
    itr++;
  }

  return true;
}


void solution::num_of_words(unsigned int x, unsigned int y,
                            std::list<word *> &w,
                            const std::list<word *> &word_list,
                            grid *g) {
  if (g->isLegalIndex(x, y)) {
    std::list<word *>::const_iterator cit = word_list.begin();
    while (cit != word_list.end()) {
      // Iterate over the words
      if ((*cit)->is_between(x, y)) {
        w.push_back(*cit);
      }
      cit++;
    }
  }
}


bool solution::is_giant_components(const std::list<word *> &word_list) {
  // Keep a record
  std::list<std::string> remain;
  giant_recursive(word_list.front(), remain, word_list);
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    if (std::find(remain.begin(), remain.end(), (*cit)->getWord()) == remain.end()) {
      return false;
    };
    cit++;
  }

  return true;
}

void solution::giant_recursive(word *current_word,
                               std::list<std::string> &words,
                               const std::list<word *> &word_list) {
  if (std::find(words.begin(), words.end(), current_word->getWord()) == words.end()) {
    words.push_back(current_word->getWord());
    if (current_word->position() == 0) {
      for (unsigned int i = current_word->start_x(); i <= current_word->end_x(); i++) {
        std::list<word *>::const_iterator cit = word_list.begin();
        while (cit != word_list.end()) {
          if ((*cit)->is_between(i, current_word->start_y())) {
            giant_recursive(*cit, words, word_list);
          };
          cit++;
        }
      }
    } else {
      for (unsigned int i = current_word->start_y(); i <= current_word->end_y(); i++) {
        std::list<word *>::const_iterator cit = word_list.begin();
        while (cit != word_list.end()) {
          if ((*cit)->is_between(current_word->start_x(), i)) {
            giant_recursive(*cit, words, word_list);
          };
          cit++;
        }
      }
    }
  }
}

void solution::generate_overlay(std::vector<std::vector<char>> &overlay) const {
  overlay = std::vector<std::vector<char>>(grid1->row(), std::vector<char>(grid1->col(), '#'));
  for (std::list<word *>::const_iterator i = word_list.begin(); i != word_list.end(); i++) {
    unsigned int x1 = (*i)->start_x();
    unsigned int x2 = (*i)->end_x();
    unsigned int y1 = (*i)->start_y();
    unsigned int y2 = (*i)->end_y();

    if (y1 == y2) {
      // x axis
      for (unsigned int j = x1; j <= x2; j++) {
        overlay[y1][j] = (*i)->getWord()[j - x1];
      }
    } else {
      // y axis
      for (unsigned int j = y1; j <= y2; j++) {
        overlay[j][x1] = (*i)->getWord()[j - y1];
      }
    }
  }
}