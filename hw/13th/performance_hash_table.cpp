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

void readData(const std::string* input_data, int input_count, hashtable_type &ht) {
  for (int i = 0; i < input_count; i++) {
    std::pair<hashtable_type::iterator, bool> res =
            ht.insert(std::pair<std::string, int>(input_data[i], 1));
    if (!res.second) {
      (res.first)->second++;
    }
  }
}

void hash_table_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your hash table like this:
  // std::unordered_set<std::string> ht(input_count);
  // OR 
  hashtable_type ht(input_count);
  // Don't init input at first
  if (operation == "sort") {
    output_count = 0;
    std::cerr << "Error: Operation does not support." << std::endl;
    return;
  } else if (operation == "remove_dups_same_order") {
    output_count = 0;
    for (int i = 0; i < input_count; i++) {
      // Iterate and insert
      // Failed means we have already added, skipped.
      std::pair<hashtable_type::iterator, bool> res =
              ht.insert(std::pair<std::string, int>(input_data[i], 1));
      if (res.second) {
        output_data[output_count] = input_data[i];
        output_count++;
      }
    }
  } else if (operation == "remove_dups_any_order") {
    readData(input_data, input_count, ht);
    output_count = 0;
    for (hashtable_type::const_iterator itr = ht.begin(); itr != ht.end(); itr++) {
      output_data[output_count] = itr->first;
      output_count++;
    }
  } else if (operation == "mode") {
    readData(input_data, input_count, ht);
    int count = 0;
    std::string mode;
    for (hashtable_type::const_iterator itr = ht.begin(); itr != ht.end(); itr++) {
      // Find the larger one
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
