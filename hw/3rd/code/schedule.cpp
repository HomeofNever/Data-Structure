#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "schedule.h"


// Constructors
Schedule::Schedule() {
    CRN = 99999;
    dept_code = "CTSM";
    course_code = "0000-00";
    course_name = "PLACEHOLDER";
    day = "NA";
    start_time = "99:99AM";
    end_time = "99:99PM";
    room = "PLACEHOLDER_ROOM";
}

Schedule::Schedule(int CRN,
         std::string &dept_code,
         std::string &course_code,
         std::string &course_name,
         std::string &day,
         std::string &start_time,
         std::string &end_time,
         std::string &room) 
{
    init(CRN, dept_code, course_code, course_name, day, start_time, end_time, room);
}

Schedule::Schedule(std::string &line) 
{
    parse(line);
}

// Init
void Schedule::init(int CRN,
          std::string &dept_code,
          std::string &course_code,
          std::string &course_name,
          std::string &day,
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
void Schedule::parse(std::string &line) 
{
    int CRN;
    std::string dept_code;
    std::string course_code;
    std::string course_name;
    std::string day;
    std::string start_time;
    std::string end_time;
    std::string room;

    std::istringstream isline(line);

    isline >> CRN >> dept_code >> course_code >> course_name >> day >> start_time >> end_time >> room;

    init(CRN, dept_code, course_code, course_name, day, start_time, end_time, room);
}

// 61557 ECSE 4900-02 MULTIDISCIPLINARY_CAP_DESIGN MR 12:00PM 01:50PM JONSSN_3332
void Schedule::print()
{
    std::cout << CRN << ' ' << getDeptCode() << ' ' << course_code << ' ' << course_name << ' ' << day << ' ' << start_time << ' ' << end_time << ' ' << room << std::endl;
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

std::string Schedule::getDay() const
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

int Schedule::getDayIndex() const
{
    std::vector<char> days({ 'M', 'T', 'W', 'R', 'F'});

    return std::find(days.begin(), days.end(), day[0]) - days.begin();
}

std::string Schedule::getCompleteDay() const
{
    std::vector<std::string> complete_days({ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"});

    return complete_days[getDayIndex()];
}

// Compare
bool compareDay(Schedule &one, Schedule &other)
{
    int p = one.getDayIndex();
    int q = other.getDayIndex();

    if (p == q)
    {
        return compareStartHour(one, other);
    } else {
        return p < q;
    }
}

// E.g. 04:50PM 05:49AM
bool compareStartHour(Schedule &one, Schedule &other)
{
    std::string t1 = one.getStartTime();
    std::string t2 = other.getStartTime();

    if (t1 == t2)
    {
        return compareCourseCode(one, other);
    }

    // AM > PM
    if (t1[5] != t2[5])
    {
        // the later the letter the lager it is.
        return t1[5] > t2[5];
    } else {
        int t1_hour, t1_min, t2_hour, t2_min;

        std::istringstream t1_stream(t1);
        std::istringstream t2_stream(t2);

        t1_stream >> t1_hour >> t1_min;
        t2_stream >> t2_hour >> t2_min;

        if (t1_hour != t2_hour)
        {
            return t1_hour < t2_hour;
        } else if (t1_min != t2_min) {
            return t1_min < t2_min;
        }

    }

    // Should not be here.
    std::cerr << "error when comparing Hours" << std::endl;
    return false;
}

bool compareCourseCode(Schedule &one, Schedule &other)
{
    std::string t1 = one.getCourseCode();
    std::string t2 = other.getCourseCode();

    if (t1 == t2)
    {
        return compareDay(one, other);
    }

    // 1200-01 < 1200-02
    int t1_first, t1_second, t2_first, t2_second;

        std::istringstream t1_stream(t1);
        std::istringstream t2_stream(t2);

        t1_stream >> t1_first >> t1_second;
        t2_stream >> t2_first >> t2_second;

        if (t1_first != t2_first)
        {
            return t1_first < t2_first;
        } else if (t1_second != t2_second) {
            // Since parse will read `-`, which cause it as negative.
            // Reverse the comparison
            return t1_second > t2_second;
        } else {
            // Should not happened;
            std::cerr << "Error when comparing Course Code.";
            return false;
        }
}