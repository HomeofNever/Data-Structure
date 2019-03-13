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
    sort(const std::list<word*> &w, grid * grid2);

    // Setter
    void setFlags(bool solution_mode, bool count_mode, bool is_giant);

    // Entry
    void combination(std::list<solution*> &result) const;

    // Debug
    void print() const;

private:
    std::vector<unsigned int> length;
    std::vector<std::vector<word*>> words;
    grid * grid1 = nullptr;
    bool one_solution = false;
    bool count_only = false;
    bool giant = false;

    // Helper
    int found_length(unsigned int i) const;
    // Generate Solutions
    void n_choose_m(unsigned int offset,
                    unsigned int m,
                    const std::vector<word*> &ls,
                    std::vector<word*> &tmp,
                    std::list<std::list<word*>> &result) const;
    void mixed_solutions(const std::vector<std::list<std::list<word*>>> &all_chosen,
                         std::list<solution*> &s) const;
    void solution_recursive(unsigned int index,
                            const std::vector<std::list<word*>> &tmp,
                            const std::vector<std::list<std::list<word*>>> &all_chosen,
                            std::list<solution*> &s) const;
};


#endif //INC_7TH_SORT_H
