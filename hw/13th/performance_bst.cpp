#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();
typedef std::map<std::string,int> bst_type;

// Read Data into map
void readData(const std::string* input_data, int input_count, bst_type &mp) {
  for (int i = 0; i < input_count; i++) {
    std::pair<bst_type::iterator, bool> res =
            mp.insert(std::pair<std::string, int>(input_data[i], 1));
    if (!res.second) {
      (res.first)->second++;
    }
  }
}

void bst_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  bst_type mp;
  // Don't read data at first, unless operation is given.
  if (operation == "sort") {
    readData(input_data, input_count, mp);
    output_count = 0;
    for (bst_type::const_iterator i = mp.begin(); i != mp.end(); i++) {
      for (int j = 0; j < i->second; j++) {
        output_data[output_count] = i->first;
        output_count++;
      }
    }
  } else if (operation == "remove_dups_same_order") {
    output_count = 0;
    for (int i = 0; i < input_count; i++) {
      // Iterate and insert
      // Failed means we have added, skipped
      std::pair<bst_type::iterator, bool> res = mp.insert(std::pair<std::string, int>(input_data[i], 1));
      if (res.second) {
        output_data[output_count] = input_data[i];
        output_count++;
      }
    }
  } else if (operation == "remove_dups_any_order") {
    readData(input_data, input_count, mp);
    output_count = 0;
    for (bst_type::iterator itr = mp.begin(); itr != mp.end(); itr++) {
      output_data[output_count] = itr->first;
      output_count++;
    }
  } else if (operation == "mode") {
    readData(input_data, input_count, mp);
    int count = 0;
    std::string mode;
    for (bst_type::iterator itr = mp.begin(); itr != mp.end(); itr++) {
      if (itr->second >= count) {
        count = itr->second;
        mode = itr->first;
      }
    }

    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
