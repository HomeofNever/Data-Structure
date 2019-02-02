#include <algorithm>
#include <fstream>
#include <iostream>

#include "ScheduleCollection.h"
#include "SearchCollection.h"

// Constructor
ScheduleCollection::ScheduleCollection() {}

/**
 * Assigned vector to self.
 * @param vec
 */
ScheduleCollection::ScheduleCollection(std::vector<Schedule> &vec)
{
    schedules = vec;
}

/**
 * Read in by line and feed to add schedule methods
 * @param in_str
 */
ScheduleCollection::ScheduleCollection(std::ifstream &in_str)
{
    std::string CRN;
    std::string dept_code;
    std::string course_code;
    std::string course_name;
    std::string day;
    std::string start_time;
    std::string end_time;
    std::string room;

    while (in_str >> CRN >> dept_code >> course_code >> course_name >> day >> start_time >> end_time >> room){
        for (unsigned i = 0; i < day.size(); i++)
        {
            char d = day[i];
            Schedule s = Schedule(CRN, dept_code, course_code, course_name, d, start_time, end_time, room);
            addSchedule(s);
        }
    }

}

// Accessors
std::vector<Schedule> ScheduleCollection::getSchedules() const
{
    return schedules;
}

/**
 * Return Collection's size by calculating vector's size
 */
int ScheduleCollection::getCollectionSize() const
{
    return (int)schedules.size();
}

/**
 * Loop over the Collection and build a vector with all schedules' room name
 */
std::vector<std::string> ScheduleCollection::getRoomList() const
{
    std::vector<std::string> room_list;
    int flag = 0;

    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        // If room is not in the list, add to the list.
        // Set flag to 1 if there is one.
        for (unsigned int j = 0; j < room_list.size(); j++)
        {
            if (room_list[j] == schedules[i].getRoom())
            {
                // Find one, break and continue
                flag = 1;
                break;
            }
        }

        // Flag not triggered, add to list
        if (flag == 0)
        {
            room_list.push_back(schedules[i].getRoom());
        }

        // Reset flag
        flag = 0;
    }

    // Sort name
    std::sort(room_list.begin(), room_list.end());

    return room_list;
}

// Search
/**
 * Get Schedules by specific room name and Build SearchCollection for it.
 *
 * @param room Room name
 */
SearchCollection ScheduleCollection::getRoomCollection(std::string &room) const
{
    std::string search_field = "room";
    std::vector<Schedule> result;

    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        if (schedules[i].getRoom() == room)
        {
            result.push_back(schedules[i]);
        }
    }

    return SearchCollection(search_field, room, result);
}

/**
 * Loop over the Collection and and Build SearchCollection for each of the room.
 */
std::vector<SearchCollection> ScheduleCollection::getRoomCollection() const
{
    std::string search_field = "room";
    std::vector<SearchCollection> result;
    std::vector<std::string> room_list = getRoomList();

    for (unsigned int i = 0; i < room_list.size(); i++) {
        result.push_back(getRoomCollection(room_list[i]));
    }

    return result;
}

/**
 * Get Schedules by specific dept_code and Build SearchCollection for it.
 * @param dept_code
 * @return
 */
SearchCollection ScheduleCollection::getDeptCollection(std::string &dept_code) const
{
    std::string search_field = "dept";
    std::vector<Schedule> result;

    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        if (schedules[i].getDeptCode() == dept_code)
        {
            result.push_back(schedules[i]);
        }
    }

    return SearchCollection(search_field, dept_code, result);
}

/**
 * Loop through collection to collect all matched day
 * @param day Specific Day
 */
SearchCollection ScheduleCollection::getDayCollection(Day &day) const
{
    std::string search_field = "day";
    std::vector<Schedule> result;
    std::string d = day.getCompleteDay();

    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        if (schedules[i].getDay() == day)
        {
            result.push_back(schedules[i]);
        }
    }

    return SearchCollection(search_field, d, result);
}

/**
 * Loop through all possible days and collect Schedules
 */
std::vector<SearchCollection> ScheduleCollection::getDayCollection() const
{
    std::string search_field = "day";
    std::vector<SearchCollection> result;
    std::vector<Day> d = getAllDay();

    for (unsigned int i = 0; i < d.size(); i++)
    {
        SearchCollection c = getDayCollection(d[i]);
        // If there is nothing in the Collection, skip it.
        if (c.getCollectionSize() > 0)
        {
            result.push_back(c);
        }
    }

    return result;
}

// Mutator
/**
 * Add Schedule to the private vector
 * @param schedule
 */
void ScheduleCollection::addSchedule(Schedule &schedule)
{
    schedules.push_back(schedule);
}


// Methods
/**
 * Print all Schedules in collection
 */
void ScheduleCollection::print()
{
    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        schedules[i].print();
    }
}
