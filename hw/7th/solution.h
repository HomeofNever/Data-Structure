//
// Created by luox6 on 2019/3/9.
//

#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H


#include "word.h"
#include <list>

class solution {
public:
    solution(const std::list<word> &w): words(w) {};

private:
    std::list<word> words;
};


#endif //INC_7TH_SOLUTION_H
