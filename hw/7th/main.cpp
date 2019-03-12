#include <iostream>
#include <fstream>
#include <algorithm>
#include "dictionary.h"
#include "grid.h"

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

  constraints->sort(std::greater<unsigned int>());

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

  std::list<std::vector<std::vector<char>>> result;
  g.run(dict, result);


  std::cout << "Number of solution(s): " << result.size() << std::endl;
  if (!count_only){
    std::list<std::vector<std::vector<char>>>::const_iterator iter = result.begin();
    while (iter != result.end()) {
      std::cout << "Board:" << std::endl;
      for (unsigned int i = 0; i < (*iter).size(); i++) {
        for (unsigned int j = 0; j < (*iter)[i].size(); j++) {
          std::cout << (*iter)[i][j];
        }
        std::cout << std::endl;
      }
      iter++;
    }
  }

  delete map;
  delete constraints;

  return 0;
}