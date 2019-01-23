//
// Created by luox6 on 2019/1/23.
//

#ifndef LAB2_TIME_H
#define LAB2_TIME_H


class Time {
public:
    Time();
    Time(int hour, int minute, int second);

    // Accessors
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Mutator
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    // Member Functions
    void PrintAMPM() const;

private:
    int hour;
    int minute;
    int second;
};

bool IsEarlierThan(const Time &t1, const Time &t2);


#endif //LAB2_TIME_H
