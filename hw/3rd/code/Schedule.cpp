#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Schedule.h"
#include "Day.h"


// Constructors
Schedule::Schedule() {
    CRN = 99999;
    dept_code = "CTSM";
    course_code = "0000-00";
    course_name = "PLACEHOLDER";
    day = Day('N');
    start_time = "99:99AM";
    end_time = "99:99PM";
    room = "PLACEHOLDER_ROOM";
}

/**
 * Assign each external variable to the private variable within object
 *
 * @param CRN
 * @param dept_code
 * @param course_code
 * @param course_name
 * @param day
 * @param start_time
 * @param end_time
 * @param room
 */
Schedule::Schedule(std::string &CRN,
         std::string &dept_code,
         std::string &course_code,
         std::string &course_name,
         char day,
         std::string &start_time,
         std::string &end_time,
         std::string &room)
{
    this->CRN = CRN;
    this->dept_code = dept_code;
    this->course_code = course_code;
    this->course_name = course_name;
    this->day = Day(day);
    this->start_time = start_time;
    this->end_time = end_time;
    this->room = room;
}

// Methods
/**
 * Get a printable version of a schedule.
 * Test if accessors work properly.
 * Example:
 * 61557 ECSE 4900-02 MULTIDISCIPLINARY_CAP_DESIGN Monday 12:00PM 01:50PM JONSSN_3332
 */
void Schedule::print()
{
    std::cout << getCRN() << ' '
              << getDeptCode() << ' '
              << getCourseCode() << ' '
              << getCourseName() << ' '
              << getDay().getCompleteDay() << ' '
              << getStartTime() << ' '
              << getStartTimeHour() << ':' << getStartTimeMinute() << getStartTimeZone() << 'M' << ' '
              << getEndTime() << ' '
              << getRoom()
              << std::endl;
}

// Accessors
std::string Schedule::getCRN() const
{
    return CRN;
}

std::string Schedule::getDeptCode() const
{
    return dept_code;
}

std::string Schedule::getCourseCode() const
{
    return course_code;
}

std::string Schedule::getCourseName() const
{
    return course_name;
}

const Day& Schedule::getDay() const
{
    return day;
}

std::string Schedule::getStartTime() const
{
    return start_time;
}

std::string Schedule::getEndTime() const
{
    return end_time;
}

std::string Schedule::getRoom() const
{
    return room;
}

// Start Time Accessors
/**
 * Get the first letter of the start_time (A or P)
 * @return
 */
char Schedule::getStartTimeZone() const
{
    return start_time[5];
}

/**
 * Get the first two digits of start_time and parse into int
 */
int Schedule::getStartTimeHour() const
{
    return std::stoi(start_time.substr(0, 2));
}

/**
 * Get the last two digits of start time and parse into int
 */
int Schedule::getStartTimeMinute() const
{
    return std::stoi(start_time.substr(3, 2));
}

// Compare
/**
 * Use Day class operator< for comparison
 * @param one
 * @param other
 */
bool compareScheduleDay(const Schedule &one, const Schedule &other)
{
    return one.getDay() < other.getDay();
}

/**
 * Compare Start time:
 * 1. AM < PM
 * 2. Compare Hours (12 < 1 < 2 ... < 11)
 * 3. Compare minutes (0 < 1 ... < 59)
 *
 * @param one
 * @param other
 */
// E.g. 04:50PM 05:49AM
bool compareStartTime(const Schedule &one, const Schedule &other)
{
    std::string t1 = one.getStartTime();
    std::string t2 = other.getStartTime();

    if (t1 == t2)
    {
        return false;
    }

    char one_zone = one.getStartTimeZone();
    char other_zone = other.getStartTimeZone();

    // AM < PM
    if (one_zone != other_zone)
    {
        // the later the letter the larger it is. (A < Z, B < C, etc.)
        return one_zone < other_zone;
    } else {
        int one_hour = one.getStartTimeHour();
        int other_hour = other.getStartTimeHour();
        int one_minute = one.getStartTimeMinute();
        int other_minute = other.getStartTimeMinute();

        // 12 < 1 < 2 < 3..., so we change it into 0 to make things easier
        if (one_hour == 12) {
            one_hour = 0;
        }

        if (other_hour == 12) {
            other_hour = 0;
        }

        if (one_hour != other_hour)
        {
            return one_hour < other_hour;
        } else if (one_minute != other_minute) {
            return one_minute < other_minute;
        }

        // Should not be here.
        std::cerr << "error when comparing Hours" << std::endl;
        return false;
    }

}

/**
 * Compare course_code
 *
 * @param one
 * @param other
 */
bool compareCourseCode(const Schedule &one, const Schedule &other)
{
    std::string t1 = one.getCourseCode();
    std::string t2 = other.getCourseCode();

    return t1 < t2;
}

/**
 * Compare dept_code
 * Use default String comparison (Alphabet)
 *
 * @param one
 * @param other
 */
bool compareDeptCode(const Schedule &one, const Schedule &other)
{
    return one.getDeptCode() < other.getDeptCode();
}