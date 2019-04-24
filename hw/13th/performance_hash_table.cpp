#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();

typedef std::unordered_map<std::string,int> hashtable_type;


void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR 
  hashtable_type ht(input_count);
  for (int i = 0; i < input_count; i++) {
    std::pair<hashtable_type::iterator, bool> res =
            ht.insert(std::pair<std::string, int>(input_data[i], 1));
    if (!res.second) {
      (res.first)->second++;
    }
  }

  if (operation == "sort") {
    output_count = 0;
    std::cerr << "Error: Operation does not support." << std::endl;
    return;
  } else if (operation == "remove_dups_same_order") {
    output_count = 0;
    for (int i = 0; i < input_count; i++) {
      hashtable_type::iterator itr = ht.find(input_data[i]);
      if (itr != ht.end() && itr->second != 0) {
        output_data[output_count] = itr->first;
        output_count++;
        itr->second = 0;
      }
    }
  } else if (operation == "remove_dups_any_order") {
    output_count = 0;
    for (hashtable_type::const_iterator itr = ht.begin(); itr != ht.end(); itr++) {
      output_data[output_count] = itr->first;
      output_count++;
    }
  } else if (operation == "mode") {
    int count = 0;
    std::string mode;
    for (hashtable_type::const_iterator itr = ht.begin(); itr != ht.end(); itr++) {
      if (itr->second >= count) {
        mode = itr->first;
        count = itr->second;
      }
    }

    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
