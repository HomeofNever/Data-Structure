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
        // Day Helper
        int getDayIndex() const;
        std::string getCompleteDay() const;
        // StartTime Helper
        char getStartTimeZone() const;
        int getStartTimeHour() const;
        int getStartTimeMinute() const;
        // Course Code Helper
        int getCourseCodePrefix() const;
        int getCourseCodeSuffix() const;
        // Object Stringify
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

bool compareDay(const Schedule &one, const Schedule &other);
bool compareStartTime(const Schedule &one, const Schedule &other);
bool compareCourseCode(const Schedule &one, const Schedule &other);
bool compareDeptCode(const Schedule &one, const Schedule &other);

#endif