//
// Created by luox6 on 2019/3/1.
//

#ifndef INC_7TH_GRID_H
#define INC_7TH_GRID_H


#include <fstream>
#include <vector>
#include <list>
#include "dictionary.h"
#include "word.h"

class grid {
public:
    grid(){};
    grid(std::ifstream &file);
    grid(const grid &grid1) {copy(grid1.map, grid1.constraints);}

    grid& operator=(const grid &grid1);

    unsigned int row() const { return map.size(); }
    unsigned int col() const { return row() > 0 ? map[0].size() : 0; }
    unsigned int num_const() const { return constraints.size(); };

    const std::vector<std::vector<char>> &getMap() const { return map; }
    const std::list<unsigned int> &getConstraints() const { return constraints; };
    char getChar(unsigned int x, unsigned int y) const;;

    std::string getString(unsigned int x,
                          unsigned int y,
                          int type,
                          unsigned int length) const;
    bool isLegalIndex(unsigned int x, unsigned int y) const { return x < col() && y < row(); };

    std::list<word> search_word(const Dictionary &dict) const;

    friend class solution; // Allow Solution class to Overlay
    void print() const;

private:
    std::vector<std::vector<char>> map;
    std::list<unsigned int> constraints;

    void clear() { map.clear(); constraints.clear(); }
    void copy(const std::vector<std::vector<char>> &m,
              const std::list<unsigned int> &c) {map = m; constraints = c;}
    void setPoint(unsigned int x, unsigned int y, char z) { if (isLegalIndex(x, y)) map[y][x] = z;}
    void search_recursive(unsigned int x,
                          unsigned int y,
                          const Dictionary &dict,
                          std::list<word> &result) const;
};


#endif //INC_7TH_GRID_H
