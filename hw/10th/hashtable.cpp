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
    if (i->first.empty()) {
      continue; // Jump Over Empty Space
    }

    unsigned int index = findIndex(i->first, new_table);
    new_table[index] = *i;
  }

  table = new_table;
}

// Find location of a given query should be by Given HashTable
unsigned int hashtable::findIndex(const std::string &str, const TABLE_TYPE &table) {
  unsigned int hash = query::getHash(str);
  unsigned int index = hash % table.size();

  if (table[index].first.empty()) {
    // No found, but it is the place
    return index;
  } else {
    while (true) {
      while (is_legal_index(index, table) &&
             ((!(table[index].first == str)) &&
              (!table[index].first.empty()))) {
        index++;
      }

      if (is_legal_index(index, table)) {
        return index;
      } else {
        // Reach the end, restart from 0
        index = 0;
      }
    }
  }
}

// Driver Function
unsigned int hashtable::findIndex(const std::string &str) const {
  return findIndex(str, table);
}