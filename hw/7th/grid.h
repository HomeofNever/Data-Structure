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
    grid(std::vector<std::vector<char>> * m, std::list<unsigned int> * c);;
    grid(const grid &grid1);
    ~grid(){ clear(); }

    grid& operator=(const grid &grid1);

    unsigned int row() const { return map->size(); }
    unsigned int col() const { return row() > 0 ? (*map)[0].size() : 0; }
    unsigned int num_const() const { return constraints.size(); };

    const std::vector<std::vector<char>> * getMap() const { return map; }
    const std::list<unsigned int> &getConstraints() const { return constraints; };
    std::list<word*> getSearched() const { return searched; };
    char getChar(unsigned int x, unsigned int y) const;
    std::string getString(unsigned int x,
                          unsigned int y,
                          int type,
                          unsigned int length) const;

    void setCurrent(word * w) { current_word = w; };
    void pop_const() { constraints.pop_front(); }

    bool is_valid(const Dictionary &d) const;

    bool isLegalIndex(unsigned int x, unsigned int y) const { return x < col() && y < row(); };
    bool isAllBlocked() const;
    bool is_constraints(unsigned int c) const;


    void print() const;

private:
    std::vector<std::vector<char>> * map;
    std::list<unsigned int> * total_constraints;
    std::list<unsigned int> constraints;
    std::list<word*> searched;
    word * current_word = nullptr;

    void clear();
    void copy(const grid &grid1);
    // void setPoint(unsigned int x, unsigned int y, char z) { if (isLegalIndex(x, y)) map[y][x] = z;}
    bool search_word(unsigned int l,
                     const Dictionary &dict,
                     std::list<grid> &result) const;
    void found_recursive(unsigned int x,
                         unsigned int y,
                         unsigned int length,
                         const Dictionary &dict,
                         bool &flag,
                         std::list<grid> &result) const;
    void search_recursive(const Dictionary &dict,
                          std::list<grid> &result) const;
    unsigned int word_recursive(unsigned int x,
                                unsigned int y,
                                int position,
                                int offset) const;

    bool no_same_word() const;
    bool no_collapse() const;
    bool no_invalid_words() const;

    void generate_overlay();
};


#endif //INC_7TH_GRID_H
