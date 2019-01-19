#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "schedule.h"

void process(std::ifstream &in_str, std::vector<Schedule> &vec)
{
    std::string line;

    while (getline(in_str, line))
    {
        vec.push_back(Schedule(line));
    }
}

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

void room(std::vector<Schedule> &vec, std::vector< std::vector<Schedule> > &result)
{
    std::vector<std::string> unique_room;
    for (unsigned int i = 0; i < vec.size(); i++)
    {

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

/*
Room DARRIN_330
Dept  Coursenum  Class Title        Day      Start Time  End Time
----  ---------  -----------------  -------  ----------  --------
ECSE  2010-01    ELECTRIC_CIRCUITS  Monday   07:00PM     08:50PM
ECSE  2410-01    SIGNALS_&_SYSTEMS  Tuesday  08:30AM     09:50AM
ECSE  2410-01    SIGNALS_&_SYSTEMS  Friday   08:30AM     09:50AM
3 entries
*/
void drawRoomTable(std::vector<Schedule> &vec, std::ofstream &out_str)
{
    int course_length = 11;
    int day_length = 6;

    // Calculation
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].getCourseName().size() > course_length)
        {
            course_length = vec[i].getCourseName().size();
        }
        if (vec[i].getCompleteDay().size() > day_length)
        {
            day_length = vec[i].getCompleteDay().size();
        }
    }

    // Sort
    struct {
        bool operator()(Schedule &a, Schedule &b) const
        {
            return compareDay(a, b);
        }
    } customLess;

    std::sort(vec.begin(), vec.end(), customLess);

    // Draw
    out_str << std::left;
    out_str << "Dept" << "  " << "Coursenum" << "  " << std::setw(course_length) << "Class Title" << "  " << std::setw(day_length) << "Day" << "  " << "Start Time" << "  " << "End Time" << std::endl;
    out_str << std::string(4, '-') << "  " << std::string(9, '-') << "  " << std::string(course_length, '-') << "  " << std::string(day_length, '-') << "  " << std::string(10, '-') << "  " << std::string(8, '-') << std::endl;

    for (int i = 0; i < vec.size(); i++)
    {
        Schedule &s = vec[i];
        out_str << s.getDeptCode() << "  " << std::setw(9) << s.getCourseCode() << "  " << std::setw(course_length) << s.getCourseName() << "  " << std::setw(day_length) << s.getCompleteDay() << "  " << std::setw(10) << s.getStartTime() << "  " << std::setw(8) << s.getEndTime() << std::endl;
    }
}

void drawDeptTable(std::vector<Schedule> &vec)
{

}

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
            drawRoomTable(result, out_str);
        }
        else
        {
            // All Room
            std::vector< std::vector<Schedule> > result;
            room(vec, result);
        }
    }
    else if (operation == "dept")
    {
        if (argc > 4)
        {
            std::vector<Schedule> result;
            std::string key(argv[4]);
            dept(key, vec, result);
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