#include <iostream>
#include <map>
#include <fstream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file\n";
    return 1;
  }

  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << std::endl;
    return 1;
  }

  int a;
  std::map<int, int> i;

  std::cout << "Input: ";
  while (istr >> a) {
    std::cout << a << ' ';
    i[a] += 1;
  }

  std::cout << std::endl;

  auto b = i.begin();

  unsigned int largest = 0;
  while (b != i.end()) {
    if (largest < b->second) {
      largest = b->second;
    }
    b++;
  }

  std::cout << "Number: ";
  b = i.begin();
  while (b != i.end()) {
    if (largest == b->second) {
      std::cout << b->first << ' ';
    }
    b++;
  }

  return 0;
}