#include "add_Task.h"

baseTask::baseTask(Date date, const std::string& task, bool done) : dueDate(date), task(task), haveDone(done) {
    Date today;
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
}
baseTask::baseTask(Date date, const std::string& task) : dueDate(date), task(task) {
    Date today;
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
    haveDone = false;
}
baseTask::baseTask(int day, int month, int year, const std::string& task) : dueDate(day, month, year), task(task) {
    Date today;
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
void dailyTask::checkRefresh() {
    Date today;

    if(today > dueDate) {
        dueDate = today;
        haveDone = false;
    }
}
void oneTimeTask::checkRefresh() {
}