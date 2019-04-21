#include <ctime>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();


void priority_queue_test(const std::string *input_data, int input_count, const std::string &operation,
                         std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  std::priority_queue<std::string, std::vector<std::string> > pq(input_data, input_data + input_count);
  for (int i = 0; i < input_count; i++)
    pq.push(input_data[i]);

  if (operation == "sort") {
    for (int i = 0; i < input_count; i++) {
      output_data[i] = pq.top();
      pq.pop();
    }

    output_count = pq.size();
  } else if (operation == "remove_dups_same_order") {
    output_count = 0;
    std::cerr << "Error: Operation does not support." << std::endl;
    return;
  } else if (operation == "remove_dups_any_order") {
    std::string prev;
    int size = 0;

    while (!pq.empty()) {
      if (prev != pq.top()) {
        output_data[size] = pq.top();
        prev = pq.top();
        size++;
      }
      pq.pop();
    }

    output_count = size;
  } else if (operation == "mode") {
    std::string mode, current;
    current = pq.top();
    pq.pop();
    int mode_count = 0;
    int current_count = 1;

    while (!pq.empty()) {
      if (current == pq.top()) {
        // if they are the same increment the count
        current_count++;
      } else if (current_count >= mode_count) {
        // found a new mode!
        mode = current;
        mode_count = current_count;
        current = pq.top();
        current_count = 1;
      } else {
        // Begin
        current = pq.top();
        current_count = 1;
      }
      pq.pop();
    }

    if (current_count >= mode_count) {
      // last entry is a new mode!
      mode = current;
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
