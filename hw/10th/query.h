//
// Created by luox6 on 2019/4/7.
//

#ifndef INC_10TH_QUERY_H
#define INC_10TH_QUERY_H

#include <string>
#include <vector>
#include <list>
#include "movie.h"

#define HASH_SEPARATOR "-"
#define DEFAULT_QUERY "DEFAULT_QUERY"
const std::string UNKNOWN_SINGLE_FIELD = "?";
const std::string UNKNOWN_LIST_FIELD  = "0";

// Query String should be `title-year-runtime`
// + `-#ofGenre{...Genres}`
// + `-#ofActor{...Actors}`
// + `-#ofRole{...Roles}`
class query {
public:
    query(){};
    ~query(){};

    // Accessor
    std::string getString() const { return str; }
    static unsigned int getHash(const std::string &str) { return doHash(str); };

    // External
    static void getQueries(movie *m, std::list<std::string*> &q);

private:
    std::string str = DEFAULT_QUERY;

    static unsigned doHash(const std::string &str);

    // Helpers
    static void getQueryWithoutList(movie *m, std::vector<std::string> &ls);
    static void getQueryOfLists(movie *m, std::vector<std::string> &ls);

    static void insert(int s, std::string &str,
                       const std::string &field,
                       const std::string &placeHolder);
    static void appendList(const listType &list, std::string &str);
};

#endif //INC_10TH_QUERY_H
