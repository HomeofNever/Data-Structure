#include "Day.h"
#include <vector>
#include <algorithm>

/**
 * Default Constructor will init an invalid char.
 * Since this Class should not be called directly (used by Schedule Class),
 * it is also not allowed to modify.
 */
Day::Day()
{
    day = 'N';
}

/**
 * Construct with char
 * @param day Char represents a specific day
 */
Day::Day(char day)
{
    this->day = day;
}

/**
 * Accessing private day variable
 * @return Origin Day char
 */
char Day::getDay() const
{
    return day;
}

// Day Helper
/**
 * It searches over an pre-defined vector and calculate the index of the Char
 * if no found, return -1 instead.
 * @return The index of the day in the given vector
 */
int Day::getDayIndex() const
{
    std::vector<char> days({ 'M', 'T', 'W', 'R', 'F' });

    for (unsigned int i = 0; i < days.size(); i++)
    {
        if (days[i] == day)
        {
            return i;
        }
    }

    return -1;
}

/**
 * It takes string from an pre-defined vector by index
 * @return The full name of the day.
 */
std::string Day::getCompleteDay() const
{
    std::vector<std::string> complete_days({ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"});

    return complete_days[getDayIndex()];
}

// Compare

/**
 * Compare two day object based on the index of the day
 *
 * @param one
 * @param other
 * @return one < other
 */
bool operator<(const Day &one, const Day &other)
{
    return one.getDayIndex() < other.getDayIndex();
}

/**
 * Compare two day object based on the char presented
 *
 * @param one
 * @param other
 */
bool operator==(const Day &one, const Day &other)
{
    return one.getDay() == other.getDay();
}

// Helper
/**
 * Build all five possible legal Days
 */
std::vector<Day> getAllDay()
{
    return std::vector<Day> {
        Day('M'),
        Day('T'),
        Day('W'),
        Day('R'),
        Day('F')
    };
}