//
// Created by luox6 on 2019/4/6.
//

#ifndef INC_10TH_MOVIE_H
#define INC_10TH_MOVIE_H


#include <string>
#include <vector>
#include "actors.h"

typedef std::vector<std::string> listType;

class movie {
public:
    movie(std::string &t, int y, int l):
          title(t), yearOfRelease(y), length(l) {};
    ~movie(){};

    // Accessor
    std::string getTitle() const { return title; }
    int getYearOfRelease() const { return yearOfRelease; }
    int getLength() const { return length; }
    listType getGenreList() const { return genreList; }
    listType getActorList() const { return actorList; }
    listType getRoleList() const { return roleList; }

    // Mutator
    void addGenre(std::string &genre) { genreList.push_back(genre); }
    void addActor(std::string &actor) { actorList.push_back(actor); }
    void addRole(std::string &role) { roleList.push_back(role); }

    // Debug
    void print() const;

private:
    std::string title;
    int yearOfRelease;
    int length;
    listType genreList;
    listType actorList;
    listType roleList;

};


#endif //INC_10TH_MOVIE_H
