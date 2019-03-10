//
// Created by luox6 on 2019/3/8.
//

#ifndef INC_7TH_SORT_H
#define INC_7TH_SORT_H

#include <list>
#include <string>
#include "word.h"
#include "solution.h"

class sort {
public:
    sort(const std::list<word> &w);
    
    std::list<solution> combination(std::list<unsigned int> &constraints) const;
    void print() const;

private:
    std::vector<unsigned int> length;
    std::vector<std::vector<word>> words;

    int found_length(unsigned int i) const;
};


#endif //INC_7TH_SORT_H
