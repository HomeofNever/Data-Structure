//
// Created by luox6 on 2019/3/1.
//

#include <iostream>
#include <list>
#include "grid.h"
#include "solution.h"

const char NOTE_SYMBOL = '!';
const char CONSTRAINT_SYMBOL = '+';
const char PLACEHOLDER_SYMBOL = '#';

bool ONE_SOLUTION = false;
bool STOP_FLAG = false;
bool COUNT_ONLY = false;
std::list<solution> result;


grid::grid(std::ifstream &file) {
  std::string str;
  while (file >> str) {
    if (str.length() > 0) {
      // Should not be a note
      if (str[0] != NOTE_SYMBOL) {
        // A constraint
        if (str[0] == CONSTRAINT_SYMBOL) {
          constraints.push_back(std::stoi(str.erase(0, 1)));
        } else {
          std::vector<char> tmp(str.length(), PLACEHOLDER_SYMBOL);
          for (unsigned int i = 0; i < str.length(); i++) {
            tmp[i] = str[i];
          }
          map.push_back(tmp);
        }
      }
    }
  }
}

void grid::print() const {
  std::cout << "Map: " << row() << " x " << col() << std::endl;
  std::cout << "Constraint: " << num_const() << std::endl;
  std::list<unsigned int>::const_iterator cb = constraints.begin();
  while (cb != constraints.end()) {
    std::cout << *cb << " ";
  }
  std::cout << std::endl;

  for (unsigned int i = 0; i < map.size(); i++) {
    for (unsigned int j = 0; j < map[i].size(); j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

std::string grid::getString(unsigned int x, unsigned int y, int type, unsigned int length) const {
  // Type 0: across, Type 1: Down
  std::string str;
  if (isLegalIndex(x, y)) {
    unsigned int end_x = x, end_y = y;
    if (type == 0) {
      end_x += length - 1;
    } else {
      end_y += length - 1;
    }

    if (isLegalIndex(end_x, end_y)) {
      if (type == 0) {
        for (unsigned int i = x; i <= end_x; i++) {
          if (map[y][i] != PLACEHOLDER_SYMBOL) {
            str.push_back(map[y][i]);
          } else {
            return std::string();
          }
        }
      } else {
        for (unsigned int i = y; i <= end_y; i++) {
          if (map[i][x] != PLACEHOLDER_SYMBOL) {
            str.push_back(map[i][x]);
          } else {
            return std::string();
          }
        }
      }
    }
  }

  return str;
}

bool grid::targetReached(std::list<std::string> words) const {
  if (words.size() == constraints.size()) {
    //@TODO
    std::list<std::string>::iterator wb = words.begin();
    while (wb != words.end()) {
      std::cout << *wb << " ";
      wb++;
    }
    std::cout << std::endl;

    std::list<unsigned int> c(constraints);
    std::list<unsigned int>::iterator cb = c.begin();
    while (cb != c.end()) {
      std::list<std::string>::iterator wb = words.begin();
      while (wb != words.end()) {
        if (*cb == (*wb).length()) {
          cb = c.erase(cb);
          wb = words.erase(wb);
          break;
        } else {
          wb++;
        }
      }
      cb++;
    }
    return c.size() == 0 && words.size() == 0;
  } else {
    return false;
  }
}

unsigned int grid::count_only(Dictionary &dict) {
  std::list<std::string> init(0);
  // State:
  // 0 cross, 1 down
  std::list<std::vector<unsigned int>> path;
  COUNT_ONLY = true;
  ONE_SOLUTION = false;
  STOP_FLAG = false;
  result = std::list<solution>();
  recursive(0, 0, 0, init, path, constraints, dict);

  return result.size();
}

unsigned int grid::all_solution(Dictionary &dict) {
  std::list<std::string> init(0);
  // State:
  // 0 cross, 1 down
  std::list<std::vector<unsigned int>> path;
  COUNT_ONLY = true;
  ONE_SOLUTION = false;
  STOP_FLAG = false;
  result = std::list<solution>();
  recursive(0, 0, 0, init, path, constraints, dict);

  return
}

void grid::recursive(unsigned int x,
                     unsigned int y,
                     int state,
                     std::list<std::string> &words,
                     std::list<std::vector<unsigned int>> &path,
                     std::list<unsigned int> &con,
                     Dictionary &dict) {
  if (STOP_FLAG)
  {
    return;
  }

  // Current Letter
  if (isLegalIndex(x, y)) {
    // The length of possible words
    std::list<unsigned int> origin_con(con);

    // start char should be legal
    if (getChar(x, y) != PLACEHOLDER_SYMBOL){
      std::vector<unsigned int> d = dict.getLength(getChar(x, y));

      // Check each of them
      for (unsigned int i = 0; i < d.size(); i++) {
        // Get Word in grid
        std::string w = getString(x, y, state, d[i]);

        if (!w.empty()) {
          if (dict.search(w)) {
            // Word found, is constraint?
            std::list<unsigned int>::iterator cb = con.begin();
            while (cb != con.end())
            {
              if (*cb == d[i])
              {
                // It is, continue
                con.erase(cb);
                std::list<std::string> next_word(words);
                std::list<std::vector<unsigned int>> next_path(path);

                next_word.push_back(w);

                // Path:
                // [ [x, y, end_x, end_y] ]
                std::vector<unsigned int> p(4, 0);
                p[0] = x;
                p[1] = y;
                p[2] = x;
                p[3] = y;
                if (state == 0) {
                  p[2] += d[i];
                } else {
                  p[3] += d[i];
                }

                next_path.push_back(p);

                // After a new word:
                // If Target?
                if (targetReached(next_word)) {
                  result.push_back(solution(next_path, next_word));
                  if (ONE_SOLUTION)
                  {
                    STOP_FLAG = true;
                  }

                  return;
                } else {
                  // Proceed with the word
                  if (state == 0) {
                    recursive(x + d[i], y, state, next_word, next_path, con, dict);
                  } else {
                    recursive(x, y + d[i], state, next_word, next_path, con, dict);
                  }
                }

                break;
              } else {
                cb++;
              }
            }
          }
        }
      }
    }

    // Proceed with one letter
    if (state == 0) {
      recursive(x + 1, y, state, words, path, origin_con, dict);
    } else {
      recursive(x, y + 1, state, words, path, origin_con, dict);
    }
  } else {

    if (state == 0) {
      // cross out of bound
      if (x >= col() && y < row()) {
        x = 0;
        y += 1;
        recursive(x, y, state, words, path, con, dict);
      } else if (y >= row()) {
        // The end of the cross, switch to down
        recursive(0, 0, 1, words, path, con, dict);
      }

    } else {
      if (y >= col() && x < row()) {
        // The end of the col, move next
        x += 1;
        y = 0;
        recursive(x, y, state, words, path, con, dict);
      } else if (x >= row()) {
        // That's the end of the story
        // std::cout << "Reach End" << std::endl;
      }
    }
  }
}