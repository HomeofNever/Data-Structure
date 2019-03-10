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

void solution::print_map(std::ostream &output) const
{
  output << "Board:" << std::endl;
  for (unsigned int i = 0; i < map.getMap().size(); i++) {
    for (unsigned int j = 0; j < map.getMap()[i].size(); j++) {
      output << map.getMap()[i][j];
    }
    output << std::endl;
  }
}

void solution::generate_overlay(const grid &g)
{
  std::vector<std::vector<bool>>overlay = std::vector<std::vector<bool>>(g.row(), std::vector<bool>(g.col(), false));
  map = g;

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
        overlay[y1][j] = true;
      }
    } else {
      // y axis
      for (unsigned int j = y1; j <= y2; j++)
      {
        overlay[j][x1] = true;
      }
    }
  }

  for (unsigned int i = 0; i < g.getMap().size(); i++) {
    for (unsigned int j = 0; j < g.getMap()[i].size(); j++) {
      if (overlay[i][j])
      {
        // Keep the same
      } else {
        map.setPoint(j, i, '#');
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
    if ((*cit)->position() == 0) {
      for (int i = (*cit)->start_x(); i <= (*cit)->end_x(); i++) {
        unsigned int length = word_recursive(i, (*cit)->start_y(), 1, 1) +
                          word_recursive(i, (*cit)->start_y(), 1, -1);
        if (length < 3) {
          return false;
        } else if (!is_constraints(length)) {
          return false;
        }
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

bool solution::is_constraints(unsigned int c) const
{
  for (int i = 0; i < constraints->size(); i++)
  {
    if ((*constraints)[i] == c)
    {
      return true;
    }
  }

  return false;
}
