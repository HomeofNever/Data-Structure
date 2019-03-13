//
// Created by luox6 on 2019/3/10.
//

#include "solution.h"

bool solution::is_valid() const {
  return no_same_word() && no_collapse() && no_invalid_words();
}

void solution::print_map(std::ostream &output) const {
  output << "Board:" << std::endl;
  std::vector<std::vector<char>> overlay;
  generate_overlay(grid1->map, overlay);
  for (unsigned int i = 0; i < overlay.size(); i++) {
    for (unsigned int j = 0; j < overlay[i].size(); j++) {
      output << overlay[i][j];
    }
    output << std::endl;
  }
}

void solution::generate_overlay(const std::vector<std::vector<char>> &map,
                                std::vector<std::vector<char>> &overlay) const {
  overlay = std::vector<std::vector<char>>(map.size(), std::vector<char>(map[0].size(), '#'));

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

bool solution::no_collapse() const {
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

bool solution::no_same_word() const {
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

bool solution::no_invalid_words() const {
  std::list<word *>::const_iterator cit = word_list.begin();
  while (cit != word_list.end()) {
    if (special_begin_end(*cit)) {
      // Foreach in the middle, no side by side unless different position.
      if ((*cit)->position() == 0) {
        for (unsigned int i = (*cit)->start_x(); i <= (*cit)->end_x(); i++) {
          if (!surrounding(i, (*cit)->start_y(), (*cit)->position())) {
            return false;
          }
        }
      } else {
        for (unsigned int i = (*cit)->start_y(); i <= (*cit)->end_y(); i++) {
          if (!surrounding((*cit)->start_x(), i, (*cit)->position())) {
            return false;
          }
        }
      }
      cit++;
    } else {
      return false;
    }
  }

  return true;
}

bool solution::special_begin_end(word *current_word) const {
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

bool solution::surrounding(unsigned int x, unsigned int y, int position) const {
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
    _x = (int) x + 1;
    num_of_words(_x, _y, checks);
  }

  std::list<word *>::const_iterator itr = checks.begin();

  while (itr != checks.end()) {
    if ((*itr)->position() == position) {
      return false;
    }
    itr++;
  }

  return true;
}

void solution::num_of_words(int x, int y, std::list<word *> &w) const {
  if (grid1->isLegalIndex(x, y)) {
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


bool solution::is_giant_components() const {
  // giant_recursive(word_list.front()->start_x(), word_list.front()->start_y(), m);
}

void solution::giant_recursive(unsigned int x,
                               unsigned int y,
                               grid &grid1) const {
  if (grid1.getChar(x, y) && grid1.getChar(x, y) != '#') {
    grid1.setPoint(x, y, '#');
    giant_recursive(x + 1, y, grid1);
    giant_recursive(x, y + 1, grid1);
    giant_recursive(x - 1, y, grid1);
    giant_recursive(x, y - 1, grid1);
  }
}

