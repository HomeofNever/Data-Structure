//
// Created by luox6 on 2019/4/6.
//

#include <iostream>
#include "hashtable.h"

// Get Movie of given query string
std::list<movie *> hashtable::getMovie(std::string &q) const {
  return table[findIndex(q)].second;
}

// Add an movie Object into hashtable
void hashtable::addItem(movie *m) {
  std::list<std::string *> tmp;
  query::getQueries(m, tmp);

  for (std::list<std::string *>::iterator i = tmp.begin(); i != tmp.end(); i++) {

    unsigned int index = findIndex(**i);
    // If this is a brand new query of the hashtable
    if (table[index].first.empty()) {
      table[index].first = **i;
      size_++;
    }

    table[index].second.push_back(m);

    delete *i;

    if (should_resize()) {
      resize();
    }
  }
}

// Resize table by doubling space and resize
void hashtable::resize() {
  unsigned int table_size = resize_size();
  TABLE_TYPE new_table = TABLE_TYPE(table_size);
  for (TABLE_TYPE::const_iterator i = table.begin(); i != table.end(); i++) {
    unsigned int hash = query::getHash(i->first);
    unsigned int index = hash % table_size;

    if (new_table[index].first.empty()) {
      new_table[index] = *i;
    } else {
      while (true) {
        while (index >= 0 &&
               index < table_size &&
               !new_table[index].first.empty()) {
          index++;
        }

        if (index >= 0 && index < table_size) {
          new_table[index] = *i;
          break;
        } else {
          // Reach the end, restart from 0
          index = 0;
        }
      }
    }
  }

  table = new_table;
}

// Find location of a given query should be
unsigned int hashtable::findIndex(std::string &str) const {
  unsigned int hash = query::getHash(str);
  unsigned int index = hash % table.size();

  if (table[index].first.empty()) {
    // No found, but it is the place
    return index;
  } else {
    while (true) {
      while (is_legal_index(index) &&
             ((!(table[index].first == str)) &&
              (!table[index].first.empty()))) {
        index++;
      }

      if (is_legal_index(index)) {
        return index;
      } else {
        // Reach the end, restart from 0
        index = 0;
      }
    }
  }
}