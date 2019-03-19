#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <cmath>
#include <algorithm>

#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

//TODO: You must fill in all ?????? with the correct types.
typedef unsigned int ID_TYPE; //Type for user IDs
typedef std::pair<double, double> COORD_TYPE; //Type for a coordinate (latitude and longitude)
typedef std::map<ID_TYPE, std::list<ID_TYPE>> ADJ_TYPE; //Adjacency Lists type
typedef std::map<ID_TYPE, COORD_TYPE> GEO_TYPE; //Positional "dictionary"

//Function forward declarations. DO NOT CHANGE these. 
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile);
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile);
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile);
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations,
                                std::ofstream& outfile, const ID_TYPE& start_id,
                                double max_distance);
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it, unsigned int offset);


// DO NOT CHANGE THIS FUNCTION
int main(int argc, char** argv){
    ADJ_TYPE adj_lists;
    GEO_TYPE locations;

    if(argc != 3){
        std::cout << "Correct usage is " << argv[0]
                  << " [commands file] [output file]" << std::endl;
        return -1;
    }

    std::ifstream commands(argv[1]);
    if(!commands){
        std::cerr << "Problem opening " << argv[1] << " for reading!"
                  << std::endl;
        return -1;
    }

    std::ofstream outfile(argv[2]);
    if(!outfile){
        std::cerr << "Problem opening " << argv[2] << " for writing!"
                  << std::endl;
        return -1;
    }

    std::string token; //Read the next command
    while(commands >> token){
        if(token == "load-connections"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename
                          << " for reading connections." << std::endl;
                return -1;
            }

            loadConnections(adj_lists, loadfile);
        }
        else if(token == "load-locations"){
            std::string filename;
            commands >> filename;

            std::ifstream loadfile(filename.c_str());
            if(!loadfile){
                std::cerr << "Problem opening " << filename
                          << " for reading locations." << std::endl;
                return -1;
            }

            loadLocations(locations, loadfile);
        }
        else if(token == "print-degrees"){
            printDegreesOfAll(adj_lists, outfile);
        }
        else if(token == "print-degree-histogram"){
            printDegreesHistogram(adj_lists, outfile);
        }
        else if(token == "all-users-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printAllUsersWithinDistance(locations, outfile, start_id,
                                        max_distance);
        }
        else if(token == "friends-within-distance"){
            ID_TYPE start_id;
            double max_distance; //In kilometers
            commands >> start_id >> max_distance;

            printFriendsWithinDistance(adj_lists, locations, outfile,
                                       start_id, max_distance);
        }
        else if(token == "friends-with-degree"){
            ID_TYPE start_id,degree;
            commands >> start_id >> degree;

            printFriendsWithDegree(adj_lists, outfile, start_id, degree);
        }
        else if(token == "nodes-within-ID-range"){
            ID_TYPE start_id,offset;
            commands >> start_id >> offset;

            printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                                    adj_lists.find(start_id), offset);
        }
        else{
            std::cerr << "Unknown token \"" << token << "\"" << std::endl;
            return -1;
        }
    }

    return 0;
}




// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE& adj_lists, std::ifstream& loadfile){
    ID_TYPE a, b;
    while (loadfile >> a >> b) {
        adj_lists[a].push_back(b);
    }
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE& locations, std::ifstream& loadfile){
    ID_TYPE id;
    double latitude, longitude;
    while (loadfile >> id >> latitude >> longitude) {
        COORD_TYPE c = COORD_TYPE(latitude, longitude);
        locations[id] = c;
    }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE& locations, std::ofstream& outfile,
                                 const ID_TYPE& start_id, double max_distance){
    GEO_TYPE::const_iterator self = locations.find(start_id);
    if (self == locations.end()) {
      outfile << "User ID " << start_id << " does not have a recorded location." << std::endl;
      return;
    }

    COORD_TYPE myself = self->second;

    std::map<double, std::list<ID_TYPE>> tmp;
    GEO_TYPE::const_iterator i = locations.begin();
    while (i != locations.end()) {
        if (i->first != start_id) {
            double d = distanceEarth(
                    i->second.first,
                    i->second.second,
                    myself.first,
                    myself.second);
            if ( d <= max_distance ){
              tmp[(int)floor(d)].push_back(i->first);
            }
        }
        i++;
    }

    if (tmp.empty()) {
      outfile << "There are no users within " << max_distance << " km of user " << start_id << std::endl;

    } else {
      outfile << "User IDs within " << max_distance <<  " km of user " << start_id << ":" << std::endl;
      std::map<double, std::list<ID_TYPE>>::const_iterator j = tmp.begin();
      while (j != tmp.end()) {
        outfile << " " << j->first << " km:";
        std::list<ID_TYPE>::const_iterator k = j->second.begin();
        while (k != j->second.end()) {
          outfile << ' ';
          outfile << *k;
          k++;
        }
        j++;
        outfile << std::endl;
      }
    }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many users
 * have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  ID_TYPE num = 0;
  std::map<ID_TYPE , ID_TYPE> n;
  ADJ_TYPE::const_iterator i = adj_lists.begin();

  while (i != adj_lists.end()) {
    ID_TYPE user_num = i->second.size();
    if (user_num >= 1) {
      num++;
      std::map<ID_TYPE , ID_TYPE >::iterator j = n.find(user_num);
      if (j == n.end()) {
        n.insert(std::pair<ID_TYPE, ID_TYPE>(i->second.size(), 1));
      } else {
        j->second++;
      }
    }
    i++;
  }

  std::map<ID_TYPE, ID_TYPE>::const_iterator k = n.begin();
  outfile << "Histogram for " << num << " users:" << std::endl;
  while (k != n.end()) {
    outfile << " Degree " << k->first << ": " << k->second << std::endl;
    k++;
  }
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the degree for
 * each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE& adj_lists, std::ofstream& outfile){
  ADJ_TYPE::const_iterator i = adj_lists.begin();
  std::map<ID_TYPE, ID_TYPE> tmp = std::map<ID_TYPE, ID_TYPE>();


  while (i != adj_lists.end()) {
    ID_TYPE s = i->second.size();
    if (s >= 1) {
      tmp.insert(std::pair<ID_TYPE, ID_TYPE>(i->first, s));
    }
    i++;
  }

  outfile << "Degrees for "<< tmp.size() <<" users:" << std::endl;
  std::map<ID_TYPE, ID_TYPE>::const_iterator j = tmp.begin();
  while (j != tmp.end()) {
    outfile << " "<< j->first << ": Degree " << j->second << std::endl;
    j++;
  }
}

