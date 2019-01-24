#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "SearchCollection.h"

SearchCollection::SearchCollection() {}

/**
 * Assign each with fields
 *
 * @param search_field
 * @param search_value
 * @param schedules
 */
SearchCollection::SearchCollection(std::string &search_field, std::string &search_value,
                                   std::vector<Schedule> &schedules) {
    this->search_field = search_field;
    this->search_value = search_value;
    this->schedules = schedules;
}

// Accessors
std::vector<Schedule> SearchCollection::getSchedules() const
{
    return schedules;
}

std::string SearchCollection::getSearchField() const
{
    return search_field;
}

std::string SearchCollection::getSearchValue() const
{
    return search_value;
}

/**
 * Return vector sizes
 */
int SearchCollection::getCollectionSize() const
{
    return (int)schedules.size();
}

/**
 * Loop through Schedules and find if a CRN is longer than the existing value
 */
int SearchCollection::getLongestCRNLength() const
{
    // CRN
    int CRN_length = 3;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getCRN().size() > CRN_length)
        {
            CRN_length = (int)schedules[i].getCRN().size();
        }
    }

    return CRN_length;
}

/**
 * Loop through Schedules and find if a name is longer than the existing value
 */
int SearchCollection::getLongestCourseNameLength() const
{
    // Class Title
    int course_length = 11;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getCourseName().size() > course_length)
        {
            course_length = (int)schedules[i].getCourseName().size();
        }
    }

    return course_length;
}

/**
 * Loop through Schedules and find if a course code is longer than the existing value
 */
int SearchCollection::getLongestCourseCodeLength() const
{
    // Coursenum
    int course_code_length = 9;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getCourseCode().size() > course_code_length)
        {
            course_code_length = (int)schedules[i].getCourseCode().size();
        }
    }

    return course_code_length;
}

/**
 * Loop through Schedules and find if a dept_code is longer than the existing value
 */
int SearchCollection::getLongestDeptLength() const
{
    // Dept
    int dept_length = 4;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getDeptCode().size() > dept_length)
        {
            dept_length = (int)schedules[i].getDeptCode().size();
        }
    }

    return dept_length;
}

/**
 * Loop through Schedules find if there is one larger than the existing value
 */
int SearchCollection::getLongestDayLength() const
{
    int day_length = 6;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getDay().getCompleteDay().size() > day_length)
        {
            day_length = (int)schedules[i].getDay().getCompleteDay().size();
        }
    }

    return day_length;
}

/**
 * Loop through Schedules find if there is one larger than the existing value
 */
int SearchCollection::getLongestRoomLength() const
{
    int room_length = 4;

    for (unsigned int i = 0; i < schedules.size(); i++) {
        if (schedules[i].getRoom().size() > room_length)
        {
            room_length = (int)schedules[i].getRoom().size();
        }
    }

    return room_length;
}

// Member Methods
/**
 * Identify which sort methods to use via if
 * Print error if none of them matched
 */
bool SearchCollection::sort()
{
    if (getSearchField() == "room")
    {
        sortForRoomTable();
        return true;
    } else if (getSearchField() == "dept")
    {
        sortForDeptTable();
        return true;
    } else if (getSearchField() == "day")
    {
        sortForDayTable();
        return true;
    }else {
        std::cerr << "Unable to find suitable sort method." << std::endl;
        return false;
    }
}

/**
 * Find suitable draw method to use for current Collection
 * Stop if sort fails
 * Report error if no found
 *
 * @param out_str
 */
bool SearchCollection::draw(std::ofstream &out_str)
{
    if (sort())
    {
        if (getSearchField() == "room")
        {
            drawRoomTable(out_str);
            return true;
        } else if (getSearchField() == "dept")
        {
            drawDeptTable(out_str);
            return true;
        } else if (getSearchField() == "day")
        {
            drawDayTable(out_str);
            return true;
        } else {
            std::cerr << "Unable to find suitable draw methods" << std::endl;
            return false;
        }
    } else {
        std::cerr << "Sort fails, stop drawing." << std::endl;
        return false;
    }
}

/**
 * Print Search fields and all Schedules
 */
