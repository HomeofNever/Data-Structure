//
// Created by luox6 on 2019/3/8.
//

#ifndef INC_7TH_SORT_H
#define INC_7TH_SORT_H

#include <list>
#include <string>
#include "solution.h"

class solution;

class sort {
public:
    sort(const std::list<word*> &w);
    sort(const sort &sort1): length(sort1.length), words(sort1.words) {};

    void setFlags(bool solution_mode, bool count_mode);;
    unsigned int combination(const grid &g, const Dictionary &d, std::list<solution*> &result) const;
    void print() const;

private:
    std::vector<unsigned int> length;
    std::vector<std::vector<word*>> words;
    bool one_solution = false;
    bool count_only = false;

    int found_length(unsigned int i) const;
    void n_choose_m(unsigned int offset,
                    unsigned int m,
                    const std::vector<word*> &ls,
                    std::vector<word*> &tmp,
                    std::vector<std::vector<word*>> &result) const;

    unsigned int mixed_solutions(const std::vector<std::vector<std::vector<word*>>> &all_chosen,
                         std::list<solution*> &s,
                         const grid &g,
                         const Dictionary &d) const;
};


#endif //INC_7TH_SORT_H
