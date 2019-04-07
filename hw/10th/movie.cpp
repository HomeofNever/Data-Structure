//
// Created by luox6 on 2019/4/6.
//

#include <iostream>
#include "movie.h"

#define SEPARATOR " - "

void movie::print() const {
  std::cout << title << SEPARATOR
            << yearOfRelease << SEPARATOR
            << length << std::endl;

  std::cout << "Genre(s): ";
  for (listType::const_iterator i = genreList.begin(); i != genreList.end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << std::endl;

  std::cout << "Actor(s): ";
  for (listType::const_iterator i = actorList.begin(); i != actorList.end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << std::endl;

  std::cout << "Role(s): ";
  for (listType::const_iterator i = roleList.begin(); i != roleList.end(); i++) {
    std::cout << *i << ' ';
  }
  std::cout << std::endl;
}
