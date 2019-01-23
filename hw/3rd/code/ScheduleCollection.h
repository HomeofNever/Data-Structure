#ifndef CODE_SCHEDULECOLLECTION_H
#define CODE_SCHEDULECOLLECTION_H

#include <vector>
#include <string>
#include <fstream>

#include "Schedule.h"
#include "SearchCollection.h"

class ScheduleCollection {
public:
    // Constructors
    ScheduleCollection();
    /**
     * Init Collection by Schedule Vector
     * @param vec Vector with Schedules
     */
    ScheduleCollection(std::vector<Schedule> &vec);

    /**
     * Init Collection by Input stream
     * @param in_str input Stream
     */
    ScheduleCollection(std::ifstream &in_str);

    // Accessors
    /**
     * Get a vector of Schedules within this Collection
     */
    std::vector<Schedule> getSchedules() const;

    /**
     * Get a vector of room string within this Collection
     */
    std::vector<std::string> getRoomList() const;

    /**
     * Get the number of Schedules in this collection
     */
    int getCollectionSize() const;

    // Search Accessors
    /**
     * Parse all Schedules' room and put in a Vector of Collections
     */
    std::vector<SearchCollection> getRoomCollection() const;

    /**
     * Get a Collection contains schedules with specific room name
     *
     * @param room The name of the room
     */
    SearchCollection getRoomCollection(std::string &room) const;

    /**
     * Get a Collection contains schedules with specific dept_code
     * @param dept_code Department code
     */
    SearchCollection getDeptCollection(std::string &dept_code) const;

    /**
     * Get vector contains Collections based day
     */
    std::vector<SearchCollection> getDayCollection() const;

    /**
     * Get vector contains Schedules based on specific day
     */
    SearchCollection getDayCollection(Day &day) const;


    // Mutator
    /**
     * Add Schedule with constructed Schedule Object
     * @param schedule
     */
    void addSchedule(Schedule &schedule);


    // Methods
    /**
     * Print current object
     */
    void print();

private:
    /**
     * a vector stores all Schedules read from the file
     */
    std::vector<Schedule> schedules;
};


#endif //CODE_SCHEDULECOLLECTION_H
