//
// Created by luox6 on 2019/4/6.
//

#ifndef INC_10TH_HASHTABLE_H
#define INC_10TH_HASHTABLE_H

#define TABLE_SIZE 200
#define OCCUPANCY 0.5

#include "movie.h"
#include "query.h"
#include <list>
#include <set>

typedef std::vector<std::pair<std::string, std::list<movie*>>> TABLE_TYPE;

class hashtable {
public:
    // Constructor
    hashtable(float o = OCCUPANCY, int table_size = TABLE_SIZE): occupancy(o) {
      table = TABLE_TYPE(table_size);
    };
    ~hashtable(){};

    // Accessor
    std::list<movie*> getMovie(std::string &q) const;

    // Mutator
    void addItem(movie *m);

private:
    TABLE_TYPE table;
    int size_ = 0;
    float occupancy = OCCUPANCY;

    void resize();

    unsigned int findIndex(const std::string &str) const;
    static unsigned int findIndex(const std::string &str, const TABLE_TYPE &table);

    // Helpers
    static bool is_legal_index(int i, const TABLE_TYPE &t) { return i >= 0 && i < t.size(); }
    bool is_legal_index(int i) const { return is_legal_index(i, table); }
    unsigned int table_size() const { return table.size(); }
    double ratio() const { return (float)size_ / (float)table_size(); }
    bool should_resize() const { return ratio() > occupancy; };
    unsigned resize_size() const { return table_size() * 2; }
};

#endif //INC_10TH_HASHTABLE_H
