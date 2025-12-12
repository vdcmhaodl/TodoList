#include "add_Task.h"

baseTask::baseTask(Date date, const std::string& task, bool done) : dueDate(date), task(task), haveDone(done) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1; // tm_mon is 0
    int currentYear = now->tm_year + 1900; // tm_year is years since 1900
    Date today = Date(currentDay, currentMonth, currentYear);
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
}
baseTask::baseTask(Date date, const std::string& task) : dueDate(date), task(task) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1; // tm_mon is 0
    int currentYear = now->tm_year + 1900; // tm_year is years since 1900
    Date today = Date(currentDay, currentMonth, currentYear);
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
    haveDone = false;
}
baseTask::baseTask(int day, int month, int year, const std::string& task) : dueDate(day, month, year), task(task) {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1; // tm_mon is 0
    int currentYear = now->tm_year + 1900; // tm_year is years since 1900
    Date today = Date(currentDay, currentMonth, currentYear);
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
    haveDone = false;
}
bool baseTask::isValid() {
    return dueDate.checkValid();
}
std::string baseTask::getTask() const {
    return task;
}
Date baseTask::getDueDate() const {
    return dueDate;
}
bool baseTask::getIsDue() const {
    return isDue;
}
void baseTask::setIsDue() {
    isDue = true;
}
bool baseTask::getHaveDone() const {
    return haveDone;
}
void baseTask::setHaveDone() {
    haveDone = true;
}
void baseTask::checkRefresh() {}
void dailyTask::checkRefresh() {
    Date today;

    if(today > dueDate) {
        dueDate = today;
        haveDone = false;
    }
}