#ifndef CODE_DATE_H
#define CODE_DATE_H


#include <string>
#include <vector>

class Day {
public:
    // Constructors
    Day();
    /**
     * Constructor
     * @param day Letter by char ("M", "T", "W", "R", "F")
     */
    Day(char day);

    // Accessors
    /**
     * get Day Char (Origin input when constructing)
     */
    char getDay() const;
    /**
     * get Index of the day (0-4 correspond to Monday to Friday)
     */
    int getDayIndex() const;
    /**
     * get Complete name of the day ("Monday", "Tuesday", etc.)
     */
    std::string getCompleteDay() const;

private:
    /**
     * Char represent to the day. ("M", "T", etc.)
     */
    char day;
};

// Compare
/**
 * Compare two days by index
 */
bool operator< (const Day &one, const Day &other);

/**
 * Compare two day by char
 */
bool operator== (const Day &one, const Day &other);

// Helper
/**
 * Get all legal day objects
 */
std::vector<Day> getAllDay();

#endif //CODE_DATE_H
