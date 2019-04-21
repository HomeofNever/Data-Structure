#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();
typedef std::list<std::string> list_type;

void list_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your list like this:
   list_type lst;
  for (int i = 0; i < input_count; i++)
    lst.push_back(input_data[i]);

  if (operation == "sort") {
    lst.sort();
    list_type::const_iterator i = lst.begin();

    for (int j = 0; j < input_count; j++) {
      output_data[j] = *i;
      i++;
    }

    output_count = lst.size();
  } else if (operation == "remove_dups_same_order") {
    for (list_type::iterator i = lst.begin(); i != (lst.end()--); i++) {
      list_type::iterator j = i;
      j++;
      for (; j != lst.end(); j++) {
        if (*i == *j) {
          j = lst.erase(j);
        }
      }
    }

    output_count = 0;
    list_type::const_iterator i = lst.begin();

    for (list_type::const_iterator itr = lst.begin(); itr != lst.end(); itr++) {
      output_data[output_count] = *itr;
      output_count++;
    }
  } else if (operation == "remove_dups_any_order") {
    lst.sort();
    lst.unique();
    output_count = 0;
    list_type::const_iterator i = lst.begin();

    for (list_type::const_iterator itr = lst.begin(); itr != lst.end(); itr++) {
      output_data[output_count] = *itr;
      output_count++;
    }

  } else if (operation == "mode") {
    lst.sort();
    int current_count = 1;
    std::string mode;
    int mode_count = 0;
    // keep track of two pointers into the structure
    list_type::const_iterator current = lst.begin();
    ++current;
    list_type::const_iterator previous = lst.begin();
    for (; current != lst.end(); ++current, ++previous) {
      if (*current == *previous) {
        // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = *previous;
        mode_count = current_count;
        current_count = 1;
      } else {
        current_count = 1;
      }
    }
    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = *previous;
      mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    output_data[0] = mode;
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
