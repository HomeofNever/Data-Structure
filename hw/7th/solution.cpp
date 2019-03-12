//
// Created by luox6 on 2019/3/10.
//

#include "solution.h"

bool solution::is_valid(const grid &g, const Dictionary &d)
{
  // Basic check
  if (no_same_word() && no_collapse()) {
    // Overlay the map
    generate_overlay(g);

    // Check current grid: should only same number of word found
    map.search_word(d);
    if (map.getSearched().size() == word_list.size()) {
      // It should be the solution
      if (no_invalid_words()) {
        return true;
      }
    }
  }

  return false;
}

void solution::print_map(std::ostream &output, const std::vector<std::vector<char>> &map) const
{
  output << "Board:" << std::endl;
  std::vector<std::vector<char>> overlay;
  generate_overlay(map, overlay);
  for (unsigned int i = 0; i < overlay.size(); i++) {
    for (unsigned int j = 0; j < overlay[i].size(); j++) {
      output << overlay[i][j];
    }
    output << std::endl;
  }
}

void solution::generate_overlay(const std::vector<std::vector<char>> &map,
                                std::vector<std::vector<char>> &overlay) const
{
   overlay = std::vector<std::vector<char>>(map.size(), std::vector<char>(map[0].size(), '#'));

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
}

bool solution::no_collapse() const
{
  std::list<word*>::const_iterator cit = word_list.begin();
  while(cit != word_list.end()) {
    std::list<word*>::const_iterator tmp(cit);
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

bool solution::no_same_word() const
{
  std::list<word*>::const_iterator cit = word_list.begin();
  while(cit != word_list.end()) {
    std::list<word*>::const_iterator tmp(cit);
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

bool solution::no_invalid_words() const
{
  std::list<word*>::const_iterator cit = word_list.begin();
  while(cit != word_list.end()) {
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

    cit++;
  }

  return true;
}

// Offset: different direction (1, -1)
unsigned int solution::word_recursive(unsigned int x,
                                      unsigned int y,
                                      int position,
                                      int offset) const
{
  char current = map.getChar(x, y);
  if (current && current != '#') {
    if (position == 0)
      return word_recursive(x + offset, y, position, offset) + 1;
    else
      return word_recursive(x, y + offset, position, offset) + 1;
  } else {
    return 0;
  }
}

bool solution::is_giant_components() const {
  grid m = map;

  giant_recursive(word_list.front()->start_x(), word_list.front()->start_y(), m);


  return m.isAllBlocked();
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