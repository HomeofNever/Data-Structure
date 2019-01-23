#include <iostream>
#include "Time.h"

// Constructors
Time::Time()
{
    hour = 23;
    minute = 59;
    second = 59;
}

Time::Time(int hour, int minute, int second)
{
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

//Accessors
int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

// Mutator
void Time::setHour(int hour)
{
    this->hour = hour;
}

void Time::setMinute(int minute)
{
    this->minute = minute;
}

void Time::setSecond(int second)
{
    this->second = second;
}

// Member Functions
void Time::PrintAMPM() const
{
    if (getHour() == 0){
        std::cout << 12 << ':'
                  << getMinute() << ':'
                  << getSecond() << ' '
                  << "am" << std::endl;
    } else if (getHour() > 12)
    {
        // It should be PM
        std::cout << getHour() - 12 << ':'
                  << getMinute() << ':'
                  << getSecond() << ' '
                  << "pm" << std::endl;
    } else if (getHour() == 12)
    {
        std::cout << getHour() << ':'
                  << getMinute() << ':'
                  << getSecond() << ' '
                  << "pm" << std::endl;
    } else {
        std::cout << getHour() << ':'
                  << getMinute() << ':'
                  << getSecond() << ' '
                  << "am" << std::endl;
    }
}

// Compare

bool IsEarlierThan(const Time &t1, const Time &t2)
{
    if (t1.getHour() != t2.getHour()){
        return t1.getHour() < t2.getHour();
    } else if (t1.getMinute() != t2.getMinute())
    {
        return t1.getMinute() < t2.getMinute();
    } else if (t1.getSecond() != t2.getSecond())
    {
        return t1.getSecond() < t2.getSecond();
    }

    return false;
}