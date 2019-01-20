#ifndef __SCHEDULE_H
#define __SCHEDULE_H

#include <string>

class Schedule {
    public:
        // Constructor
        Schedule();
        Schedule(int CRN,
                std::string &dept_code,
                std::string &course_code,
                std::string &course_name,
                char day,
                std::string &start_time,
                std::string &end_time,
                std::string &room
        );

        // Accessor
        int getCRN() const;
        std::string getDeptCode() const;
        std::string getCourseCode() const;
        std::string getCourseName() const;
        char getDay() const;
        std::string getStartTime() const;
        std::string getEndTime() const;
        std::string getRoom() const;

        // Other methods
        int getDayIndex() const;
        std::string getCompleteDay() const;
        void print();

    private:
        int CRN;
        std::string dept_code;
        std::string course_code;
        std::string course_name;
        char day;
        std::string start_time;
        std::string end_time;
        std::string room;

        // Parse input
        // Init function
        void init(int CRN,
                  std::string &dept_code,
                  std::string &course_code,
                  std::string &course_name,
                  char day,
                  std::string &start_time,
                  std::string &end_time,
                  std::string &room);
};

bool compareDay(Schedule &one, Schedule &other);
bool compareStartHour(Schedule &one, Schedule &other);
bool compareCourseCode(Schedule &one, Schedule &other);

#endif