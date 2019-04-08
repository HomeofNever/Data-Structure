//
// Created by luox6 on 2019/4/7.
//

#include <cstring>
#include <iostream>
#include <algorithm>
#include "query.h"

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
const unsigned int SEED = 1315423911;

query::query(std::string &l) {
  if (!l.empty()) {
    str = l;
    // doHash();
  } else {
    std::cerr << "Get Empty String as Query!" << std::endl;
  }
}

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

void query::getQueryWithoutList(movie *m, std::vector<std::string> &ls) {
  for (int i = 0; i < POSSIBLE_COMBINATION.size(); i++) {
    std::string tmp;
    insert(POSSIBLE_COMBINATION[i][0], tmp, m->title);
    insert(POSSIBLE_COMBINATION[i][1], tmp, m->yearOfRelease);
    insert(POSSIBLE_COMBINATION[i][2], tmp, m->length);
    ls.push_back(tmp);
  }
}

void query::getQueryOfLists(movie *m, std::vector<std::string> &ls) {
  std::string genre, actor, role;
  appendList(m->genreList, genre);
  appendList(m->actorList, actor);
  appendList(m->roleList, role);

  for (int i = 0; i < POSSIBLE_COMBINATION.size(); i++) {
    std::string tmp;
    insert(POSSIBLE_COMBINATION[i][0], tmp, genre);
    insert(POSSIBLE_COMBINATION[i][1], tmp, actor);
    insert(POSSIBLE_COMBINATION[i][2], tmp, role);
    ls.push_back(tmp);
  }
}

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

void query::appendList(const listType &list, std::string &str) {
  str = "";
  str += std::to_string(list.size());
  for (listType::const_iterator i = list.begin(); i != list.end(); i++) {
    str += *i;
  }
}

void query::insert(int s, std::string &str, std::string &field) {
  if (s) {
    str += field;
  } else {
    str += UNKNOWN_LIST_FIELD;
  }
  str += HASH_SEPARATOR;
}
