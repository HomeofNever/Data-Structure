#include "Schedule.h"
#include "Day.h"

int main()
{
    int CRN = 9999;
    std::string dept_code = "a";
    std::string course_code = "b";
    std::string course_name = "c";
    char d1= 'M';
    std::string start_time = "as";
    std::string end_time = "ad";
    std::string room = "asas";
    Schedule s = Schedule(CRN, dept_code, course_code, course_name, d1, start_time, end_time, room);
    Schedule d = Schedule();
    s.print();
}