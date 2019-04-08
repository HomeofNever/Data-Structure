//
// Created by luox6 on 2019/4/7.
//

#include <cstring>
#include <iostream>
#include <algorithm>
#include "query.h"

// (0..3)C3 All possible solutions
const std::vector<std::vector<int>> POSSIBLE_COMBINATION =
        std::vector<std::vector<int>>{
                {0, 0, 0},
                {1, 0, 0},
                {0, 1, 0},
                {0, 0, 1},
                {1, 1, 0},
                {1, 0, 1},
                {0, 1, 1},
                {1, 1, 1}
        };
// Seed for hash function
const unsigned int SEED = 1315423911;

// Hash Function str->int
unsigned int query::doHash(const std::string &str) {
  //  This implementation comes from
  //  http://www.partow.net/programming/hashfunctions/
  //
  //  This is a general-purpose, very good hash function for strings.
  unsigned int hash = SEED;
  for(unsigned int i = 0; i < str.length(); i++)
    hash ^= ((hash << 5) + str[i] + (hash >> 2));
  return hash;
}

// Generate Partial Query String of List fields
void query::getQueryWithoutList(movie *m, std::vector<std::string> &ls) {
  for (int i = 0; i < POSSIBLE_COMBINATION.size(); i++) {
    std::string tmp;
    insert(POSSIBLE_COMBINATION[i][0],
            tmp, m->title, UNKNOWN_SINGLE_FIELD);
    insert(POSSIBLE_COMBINATION[i][1],
            tmp, m->yearOfRelease, UNKNOWN_SINGLE_FIELD);
    insert(POSSIBLE_COMBINATION[i][2],
            tmp, m->length, UNKNOWN_SINGLE_FIELD);
    ls.push_back(tmp);
  }
}

// Generate all possible query strings
void query::getQueryOfLists(movie *m, std::vector<std::string> &ls) {
  std::string genre, actor, role;
  appendList(m->genreList, genre);
  appendList(m->actorList, actor);
  appendList(m->roleList, role);

  for (int i = 0; i < POSSIBLE_COMBINATION.size(); i++) {
    std::string tmp;
    insert(POSSIBLE_COMBINATION[i][0], tmp, genre, UNKNOWN_LIST_FIELD);
    insert(POSSIBLE_COMBINATION[i][1], tmp, actor, UNKNOWN_LIST_FIELD);
    insert(POSSIBLE_COMBINATION[i][2], tmp, role, UNKNOWN_LIST_FIELD);
    ls.push_back(tmp);
  }
}

// Generate all possible query string of single fields
void query::getQueries(movie *m, std::list<std::string*> &q) {
  std::vector<std::string> singleField, listField;
  getQueryWithoutList(m, singleField);
  getQueryOfLists(m, listField);

  for (int i = 0; i < singleField.size(); i++) {
    for (int j = 0; j < listField.size(); j++) {
      std::string tmp = singleField[i] + listField[j].substr(0, listField[j].size() - 1);
      std::string * new_str = new std::string(tmp);
      q.push_back(new_str);
    }
  }
}

// Turn list into string
void query::appendList(const listType &list, std::string &str) {
  str = "";
  str += std::to_string(list.size());
  for (listType::const_iterator i = list.begin(); i != list.end(); i++) {
    str += *i;
  }
}

// PlaceHolder or Actual Value Helper
void query::insert(int s, std::string &str,
                   const std::string &field,
                   const std::string &placeHolder) {
  if (s) {
    str += field;
  } else {
    str += placeHolder;
  }
  str += HASH_SEPARATOR;
}
