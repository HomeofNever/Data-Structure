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
                std::string &day,
                std::string &start_time,
                std::string &end_time,
                std::string &room
        );
        Schedule(std::string &line);

        // Accessor
        int getCRN() const;
        std::string getDeptCode() const;
        std::string getCourseCode() const;
        std::string getCourseName() const;
        std::string getDay() const;
        std::string getStartTime() const;
        std::string getEndTime() const;
        std::string getRoom() const;

        int getDayIndex() const;
        std::string getCompleteDay() const;

        // Other methods
        void print();

    private:
        int CRN;
        std::string dept_code;
        std::string course_code;
        std::string course_name;
        std::string day;
        std::string start_time;
        std::string end_time;
        std::string room;

        // Parse input
        void parse(std::string &line);

        // Init function
        void init(int CRN,
                  std::string &dept_code,
                  std::string &course_code,
                  std::string &course_name,
                  std::string &day,
                  std::string &start_time,
                  std::string &end_time,
                  std::string &room);
};

bool compareDay(Schedule &one, Schedule &other);
bool compareStartHour(Schedule &one, Schedule &other);
bool compareCourseCode(Schedule &one, Schedule &other);

#endif