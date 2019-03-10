//
// Created by luox6 on 2019/3/1.
//

#ifndef INC_7TH_GRID_H
#define INC_7TH_GRID_H


#include <fstream>
#include <vector>
#include <list>
#include "dictionary.h"
#include "sort.h"
#include "word.h"

class grid {
public:
    grid(std::ifstream &file);
    grid(const grid &grid1): map(grid1.map), constraints(grid1.constraints) {};

    unsigned int row() const { return map.size(); }
    unsigned int col() const { return row() > 0 ? map[0].size() : 0;}
    unsigned int num_const() const { return constraints.size(); };

    const std::vector<std::vector<char>> & getMap() const { return map; }

    char getChar(unsigned int x, unsigned int y) const { if (isLegalIndex(x, y)) { return map[y][x]; } return '\0';};
    std::string getString(unsigned int x, unsigned int y, int type, unsigned int length) const;

    std::list<word> search_word(Dictionary& dict) const;

    bool isLegalIndex(unsigned int x, unsigned int y) const { return x < col() && y < row(); };

    void print() const;
private:
    std::vector<std::vector<char>> map;
    std::list<unsigned int> constraints;

    void search_recursive(unsigned int x,
                          unsigned int y,
                          Dictionary &dict,
                          std::list<word> &result) const;
};


#endif //INC_7TH_GRID_H
