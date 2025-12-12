#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
class Date {
private:
    int day;
    int month;
    int year;
public:
    Date();
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
    bool checkValid();
    std::string getDate() const;

    Date& operator=(const Date& other);
    friend Date& operator++(const Date& other, int);
    friend std::istream& operator>>(std::istream& in, Date& date);
    bool operator>=(const Date& other) const;
    bool operator>(const Date& other) const;
};