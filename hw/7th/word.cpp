//
// Created by luox6 on 2019/3/9.
//

#include <iostream>
#include "word.h"

void word::print() const {
  std::cout << "Word: " << theword << std::endl;
  std::cout << "Path: " << "(" << _start_x << ", " << _start_y << ") -> " << "(" << _end_x << ", " << _end_y << ")"
            << std::endl;
  std::cout << "Length: " << length() << std::endl;
  std::cout << "Position: " << position() << std::endl;
}

bool word::same_word(const word &word1, const word &word2) {
  return word1.getWord() == word2.getWord();
}

bool word::collapse(const word &word1, const word &word2) {
  if (word1.position() == word2.position()) {
    if (word1.position() == 0) {
      if (word1.start_y() == word2.start_y()) {
        // Either start x should not be in the body of another one
        return (word1.start_x() <= word2.start_x()
                  && word2.start_x() <= word1.end_x()) ||
               (word2.start_x() <= word1.start_x()
                  && word1.start_x() <= word2.end_x());
      }
    } else {
      if (word1.start_x() == word2.start_x()) {
        // Same, but diff attribute
        return (word1.start_y() <= word2.start_y()
                  && word2.start_y() <= word1.end_y()) ||
               (word2.start_y() <= word1.start_y()
                  && word1.start_y() <= word2.end_y());
      }
    }
  }

  return false;
}
