//
// Created by luox6 on 2019/3/10.
//

#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H

#include "grid.h"
#include <list>

class solution {
public:
    solution(const std::list<word*> &w): word_list(w) {};
    solution(const solution &solution): word_list(solution.word_list),
                                        map(solution.map) {};

    bool is_valid(const grid &g, const Dictionary &d);
    void print_map(std::ostream &output) const;

private:
    std::list<word*> word_list;
    grid map = grid();

    void generate_overlay(const grid &g);
    bool no_same_word() const;
    bool no_collapse() const;
};

#endif //INC_7TH_SOLUTION_H
