#include "time.h"

void Time::setTime(int h, int m, int s) {
    hours = h;
    minutes = m;
    seconds = s;
    TimeLogic();
}
int Time::getHours() const {
    return hours;
}
int Time::getMinutes() const {
    return minutes;
}
int Time::getSeconds() const {
    return seconds;
}
int Time::getDays() const {
    return days;
}
void Time::TimeLogic() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds = seconds % 60;
    } else if (seconds < 0) {
        int borrow = (abs(seconds) + 59) / 60;
        minutes -= borrow;
        seconds += borrow * 60;
    }

    if (minutes >= 60) {
        hours += minutes / 60;
        minutes = minutes % 60;
    } else if (minutes < 0) {
        int borrow = (abs(minutes) + 59) / 60;
        hours -= borrow;
        minutes += borrow * 60;
    }
    if (hours >= 24) {
        days += hours / 24;
        hours = hours % 24;
    } else if (hours < 0) {
        int dayBorrow = (-hours + 23) / 24;
        days -= dayBorrow;
        hours += dayBorrow * 24;
    }
}
bool Time::operator<(const Time& other) const {
    if (days != other.days) return days < other.days;
    if (hours != other.hours) return hours < other.hours;
    if (minutes != other.minutes) return minutes < other.minutes;
    return seconds < other.seconds;
}
std::string Time::toString() const {
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);
    return std::string(buffer);
}