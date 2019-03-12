//
// Created by luox6 on 2019/3/10.
//

#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H

#include "grid.h"
#include <list>

class solution {
public:
    solution(const std::list<word*> &w,
             std::vector<unsigned int> * con): word_list(w) {};
    solution(const std::list<word*> &w): word_list(w) {};
    solution(const solution &solution): word_list(solution.word_list) {};

    bool is_valid(const grid &g, const Dictionary &d);
    bool is_giant_components() const;

    void print_map(std::ostream &output, const std::vector<std::vector<char>> &map) const;

private:
    std::list<word*> word_list;

    void generate_overlay(const std::vector<std::vector<char>> &map,
                          std::vector<std::vector<char>> &overlay) const;
    bool no_same_word() const;
    bool no_collapse() const;
    bool no_invalid_words() const;

    unsigned int word_recursive(unsigned int x,
                                unsigned int y,
                                int position,
                                int offset) const;
    void giant_recursive(unsigned int x,
                         unsigned int y,
                         grid &grid1) const;
};

#endif //INC_7TH_SOLUTION_H
