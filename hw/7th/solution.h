//
// Created by luox6 on 2019/3/8.
//

#ifndef INC_7TH_SOLUTION_H
#define INC_7TH_SOLUTION_H


#include <vector>
#include <list>
#include <string>

class solution {
public:
    solution(
            const std::list<std::vector<unsigned int>> &p,
            const std::list<std::string> &w,
            unsigned int row1,
            unsigned int col1);

    void print_map(const std::vector<std::vector<char>> &map) const;
    void print() const;

private:
    std::list<std::vector<unsigned int>> path;
    std::list<std::string> found_words;

    unsigned int row, col;
};


#endif //INC_7TH_SOLUTION_H
