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
            grid * grid2): word_list(w), grid1(grid2) {};
    solution(const solution &solution): word_list(solution.word_list),
                                        grid1(solution.grid1) {};

    bool is_valid(const Dictionary &d) const;
    bool is_giant_components() const;

    void print_map(std::ostream &output) const;

private:
    std::list<word*> word_list;
    grid * grid1;

    void generate_overlay(const std::vector<std::vector<char>> &map,
                          std::vector<std::vector<char>> &overlay) const;
    bool no_same_word() const;
    bool no_collapse() const;
    bool no_invalid_words() const;

    bool special_begin_end(word * current_word) const;
    bool surrounding(unsigned int x, unsigned int y, int position) const;
    void num_of_words(int x, int y, std::list<word *> &w) const;

    void giant_recursive(unsigned int x,
                         unsigned int y,
                         grid &grid1) const;
};

#endif //INC_7TH_SOLUTION_H
