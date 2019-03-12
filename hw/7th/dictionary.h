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
    ~Dictionary(){ clear(); }

    unsigned int size() const { return list.size(); }
    const std::vector<std::string*> & get_word_by_length(unsigned int i) const;

    void print() const;
    bool search(std::string &str) const;

private:
    std::vector<std::string*> list;
    std::vector<unsigned int> length;
    std::vector<std::vector<std::string*>> words;

    int length_index(unsigned int i) const;
    void clear();

    void lengths();
};


#endif //INC_7TH_DICTIONARY_H
