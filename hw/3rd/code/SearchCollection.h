#ifndef CODE_SEARCHCOLLECTION_H
#define CODE_SEARCHCOLLECTION_H

#include <vector>
#include <string>
#include <fstream>

#include "Schedule.h"

/**
 * SearchCollection is created when Schedules in ScheduleCollection
 * are filtered for a table and ready to to customized sort and draw
 */
class SearchCollection {
public:

    // Constructors
    SearchCollection();
    /**
     * This constructor handles search results and customize sort and draw behavior.
     *
     * @param search_field
     * @param search_value
     * @param schedules
     */
    SearchCollection(std::string &search_field, std::string &search_value, std::vector<Schedule> &schedules);

    // Accessors

    /**
     * Return All Schedules within collection.
     */
    std::vector<Schedule> getSchedules() const;

    /**
     * Get Search Field ("dept", "room", "custom") provided
     */
    std::string getSearchField() const;

    /**
     * Get Search Value ("room_name", "dept_code", "custom_value") provided
     */
    std::string getSearchValue() const;

    /**
     * Get current Collection size.
     */
    int getCollectionSize() const;

    /**
     * Get the length of the longest CRN
     */
    int getLongestCRNLength() const;

    /**
     * Get the length of the longest name size.
     */
    int getLongestCourseNameLength() const;

    /**
     * Get the length of the longest course code
     */
    int getLongestCourseCodeLength() const;

    /**
     * Get the length of the longest dept code
     */
    int getLongestDeptLength() const;

    /**
     * Get the length of the longest day words' length ("Monday" => 6, "Tuesday" => 7 ...).
     */
    int getLongestDayLength() const;

    /**
     * Get the length of the longest room words' length
     */
    int getLongestRoomLength() const;


    // Member methods
    /**
     * Print all Schedules (to std::cout).
     */
    void print();

    /**
     * Find and call specific call methods. (based on the search field provided)
     */
    bool sort();

    /**
     * Draw the collection and stream to specific stream pointer.
     *
     * @param out_str
     */
    bool draw(std::ofstream &out_str);

private:

    // Variables
    /**
     * This vector holds all schedules in the collection
     */
    std::vector<Schedule> schedules;

    /**
     * Type of the search ("room", "dept", "custom")
     */
    std::string search_field;

    /**
     * Value of the search ("room_name", "dept_code", "custom_value")
     */
    std::string search_value;

    // Sort methods
    /**
     * Sort Collection for drawing room table
     */
    void sortForRoomTable();

    /**
     * Sort Collection for drawing dept Table
     */
    void sortForDeptTable();

    /**
     * Sort Collection for drawing day Table
     */
    void sortForDayTable();

    // Draw methods
    /**
     * Draw a single room table
     *
     * @param out_str
     */
    void drawRoomTable(std::ofstream &out_str);

    /**
     * Draw a single dept table
     *
     * @param out_str
     */
    void drawDeptTable(std::ofstream &out_str);

    /**
     * Draw a single day table
     *
     * @param out_str
     */
    void drawDayTable(std::ofstream &out_str);
};


#endif //CODE_SEARCHCOLLECTION_H
