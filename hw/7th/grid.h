//
// Created by luox6 on 2019/3/1.
//

#ifndef INC_7TH_GRID_H
#define INC_7TH_GRID_H


#include <fstream>
#include <vector>
#include <list>
#include "dictionary.h"

class grid {
public:
    grid(std::ifstream &file);

    unsigned int row() const { return map.size(); }
    unsigned int col() const { return row() > 0 ? map[0].size() : 0;}
    unsigned int num_const() const { return constraints.size(); };
    char getChar(unsigned int x, unsigned int y) const { if (isLegalIndex(x, y)) { return map[y][x]; } return '\0';};
    std::string getString(unsigned int x, unsigned int y, int type, unsigned int length) const;
    unsigned int count_only(Dictionary &dict);
    void one_solution();

    bool isLegalIndex(unsigned int x, unsigned int y) const { return x < col() && y < row(); };

    void print() const;

private:
    std::vector<std::vector<char>> map;
    std::list<unsigned int> constraints;

    bool targetReached(std::list<std::string> words) const;
    void recursive(unsigned int x,
                  unsigned int y,
                  int state,
                  std::list<std::string> &words,
                  std::list<std::vector<unsigned int>> &path,
                  std::list<unsigned int> &con,
                  Dictionary &dict);
};


#endif //INC_7TH_GRID_H
