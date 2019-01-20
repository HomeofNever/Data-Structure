#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "schedule.h"

// Helper functions
int calculateCourseLength(std::vector<Schedule> &vec)
{
    int course_length = 11;

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].getCourseName().size() > course_length)
        {
            course_length = vec[i].getCourseName().size();
        }
    }

    return course_length;
}

int calculateDayLength(std::vector<Schedule> &vec)
{
    int day_length = 6;

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].getCompleteDay().size() > day_length)
        {
            day_length = vec[i].getCompleteDay().size();
        }
    }

    return day_length;
}

void sortRoomTable(std::vector<Schedule> &vec)
{
    std::sort(vec.begin(), vec.end(), [](Schedule &a, Schedule &b) {
        return compareDay(a, b);
    });
}

void sortDeptTable(std::vector<Schedule> &vec)
{
    std::sort(vec.begin(), vec.end(), [](Schedule &a, Schedule &b) {
        return compareCourseCode(a, b);
    });
}


void noDataNotice(std::ofstream &out_str)
{
    out_str << "No data available." << std::endl;
}

void process(std::ifstream &in_str, std::vector<Schedule> &vec)
{
    int CRN;
    std::string dept_code;
    std::string course_code;
    std::string course_name;
    std::string day;
    std::string start_time;
    std::string end_time;
    std::string room;

    while (in_str >> CRN >> dept_code >> course_code >> course_name >> day >> start_time >> end_time >> room)
    {
        for (unsigned i = 0; i < day.size(); i++)
        {
            char d = day[i];
            vec.push_back(Schedule(CRN, dept_code, course_code, course_name, d, start_time, end_time, room));
        }
    }
}

// Room parser
void room(std::string &key, std::vector<Schedule> &vec, std::vector<Schedule> &result)
{
    for (unsigned int i = 0; i < vec.size(); i++) 
    {
       if (vec[i].getRoom() == key)
       {
           result.push_back(vec[i]);
       }
    }
}

void room(std::vector<Schedule> &vec, std::vector<std::string> &room_list, std::vector< std::vector<Schedule> > &result)
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        // If room is not in the list, add to the list.
        if(std::find(room_list.begin(), room_list.end(), vec[i].getRoom()) == room_list.end()) {
            room_list.push_back(vec[i].getRoom());
        }
    }

    // Sort name
    std::sort(room_list.begin(), room_list.end());

    for (unsigned int i = 0; i < room_list.size(); i++) {
        std::vector<Schedule> single_room;
        room(room_list[i], vec, single_room);
        result.push_back(single_room);
    }
}

void dept(std::string &dept, std::vector<Schedule> &vec, std::vector<Schedule> &result)
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        if (vec[i].getDeptCode() == dept)
        {
            result.push_back(vec[i]);
        }
    }
}

// Draw Methods
/*
Room DARRIN_330
Dept  Coursenum  Class Title        Day      Start Time  End Time
----  ---------  -----------------  -------  ----------  --------
ECSE  2010-01    ELECTRIC_CIRCUITS  Monday   07:00PM     08:50PM
ECSE  2410-01    SIGNALS_&_SYSTEMS  Tuesday  08:30AM     09:50AM
ECSE  2410-01    SIGNALS_&_SYSTEMS  Friday   08:30AM     09:50AM
3 entries
*/
void drawRoomTable(std::string &room_name, std::vector<Schedule> &vec, std::ofstream &out_str)
{
    if (vec.size() == 0)
    {
        //noDataNotice(out_str);
    } else {
        out_str << "Room" << ' ' << room_name << std::endl;

        int course_length = calculateCourseLength(vec);
        int day_length = calculateDayLength(vec);
        sortRoomTable(vec);

        // Draw
        out_str << std::left;
        out_str << "Dept" << "  " << "Coursenum" << "  " << std::setw(course_length) << "Class Title" << "  " << std::setw(day_length) << "Day" << "  " << "Start Time" << "  " << "End Time" << std::endl;
        out_str << std::string(4, '-') << "  " << std::string(9, '-') << "  " << std::string(course_length, '-') << "  " << std::string(day_length, '-') << "  " << std::string(10, '-') << "  " << std::string(8, '-') << std::endl;

        for (int i = 0; i < vec.size(); i++)
        {
            Schedule &s = vec[i];
            out_str << s.getDeptCode() << "  " << std::setw(9) << s.getCourseCode() << "  " << std::setw(course_length) << s.getCourseName() << "  " << std::setw(day_length) << s.getCompleteDay() << "  " << std::setw(10) << s.getStartTime() << "  " << std::setw(8) << s.getEndTime() << std::endl;
        }

        // Size
        out_str << vec.size() << ' ' << "entries" << std::endl;
        out_str << std::endl;
    }
}