void SearchCollection::print()
{
    std::cout << getSearchField() << ' ' << getSearchValue() << std::endl;
    for (unsigned int i = 0; i < schedules.size(); i++)
    {
        schedules[i].print();
    }
}


// Private Methods
// Draw Methods
/**
 * Loop over Collection and draw Room table
 * Example:
    Room DARRIN_330
    Dept  Coursenum  Class Title        Day      Start Time  End Time
    ----  ---------  -----------------  -------  ----------  --------
    ECSE  2010-01    ELECTRIC_CIRCUITS  Monday   07:00PM     08:50PM
    ECSE  2410-01    SIGNALS_&_SYSTEMS  Tuesday  08:30AM     09:50AM
    ECSE  2410-01    SIGNALS_&_SYSTEMS  Friday   08:30AM     09:50AM
    3 entries
*/
void SearchCollection::drawRoomTable(std::ofstream &out_str)
{
    if (schedules.size() != 0)
    {
        out_str << "Room" << ' ' << getSearchValue() << std::endl;

        int course_length = getLongestCourseNameLength();
        int course_code_length = getLongestCourseCodeLength();
        int dept_code_length = getLongestDeptLength();
        int day_length = getLongestDayLength();

        // Draw
        out_str << std::left;
        out_str << std::setw(dept_code_length) << "Dept" << "  "
                << std::setw(course_code_length) << "Coursenum" << "  "
                << std::setw(course_length) << "Class Title" << "  "
                << std::setw(day_length) << "Day" << "  "
                << "Start Time" << "  "
                << "End Time"
                << std::endl;
        out_str << std::string(dept_code_length, '-') << "  "
                << std::string(course_code_length, '-') << "  "
                << std::string(course_length, '-') << "  "
                << std::string(day_length, '-') << "  "
                << std::string(10, '-') << "  "
                << std::string(8, '-')
                << std::endl;

        for (unsigned int i = 0; i < schedules.size(); i++)
        {
            Schedule s = schedules[i];
            out_str << std::setw(dept_code_length) << s.getDeptCode() << "  "
                    << std::setw(course_code_length) << s.getCourseCode() << "  "
                    << std::setw(course_length) << s.getCourseName() << "  "
                    << std::setw(day_length) << s.getDay().getCompleteDay() << "  "
                    << std::setw(10) << s.getStartTime() << "  "
                    << std::setw(8) << s.getEndTime()
                    << std::endl;
        }

        // Size
        out_str << getCollectionSize() << ' ' << "entries" << std::endl;
        out_str << std::endl;
    }
}

/**
 * Loop over Collection and draw Dept Table
 * Example:
    Dept ECSE
    Coursenum  Class Title                     Day        Start Time  End Time
    ---------  ------------------------------  ---------  ----------  --------
    1010-01    INTRODUCTION_TO_ECSE            Monday     12:00PM     01:50PM
    1010-01    INTRODUCTION_TO_ECSE            Thursday   12:00PM     01:50PM
    1010-02    INTRODUCTION_TO_ECSE            Thursday   04:00PM     05:50PM
    ...
    83 entries
 */
void SearchCollection::drawDeptTable(std::ofstream &out_str) {
    if (getCollectionSize() != 0) {
        // Title
        out_str << "Dept" << ' ' << getSearchValue() << std::endl;

        int course_length = getLongestCourseNameLength();
        int course_code_length = getLongestCourseCodeLength();
        int day_length = getLongestDayLength();

        // Table header
        out_str << std::left;
        out_str << std::setw(course_code_length) << "Coursenum" << "  "
                << std::setw(course_length) << "Class Title" << "  "
                << std::setw(day_length) << "Day" << "  "
                << "Start Time" << "  "
                << "End Time"
                << std::endl;
        out_str << std::string(course_code_length, '-') << "  "
                << std::string(course_length, '-') << "  "
                << std::string(day_length, '-') << "  "
                << std::string(10, '-') << "  "
                << std::string(8, '-')
                << std::endl;

        for (int i = 0; i < schedules.size(); i++) {
            Schedule s = schedules[i];
            // Fields
            out_str << std::setw(course_code_length) << s.getCourseCode() << "  "
                    << std::setw(course_length) << s.getCourseName() << "  "
                    << std::setw(day_length) << s.getDay().getCompleteDay() << "  "
                    << std::setw(10) << s.getStartTime() << "  "
                    << std::setw(8) << s.getEndTime()
                    << std::endl;
        }

        // Size
        out_str << getCollectionSize() << ' ' << "entries" << std::endl;
        out_str << std::endl;
    }
}

