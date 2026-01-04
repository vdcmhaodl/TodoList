#pragma once
#include <string>
#include "handle_date.h"
class Time {
private:
    int hours;
    int minutes;
    int seconds;
    int days;
public:
    Time() : hours(0), minutes(0), seconds(0), days(0) {}
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s), days(0) {}
    void setTime(int h, int m, int s);
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    int getDays() const;
    void TimeLogic();
    std::string toString() const;
};