/**
 * "User 1 has 1 friend(s) with degree 1: 2"
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE& adj_lists, std::ofstream& outfile,
                            const ID_TYPE& start_id, unsigned int degree){
  // No Such User
  ADJ_TYPE::const_iterator self = adj_lists.find(start_id);
  if (self == adj_lists.end()) {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }

  std::list<ID_TYPE> tmp;
  std::list<ID_TYPE>::const_iterator friends = self->second.begin();

  while (friends != self->second.end()) {
    ADJ_TYPE::const_iterator f = adj_lists.find(*friends);
    if (f != adj_lists.end()) {
      if (f->second.size() == degree) {
        tmp.push_back(f->first);
      }
    }
    friends++;
  }

  if (tmp.empty()) {
    outfile << "User " << start_id <<" has 0 friend(s) with degree " << degree << std::endl;
  } else {
    outfile << "User " << start_id << " has " << tmp.size() <<" friend(s) with degree " << degree << ":";
    std::list<ID_TYPE>::const_iterator j = tmp.begin();
    while (j != tmp.end()) {
      outfile << ' ' << (*j);
      j++;
    }

    outfile << std::endl;
  }
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printFriendsWithinDistance(const ADJ_TYPE& adj_lists, const GEO_TYPE& locations,
                                std::ofstream& outfile, const ID_TYPE& start_id,
                                double max_distance){
  ADJ_TYPE::const_iterator myself_adj = adj_lists.find(start_id);
  // No such user
  if (myself_adj == adj_lists.end()) {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }

  GEO_TYPE::const_iterator myself_geo = locations.find(start_id);
  // No Location
  if (myself_geo == locations.end()) {
    outfile << "User ID " << start_id << " does not have a recorded location." << std::endl;
    return;
  }

  std::map<double, std::list<ID_TYPE>> tmp;
  std::list<ID_TYPE>::const_iterator friends = myself_adj->second.begin();
  COORD_TYPE self = myself_geo->second;

  while (friends != myself_adj->second.end()) {
    GEO_TYPE::const_iterator f = locations.find(*friends);
    // User should have location before comparison
    if (f != locations.end()) {
      COORD_TYPE fd = f->second;
      double d = distanceEarth(fd.first, fd.second, self.first, self.second);
      if (d <= max_distance) {
        tmp[d].push_back(f->first);
      }
    }
    friends++;
  }

  if (tmp.empty()) {
    outfile << "There are no friends within " << max_distance << " km of user " << start_id << std::endl;
  } else {
    outfile << "Friends within " << max_distance << " km of user " << start_id << ":" << std::endl;
    std::map<double, std::list<ID_TYPE>>::const_iterator j = tmp.begin();
    while (j != tmp.end()) {
      outfile << ' ' << j->first << " km:";
      std::list<ID_TYPE>::const_iterator k = j->second.begin();
      while (k != j->second.end()) {
        outfile << ' ' << *k;
        k++;
      }
      outfile << std::endl;
      j++;
    }
  }
}

/**
 * "There are no users with an ID within +/-1000000000 of 3958578120"
 * "Users with an ID within +/-1 of 3: 2 4"
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator-- O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0 diifference)
 *        It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed user's
 *               ID can have
 */
void printUsersWithinIDRange(std::ofstream& outfile, ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it, unsigned int offset){
  std::list<ID_TYPE> tmp;
  if (start_it != end) {
    while (begin != end) {
      if (start_it != begin) {
        unsigned int diff = begin->first > start_it->first ?
                            begin->first - start_it->first : start_it->first - begin->first;
        if (diff <= offset) {
          if (!begin->second.empty()) {
            tmp.push_back(begin->first);
          }
        }
      }
      begin++;
    }
  } else {
    outfile << "There is no user with the requested ID" << std::endl;
    return;
  }

  if (tmp.empty()) {
    outfile << "There are no users with an ID within +/-" << offset << " of " << start_it->first << std::endl;
  } else {
    std::list<ID_TYPE>::const_iterator j = tmp.begin();
    outfile << "Users with an ID within +/-" << offset << " of " << start_it->first << ":";
    while (j != tmp.end()) {
      outfile << ' ' << (*j);
      j++;
    }
    outfile << std::endl;
  }

}