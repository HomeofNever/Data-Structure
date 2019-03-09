//
// Created by luox6 on 2019/3/8.
//

#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H


#include <vector>
#include "grid.h"

class solution {
public:
    solution(
            const std::list<std::vector<unsigned int>> &p,
            const std::list<std::string> &w);

private:

    std::list<std::vector<unsigned int>> path;
    std::list<std::string> found_words;
};


#endif //INC_7TH_SOLUTION_H
