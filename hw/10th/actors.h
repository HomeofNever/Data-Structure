//
// Created by luox6 on 2019/4/6.
//

#ifndef INC_10TH_ACTORS_H
#define INC_10TH_ACTORS_H

#include <string>
#include <map>
typedef std::map<std::string, std::string> ACTORS_TYPES;


class actors {
public:
    // Accessor
    std::string getActor(const std::string &id) const { return actors.find(id)->second; }

    // Mutator
    bool addActor(std::string &id, std::string &name) { return actors.insert(std::make_pair(id, name)).second; }

    // Debug
    void print() const;
private:
     ACTORS_TYPES actors;
};


#endif //INC_10TH_ACTORS_H
