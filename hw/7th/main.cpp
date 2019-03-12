#include <iostream>
#include <fstream>
#include <algorithm>
#include "dictionary.h"
#include "grid.h"
#include "sort.h"

const char NOTE_SYMBOL = '!';
const char CONSTRAINT_SYMBOL = '+';
const char PLACEHOLDER_SYMBOL = '#';

// ./a.out [dictionary file] [initial grid file] [solution mode] [output mode] [gc]
int main(int argc, char *argv[]) {
  // No matter what happened, 4 parameters are required.
  if (argc < 5)
  {
    std::cerr << "Program required at least 4 parameters to run." << std::endl;
    return 1;
  }

  // Open dict file
  std::ifstream in_dict_str(argv[1]);
  if (!in_dict_str.good())
  {
    std::cerr << "Can't open " << argv[1] << " to read." << std::endl;
    return 1;
  }

  Dictionary dict = Dictionary(in_dict_str);

  // Open Grid File
  std::ifstream in_grid_str(argv[2]);
  if (!in_grid_str.good())
  {
    std::cerr << "Can't open " << argv[2] << " to read." << std::endl;
    return 1;
  }

  // Parse map and constraints
  std::string str;
  std::vector<std::vector<char>> * map = new std::vector<std::vector<char>>();
  std::list<unsigned int> * constraints = new std::list<unsigned int>();
  while (in_grid_str >> str) {
    if (str.length() > 0) {
      // Should not be a note
      if (str[0] != NOTE_SYMBOL) {
        // A constraint
        if (str[0] == CONSTRAINT_SYMBOL) {
          constraints->push_back(std::stoi(str.erase(0, 1)));
        } else {
          std::vector<char> tmp(str.length(), PLACEHOLDER_SYMBOL);
          for (unsigned int i = 0; i < str.length(); i++) {
            tmp[i] = str[i];
          }
          map->push_back(tmp);
        }
      }
    }
  }

  std::sort(std::begin((*constraints)), std::end((*constraints)), std::greater<unsigned int>());

  // Get Solution mode
  // one_solution / all_solution
  std::string mode = argv[3];

  bool one_solution = mode == "one_solution";

  // Get Output mode
  // count_only / print_boards
  std::string output = argv[4];

  bool count_only = output == "count_only";

  std::string gc = "";
  // Maybe we have 5th？
  if (argc > 5)
  {
    gc = argv[5];
  }

  bool is_giant_components = gc == "gc";

  dict.print();
  grid g = grid(map, constraints);

//  g.search_word(dict);
//  std::list<word*> w = g.getSearched();
//
//  sort s(w);
//  s.setFlags(one_solution, count_only);
//  std::list<solution*> valid;
//  unsigned int count = s.combination(g, dict, valid);
//  std::list<solution*>::iterator iter;
//
//  // Extra credits
//  if (is_giant_components) {
//    iter = valid.begin();
//    while (iter != valid.end()) {
//      if (!(*iter)->is_giant_components()) {
//        delete (*iter);
//        count--;
//        iter = valid.erase(iter);
//      } else {
//        iter++;
//      }
//    }
//  }
//
//  std::cout << "Number of solution(s): " << count << std::endl;
//  if (!count_only){
//     iter = valid.begin();
//    while (iter != valid.end()) {
//      (*iter)->print_map(std::cout);
//      delete *iter;
//      iter++;
//    }
//  }



  delete map;
  delete constraints;

  return 0;
}