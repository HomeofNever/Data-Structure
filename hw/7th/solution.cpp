//
// Created by luox6 on 2019/3/8.
//

#include <iostream>
#include "solution.h"

solution::solution(const std::list<std::vector<unsigned int>> &p,
                   const std::list<std::string> &w,
                   unsigned int row1,
                   unsigned int col1) {
  path = p;
  found_words = w;
  row = row1;
  col = col1;
}

void solution::print() const
{
  std::cout << "words: ";
  for (std::list<std::string>::const_iterator i = found_words.begin();
       i != found_words.end();
       i++)
  {
    std::cout << *i << ' ';
  }

  std::cout << std::endl;

  std::cout << "Paths: ";
  for (std::list<std::vector<unsigned int>>::const_iterator i = path.begin(); i != path.end(); i++)
  {
    std::cout << '(' << (*i)[0] << ", " << (*i)[1] << " - (" << (*i)[2] << ", " << (*i)[3] << ')' << std::endl;
  }
}

void solution::print_map(const std::vector<std::vector<char>> &map) const
{
  std::vector<std::vector<bool>>overlay = std::vector<std::vector<bool>>(row, std::vector<bool>(col, false));

  for (std::list<std::vector<unsigned int>>::const_iterator i = path.begin(); i != path.end(); i++)
  {
    unsigned int x1 = (*i)[0];
    unsigned int x2 = (*i)[2];
    unsigned int y1 = (*i)[1];
    unsigned int y2 = (*i)[3];

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

  for (unsigned int i = 0; i < map.size(); i++) {
    for (unsigned int j = 0; j < map[i].size(); j++) {
      if (overlay[i][j])
      {
        std::cout << map[i][j];
      } else {
        std::cout << '#';
      }
    }
    std::cout << std::endl;
  }
}
