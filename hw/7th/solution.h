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
             std::vector<unsigned int> * con): word_list(w), constraints(con) {};
    solution(const solution &solution): word_list(solution.word_list),
                                        map(solution.map) {};

    bool is_valid(const grid &g, const Dictionary &d);
    void print_map(std::ostream &output) const;

private:
    std::list<word*> word_list;
    std::vector<unsigned int> * constraints;
    grid map = grid();

    void generate_overlay(const grid &g);
    bool no_same_word() const;
    bool no_collapse() const;
    bool no_invalid_words() const;

    bool is_constraints(unsigned int c) const;

    unsigned int word_recursive(unsigned int x,
                                unsigned int y,
                                int position,
                                int offset) const;
};

#endif //INC_7TH_SOLUTION_H
