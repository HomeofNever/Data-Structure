//
// Created by luox6 on 2019/3/9.
//

#include <iostream>
#include "word.h"

void word::print() const {
  std::cout << "Word: " << theword << std::endl;
  std::cout << "Path: " << "(" << _start_x << ", " << _start_y << ") -> " << "(" << _end_x << ", " << _end_y << ")" << std::endl;
  std::cout << "Length: " << length() << std::endl;
  std::cout << "Position: " << position() << std::endl;
}