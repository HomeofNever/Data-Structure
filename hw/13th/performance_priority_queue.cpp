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


void priority_queue_test(const std::string* input_data, int input_count, const std::string &operation, std::string *output_data, int &output_count) {

  // HINT: declare your priority_queue like this:
  std::priority_queue<std::string,std::vector<std::string> > pq(input_data,input_data+input_count);
  for (int i = 0; i < input_count; i++)
    pq.push(input_data[i]);

  if (operation == "sort") {
    for (int i = 0; i < input_count; i++) {
      output_data[i] = pq.top();
      pq.pop();
    }

    output_count = pq.size();
  } else if (operation == "remove_dups_same_order") {
    std::cerr << "Error: Operation does not support." << std::endl;
    return;
  } else if (operation == "remove_dups_any_order") {
  } else if (operation == "mode") {
  } else {
    std::cerr << "Error: Unknown operation: " << operation << std::endl;
    usage();
  }
}
