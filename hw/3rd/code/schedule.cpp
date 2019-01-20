#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "schedule.h"


// Constructors
Schedule::Schedule() {
    CRN = 99999;
    dept_code = "CTSM";
    course_code = "0000-00";
    course_name = "PLACEHOLDER";
    day = 'N';
    start_time = "99:99AM";
    end_time = "99:99PM";
    room = "PLACEHOLDER_ROOM";
}

Schedule::Schedule(int CRN,
         std::string &dept_code,
         std::string &course_code,
         std::string &course_name,
         char day,
         std::string &start_time,
         std::string &end_time,
         std::string &room) 
{
    init(CRN, dept_code, course_code, course_name, day, start_time, end_time, room);
}

// Init
void Schedule::init(int CRN,
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
    this->day = day;
    this->start_time = start_time;
    this->end_time = end_time;
    this->room = room;
}

// Methods
// Get a printable version of a schedule.
// 61557 ECSE 4900-02 MULTIDISCIPLINARY_CAP_DESIGN MR 12:00PM 01:50PM JONSSN_3332
void Schedule::print()
{
    std::cout << CRN << ' ' << dept_code << ' ' << course_code << ' ' << course_name << ' ' << day << ' ' << start_time << ' ' << end_time << ' ' << room << std::endl;
}

// Accessor
int Schedule::getCRN() const
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

char Schedule::getDay() const
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

// Helper Accessor
// Day Helper
int Schedule::getDayIndex() const
{
    std::vector<char> days({ 'M', 'T', 'W', 'R', 'F'});

    return std::find(days.begin(), days.end(), day) - days.begin();
}

std::string Schedule::getCompleteDay() const
{
    std::vector<std::string> complete_days({ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"});

    return complete_days[getDayIndex()];
}


// StartTime Helper
char Schedule::getStartTimeZone() const
{
    return start_time[5];
}

int Schedule::getStartTimeHour() const
{
    return (int)start_time[0] * 10 + (int)start_time[1];
}

int Schedule::getStartTimeMinute() const
{
    return (int)start_time[3] * 10 + (int)start_time[4];
}

// Course Code Helper
int Schedule::getCourseCodePrefix() const
{
    return (int)course_code[0] * 1000 + (int)course_code[1] * 100 + (int)course_code[2] * 10 + (int)course_code[3];
}

int Schedule::getCourseCodeSuffix() const
{
    return (int)course_code[5] * 10 + (int)course_code[6];
}

// Compare
bool compareDay(const Schedule &one, const Schedule &other)
{
    int p = one.getDayIndex();
    int q = other.getDayIndex();

    return p < q;
}

// E.g. 04:50PM 05:49AM
bool compareStartTime(const Schedule &one, const Schedule &other)
{
    std::string t1 = one.getStartTime();
    std::string t2 = other.getStartTime();

    if (t1 == t2)
    {
        // It doesn't matter because they are the same
        return false;
    }

    char one_zone = one.getStartTimeZone();
    char other_zone = other.getStartTimeZone();

    // AM > PM
    if (one_zone != other_zone)
    {
        // the later the letter the lager it is.
        return one_zone < other_zone;
    } else {
        int one_hour = one.getStartTimeHour();
        int other_hour = other.getStartTimeHour();
        int one_minute = one.getStartTimeMinute();
        int other_minute = other.getStartTimeMinute();

        // 12 < 1 < 2 < 3..., so we change it into 0 to make things easier
        if (one_hour == 12) {
            other_hour = 0;
        }

        if (one_hour == 12) {
            other_hour = 0;
        }

        if (one_hour != other_hour)
        {
            return one_hour < other_hour;
        } else if (one_minute != other_minute) {
            return one_minute > other_minute;
        }

        // Should not be here.
        std::cerr << "error when comparing Hours" << std::endl;
        return false;
    }

}

bool compareCourseCode(const Schedule &one, const Schedule &other)
{
    std::string t1 = one.getCourseCode();
    std::string t2 = other.getCourseCode();

    if (t1 == t2)
    {
        return false;
    }

    // 1200-01 < 1200-02
    int t1_prefix = one.getCourseCodePrefix();
    int t1_suffix = one.getCourseCodeSuffix();
    int t2_prefix = other.getCourseCodePrefix();
    int t2_suffix = other.getCourseCodeSuffix();

    if (t1_prefix != t2_prefix)
    {
        return t1_prefix < t2_prefix;
    } else if (t1_suffix != t2_suffix) {
        return t1_suffix < t2_suffix;
    }

    // Should not happen;
    std::cerr << "Error when comparing Course Code.";
    return false;
}

bool compareDeptCode(const Schedule &one, const Schedule &other)
{
    return one.getDeptCode() < other.getDeptCode();
}