//
// Created by luox6 on 2019/4/6.
//

#include <iostream>
#include "movie.h"

#define SEPARATOR " - "

// Print Keys intstead of actors
void movie::debug_print() const {
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

/* Sample Output
  DS_VI:Curse_of_the_Recursion
  2102
  120
  1 Horror
  3 Ben_Bitdiddle (Unknown_Role) Buster_Holzbauer (Unknown_Role) Alyssa_P_Hacker (Unknown_Role)
 */
void movie::print(actors &actor_list) const {
  std::cout << title << std::endl
            << yearOfRelease << std::endl
            << length << std::endl;

  std::cout << genreList.size();
  for (listType::const_iterator i = genreList.begin(); i != genreList.end(); i++) {
    std::cout << ' ' << *i;
  }
  std::cout << std::endl;

  std::cout << actorList.size();
  for (unsigned int i = 0; i < actorList.size(); i++) {
    std::cout << ' ' << actor_list.getActor(actorList[i])
              << ' ' << '(' << roleList[i] << ')';
  }
  std::cout << std::endl;
}