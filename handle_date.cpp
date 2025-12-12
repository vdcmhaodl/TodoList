#include "handle_date.h"
#include <limits>

Date::Date() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1; // tm_mon is 0
    int currentYear = now->tm_year + 1900; // tm_year is years since 1900
    day = currentDay;
    month = currentMonth;
    year = currentYear;
}
bool Date::checkValid() {
    if(year < 0 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    if(month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        int maxDay = isLeap ? 29 : 28;
        if(day > maxDay) return false;
    } else if(month == 4 || month == 6 || month == 9 || month == 11) {
        if(day > 30) return false;
    } else {
        if(day > 31) return false;
    }
    return true;
}
Date& operator++(const Date& other, int) {
    Date* newDate = new Date(other.day, other.month, other.year);
    newDate->day += 1;
    bool valid = newDate->checkValid();
    while(!valid) {
        newDate->day = 1;
        newDate->month += 1;
        if(newDate->month > 12) {
            newDate->month = 1;
            newDate->year += 1;
        }
        valid = newDate->checkValid();
    }
    return *newDate;
}
Date& Date::operator=(const Date& other) {
    if(this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}
bool Date::operator>=(const Date& other) const {
    if(year != other.year) return year > other.year;
    if(month != other.month) return month > other.month;
    return day >= other.day;
}
bool Date::operator>(const Date& other) const {
    if(year != other.year) return year > other.year;
    if(month != other.month) return month > other.month;
    return day > other.day;
}
std::istream& operator>>(std::istream& in, Date& date) {
    char sep1, sep2;
    bool firstTry = true;
    do {
        if(!firstTry) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid date. Please enter again: ";
        }
        in >> date.day >> sep1 >> date.month >> sep2 >> date.year;
        firstTry = false;
    } while(date.checkValid() == false);
    return in;
}
std::string Date::getDate() const {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}