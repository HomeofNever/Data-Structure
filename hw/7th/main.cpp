#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "grid.h"
#include "sort.h"

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

  grid * g = new grid(in_grid_str);

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

  g->search_word(dict);
  std::list<word*> w = g->getSearched();

  sort s(w, g);
  s.setFlags(one_solution, count_only);
  std::list<solution*> valid;
  s.combination(dict, valid);
  unsigned int count = valid.size();
  std::list<solution*>::iterator iter;

  // Extra credits
  if (is_giant_components) {
    iter = valid.begin();
    while (iter != valid.end()) {
      if (!(*iter)->is_giant_components()) {
        delete (*iter);
        count--;
        iter = valid.erase(iter);
      } else {
        iter++;
      }
    }
  }

  std::cout << "Number of solution(s): " << count << std::endl;
  if (!count_only){
     iter = valid.begin();
    while (iter != valid.end()) {
      (*iter)->print_map(std::cout);
      delete *iter;
      iter++;
    }
  }


  delete g;

  return 0;
}