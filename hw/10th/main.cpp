#include <iostream>
#include <fstream>
#include <list>
#include "movie.h"
#include "hashtable.h"
#include "query.h"

#define TABLE_SIZE_INPUT "table_size"
#define OCCUPANCY_INPUT "occupancy"
#define MOVIE_INPUT "movies"
#define ACTOR_INPUT "actors"
#define QUERY_BEGIN "query"
#define QUIT "quit"

#define DEBUG_ACTOR "printActor"
#define DEBUG_MOVIE "printMovie"
#define DEBUG_QUERIES "printQueries"

// Handle file open related issue
std::ifstream open_file(std::string &filename) {
  std::ifstream tmp(filename);
  if(!tmp){
    std::cerr << "Problem opening "
              << filename << " for reading!" << std::endl;
    exit(1);
  }

  return tmp;
}


// Parse Actor file
void read_actor_file(std::ifstream &stream, actors &a) {
  std::string id, name;
  while (stream >> id >> name) {
    if (!a.addActor(id, name)) {
      std::cerr << "Error when adding actor" << id << ' ' << name << std::endl;
    }
  }
}

// Parse Genre in movie file
void read_genre(movie *m, std::istream &stream) {
  int num;
  std::string genre;

  stream >> num;
  for (int i = 0; i < num; i++) {
    stream >> genre;
    m->addGenre(genre);
  }
}

// Parse Actor in movie file
void read_actor(movie *m, std::istream &stream) {
  int num;
  std::string actor;

  stream >> num;
  for (int i = 0; i < num; i++) {
    stream >> actor;
    m->addActor(actor);
  }
}

// Parse Role in movie file
void read_role(movie *m, std::istream &stream) {
  int num;
  std::string role;

  stream >> num;
  for (int i = 0; i < num; i++) {
    stream >> role;
    m->addRole(role);
  }
}

// Parse Movie file
void read_movie_file(std::ifstream &stream, std::list<movie*> &m) {
  std::string title, year, minute;
  while (stream >> title >> year >> minute) {
    movie * new_movie = new movie(title, year, minute);
    read_genre(new_movie, stream);
    read_actor(new_movie, stream);
    read_role(new_movie, stream);

    m.push_back(new_movie);
  }
}

// Generate query string of given format
std::string generateQueryString(std::istream &stream) {
  std::string queryString;
  std::string part;
  // std::cin >> title >> year >> minute;
  for (int i = 0; i < 3; i++) {
    stream >> part;
    queryString += part + HASH_SEPARATOR;
  }
  for (int i = 0; i < 3; i++) {
    int num;
    stream >> num;
    queryString += std::to_string(num);
    for (int j = 0; j < num; j++) {
      stream >> part;
      queryString += part;
    }
    queryString += HASH_SEPARATOR;
  }

  return queryString.substr(0, queryString.size() - 1);
}

// Clean up movies when quitting
void delete_movies(std::list<movie*> &m) {
  for (std::list<movie*>::iterator i = m.begin(); i != m.end(); i++) {
    delete *i;
  }
}

int main(int argc, char** argv) {
  // init default
  int table_size = TABLE_SIZE;
  float occupancy = OCCUPANCY;

  std::list<movie*> m;
  hashtable * h = nullptr;
  actors a;

  std::string str;
  while (std::cin >> str) {
    if (str == QUIT) {
      delete_movies(m);
      delete h;
      break;
    } else {
      if (str != QUERY_BEGIN) {
        // init files
        if (str == MOVIE_INPUT) {
          std::cin >> str;
          std::ifstream movie_file = open_file(str);
          read_movie_file(movie_file, m);
        } else if (str == ACTOR_INPUT) {
          std::cin >> str;
          std::ifstream actor_file = open_file(str);
          read_actor_file(actor_file, a);
        } else if (str == TABLE_SIZE_INPUT) {
          std::cin >> table_size;
        } else if (str == OCCUPANCY_INPUT) {
          std::cin >> occupancy;
        } else if (str == DEBUG_ACTOR) {
          a.print();
        } else if (str == DEBUG_MOVIE) {
          for (std::list<movie*>::const_iterator i = m.begin(); i != m.end(); i++) {
            (*i)->debug_print();
          }
          std::cout << "  " << "Total: " << m.size() << std::endl;
        } else if (str == DEBUG_QUERIES) {
          std::list<std::string*> q;
          for (std::list<movie*>::const_iterator i = m.begin(); i != m.end(); i++) {
            query::getQueries(*i, q);
          }
          for (std::list<std::string*>::const_iterator i = q.begin(); i != q.end(); i++) {
            std::cout << "Query: " << **i << std::endl;
            std::cout << "Hash: " << query::getHash(**i) << std::endl;
            delete *i;
          }
          std::cout << "  " << "Total: " << q.size() << std::endl;
        } else {
          std::cerr << "Command Not Recognized!" << std::endl;
        }

        // Create Hash Table
        if (h == nullptr && !m.empty()) {
          h = new hashtable(occupancy, table_size);
          for (std::list<movie*>::const_iterator i = m.begin(); i != m.end(); i++) {
            h->addItem(*i);
          }
        }
      } else {
        // Parsing Query string
        std::string q = generateQueryString(std::cin);
        std::list<movie*> result = h->getMovie(q);
        if (result.empty()) {
          std::cout << "No results for query." << std::endl;
        } else {
          std::cout << "Printing " << result.size() << " result(s):" << std::endl;
          for (std::list<movie*>::const_iterator i = result.begin(); i != result.end(); i++) {
            (*i)->print(a);
          }
        }
      }
    }
  }

  return 0;
}