/**
 * Loop over Collection and draw day Table
 * Example:
    Day Monday
    CRN    Dept  Coursenum  Class Title                   Start Time  End Time  Room
    -----  ----  ---------  ----------------------------  ----------  --------  -----------
    64226  ECSE  4110-01    POWER_ENGINEERING_ANALYSIS    10:00AM     11:20AM   JONSSN_6309
    63144  ECSE  4530-01    DIGITAL_SIGNAL_PROCESSING     10:00AM     11:20AM   JONSSN_4104
    61556  ECSE  4900-01    MULTIDISCIPLINARY_CAP_DESIGN  10:00AM     11:50AM   JONSSN_3332
    ...
    22 entries
 */
void SearchCollection::drawDayTable(std::ofstream &out_str)
{
    if (getCollectionSize() != 0) {
        // Title
        out_str << "Day" << ' ' << getSearchValue() << std::endl;

        int CRN_length = getLongestCRNLength();
        int dept_code_length = getLongestDeptLength();
        int course_code_length = getLongestCourseCodeLength();
        int course_length = getLongestCourseNameLength();
        int room_length = getLongestRoomLength();

        // Draw
        out_str << std::left;
        out_str << std::setw(CRN_length) << "CRN" << "  "
                << std::setw(dept_code_length) << "Dept" << "  "
                << std::setw(course_code_length) << "Coursenum" << "  "
                << std::setw(course_length) << "Class Title" << "  "
                << "Start Time" << "  "
                << "End Time" << "  "
                << "Room"
                << std::endl;
        out_str << std::string(CRN_length, '-') << "  "
                << std::string(dept_code_length, '-') << "  "
                << std::string(course_code_length, '-') << "  "
                << std::string(course_length, '-') << "  "
                << std::string(10, '-') << "  "
                << std::string(8, '-') << "  "
                << std::string(room_length, '-')
                << std::endl;

        for (unsigned int i = 0; i < schedules.size(); i++)
        {
            Schedule s = schedules[i];
            out_str << std::setw(CRN_length) << s.getCRN() << "  "
                    << std::setw(dept_code_length) << s.getDeptCode() << "  "
                    << std::setw(course_code_length) << s.getCourseCode() << "  "
                    << std::setw(course_length) << s.getCourseName()<< "  "
                    << std::setw(10) << s.getStartTime() << "  "
                    << std::setw(8) << s.getEndTime() << "  "
                    << std::setw(room_length) << s.getRoom()
                    << std::endl;
        }

        // Size
        out_str << getCollectionSize() << ' ' << "entries" << std::endl;
        out_str << std::endl;
    }

}


// Sort Methods
/**
 * Sequence: day -> start_time -> course_code -> dept
 */
void SearchCollection::sortForRoomTable()
{
    std::stable_sort(schedules.begin(), schedules.end(), compareDeptCode);
    std::stable_sort(schedules.begin(), schedules.end(), compareCourseCode);
    std::stable_sort(schedules.begin(), schedules.end(), compareStartTime);
    std::stable_sort(schedules.begin(), schedules.end(), compareScheduleDay);
}

/**
 * Sequence: course_code -> day -> start_time
 */
void SearchCollection::sortForDeptTable()
{
    std::stable_sort(schedules.begin(), schedules.end(), compareStartTime);
    std::stable_sort(schedules.begin(), schedules.end(), compareScheduleDay);
    std::stable_sort(schedules.begin(), schedules.end(), compareCourseCode);
}

/**
 * Sequence: dept_code -> start_time -> course_code
 */
void SearchCollection::sortForDayTable()
{
    std::stable_sort(schedules.begin(), schedules.end(), compareCourseCode);
    std::stable_sort(schedules.begin(), schedules.end(), compareStartTime);
    std::stable_sort(schedules.begin(), schedules.end(), compareDeptCode);
}