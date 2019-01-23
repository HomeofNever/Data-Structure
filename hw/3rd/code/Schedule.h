#ifndef __SCHEDULE_H
#define __SCHEDULE_H

#include <string>
#include "Day.h"

class Schedule {
    public:
        // Constructors
        Schedule();
        /**
         * Initiate Object with parameters
         * @param CRN
         * @param dept_code
         * @param course_code
         * @param course_name
         * @param day
         * @param start_time
         * @param end_time
         * @param room
         */
        Schedule(int CRN,
                std::string &dept_code,
                std::string &course_code,
                std::string &course_name,
                Day day,
                std::string &start_time,
                std::string &end_time,
                std::string &room
        );

        // Accessors
        /**
         * Get CRN from private variable
         */
        int getCRN() const;

        /**
         * Get dept_code from private variable
         */
        std::string getDeptCode() const;

        /**
         * Get course_code from private variable
         */
        std::string getCourseCode() const;

        /**
         * Get course_name from private variable
         */
        std::string getCourseName() const;

        /**
         * Get Day object from private variable
         */
        Day getDay() const;

        /**
         * Get start_time string from private variable
         */
        std::string getStartTime() const;

        /**
         * Get end_time string from private variable
         */
        std::string getEndTime() const;

        /**
         * Get room string from private variable
         */
        std::string getRoom() const;

        // Helper methods
        // StartTime Helper
        /**
         * Get the zone of start_time (AM or PM)
         */
        char getStartTimeZone() const;

        /**
         * Get hour int of start_time (1-12)
         */
        int getStartTimeHour() const;

        /**
         * Get minute int of start_time (0-60)
         */
        int getStartTimeMinute() const;

        // Course Code Helper
        /**
         * Get course_code prefix (xxxx-yy first four digits)
         */
        int getCourseCodePrefix() const;

        /**
         * Get course_code suffix (xxxx-yy last two digits)
         */
        int getCourseCodeSuffix() const;

        /**
         * Print current object
         */
        void print();

    private:
        /**
         * Attributes for Schedules
         */
        int CRN;
        std::string dept_code;
        std::string course_code;
        std::string course_name;
        /**
         * Day Object for day comparison
         */
        Day day;
        std::string start_time;
        std::string end_time;
        std::string room;
};

/**
 * Day Comparison (use Day class's operator<)
 * @param one
 * @param other
 * @return
 */
bool compareScheduleDay(const Schedule &one, const Schedule &other);

/**
 * Start time comparison (AM-PM, hours, minutes)
 * @param one
 * @param other
 * @return
 */
bool compareStartTime(const Schedule &one, const Schedule &other);

/**
 * Course Code comparison (prefix-suffix)
 * @param one
 * @param other
 * @return
 */
bool compareCourseCode(const Schedule &one, const Schedule &other);

/**
 * Dept Comparison (Alphabet)
 *
 * @param one
 * @param other
 * @return
 */
bool compareDeptCode(const Schedule &one, const Schedule &other);

#endif