void drawMultipleRoomTable(std::vector<std::string> &room_list, std::vector< std::vector<Schedule> > result, std::ofstream &out_str)
{
    if (room_list.size() == 0) {
        noDataNotice(out_str);
    } else {
        for (unsigned int i = 0; i < room_list.size(); i++)
        {
            drawRoomTable(room_list[i], result[i], out_str);
        }
    }
}

void drawDeptTable(std::string &dept_name, std::vector<Schedule> &vec, std::ofstream &out_str)
{
    if (vec.size() == 0)
    {
        noDataNotice(out_str);
    } else {
        out_str << "Dept" << ' ' << dept_name << std::endl;

        int course_length = calculateCourseLength(vec);
        int day_length = calculateDayLength(vec);

        sortDeptTable(vec);

        // Draw
        out_str << std::left;
        out_str << "Coursenum" << "  " << std::setw(course_length) << "Class Title" << "  " << std::setw(day_length) << "Day" << "  " << "Start Time" << "  " << "End Time" << std::endl;
        out_str << std::string(9, '-') << "  " << std::string(course_length, '-') << "  " << std::string(day_length, '-') << "  " << std::string(10, '-') << "  " << std::string(8, '-') << std::endl;

        for (int i = 0; i < vec.size(); i++)
        {
            Schedule &s = vec[i];
            out_str << std::setw(9) << s.getCourseCode() << "  " << std::setw(course_length) << s.getCourseName() << "  " << std::setw(day_length) << s.getCompleteDay() << "  " << std::setw(10) << s.getStartTime() << "  " << std::setw(8) << s.getEndTime() << std::endl;
        }

        // Size
        out_str << vec.size() << ' ' << "entries" << std::endl;
        out_str << std::endl;
    }
}


// Main Entry
/*
scheduling.exe simple2.txt out_simple2_room.txt room
scheduling.exe simple2.txt out_simple2_room.txt room ACADMY_AUD
scheduling.exe simple2.txt out_simple2_dept_ECSE.txt dept ECSE
scheduling.exe simple2.txt out_simple2_custom.txt custom
*/
int main(int argc, char *argv[])
{
    // No matter what happened, 3 parameters are required.
    if (argc < 3)
    {
        std::cerr << "Program required at least 3 parameters to run." << std::endl;
        return 1;
    }

    // Input file name
    std::string input = argv[1];

    // Open input file
    std::ifstream in_str(input);
    if (!in_str.good())
    {
        std::cerr << "Can't open " << input << " to read." << std::endl;
        return 1;
    }

    // Output file name
    std::string output = argv[2];

    // Open output file
    std::ofstream out_str(output);
    if (!out_str.good())
    {
        std::cerr << "Can't open " << output << " to write." << std::endl;
        return 1;
    }

    // Possible operation: room / dept / custom
    std::string operation = argv[3];

    // Process Input
    std::vector<Schedule> vec;
    process(in_str, vec);

    // Decide which operation to go
    if (operation == "room")
    {
        if (argc > 4)
        {
            std::vector<Schedule> result;
            std::string key(argv[4]);

            room(key, vec, result);
            drawRoomTable(key, result, out_str);
        }
        else
        {
            // All Room
            std::vector<std::string> room_list;
            std::vector< std::vector<Schedule> > result;

            room(vec, room_list, result);
            drawMultipleRoomTable(room_list, result, out_str);
        }
    }
    else if (operation == "dept")
    {
        if (argc > 4)
        {
            std::vector<Schedule> result;
            std::string key(argv[4]);

            dept(key, vec, result);
            drawDeptTable(key, result, out_str);
        }
        else
        {
            std::cerr << "The function you enters requires 1 extra parameters." << std::endl;
            return 1;
        }
    }
    else if (operation == "custom")
    {
        // Custom
    }
    else
    {
        std::cerr << "The function you enters is not recognized." << std::endl;
        return 1;
    }

    in_str.close();
    out_str.close();
    
    return 0;
}