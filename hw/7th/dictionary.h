//
// Created by luox6 on 2019/3/1.
//

#ifndef INC_7TH_DICTIONARY_H
#define INC_7TH_DICTIONARY_H


#include <fstream>
#include <vector>
#include <string>

class Dictionary {
public:
    Dictionary(std::ifstream &file);
    ~Dictionary(){}

    unsigned int size() const { return list.size(); }
    const std::vector<unsigned int> & getLength(char x) const;

    void print() const;
    bool search(std::string &str) const;

private:
    std::vector<std::string> list;
    std::vector<std::vector<unsigned int>> alphabet = std::vector<std::vector<unsigned int>>(26);

    void lengths();
};


#endif //INC_7TH_DICTIONARY_H
