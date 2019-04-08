//
// Created by luox6 on 2019/4/6.
//

#ifndef INC_10TH_MOVIE_H
#define INC_10TH_MOVIE_H


#include <string>
#include <vector>
#include "actors.h"

typedef std::vector<std::string> listType;

// Class that describe how a movie will be
class movie {
public:
    // Constructors
    movie(){}
    movie(std::string &t, std::string &y, std::string &l):
          title(t), yearOfRelease(y), length(l) {};
    ~movie(){};

    // Accessors
    std::string getTitle() const { return title; }
    std::string getYearOfRelease() const { return yearOfRelease; }
    std::string getLength() const { return length; }
    listType getGenreList() const { return genreList; }
    listType getActorList() const { return actorList; }
    listType getRoleList() const { return roleList; }

    // Mutators
    void addGenre(std::string &genre) { genreList.push_back(genre); }
    void addActor(std::string &actor) { actorList.push_back(actor); }
    void addRole(std::string &role) { roleList.push_back(role); }

    // Friends
    // Let Query Access and Generate Queries directly
    friend class query;

    // Output
    void print(actors &actor_list) const;
    // Debug
    void debug_print() const;

private:
    std::string title;
    std::string yearOfRelease;
    std::string length;
    listType genreList;
    listType actorList;
    listType roleList;
};


#endif //INC_10TH_MOVIE_H
