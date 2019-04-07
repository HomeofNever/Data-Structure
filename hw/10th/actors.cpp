//
// Created by luox6 on 2019/4/6.
//

#include <iostream>
#include "actors.h"

void actors::print() const {
  for (ACTORS_TYPES::const_iterator i = actors.begin();
       i != actors.end();
       i++) {
    std::cout << i->first << " - " << i->second << std::endl;
  }
}
