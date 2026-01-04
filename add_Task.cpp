#include "add_Task.h"

Time currentTime() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    return Time(now->tm_hour, now->tm_min, now->tm_sec);
}
void baseTask::checkDueStatus(bool &isDue) {
    Date today;
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        if(today == dueDate) {
            Time currTime = currentTime();
            if(currTime < estimatedTime) {
                isDue = false;
            } else {
                isDue = true;
            }
        } else {
        isDue = false;
        }
    }
}
baseTask::baseTask(Date date, const std::string& task, bool done) : dueDate(date), task(task), haveDone(done) {
    estimatedTime = Time(0, 0, 0);
    checkDueStatus(isDue);
}
baseTask::baseTask(Date date, const std::string& task) : dueDate(date), task(task) {
    estimatedTime = Time(0, 0, 0);
    checkDueStatus();
}
baseTask::baseTask(int day, int month, int year, const std::string& task) : dueDate(day, month, year), task(task) {
    estimatedTime = Time(0, 0, 0);
    Date today;
    if(today > dueDate) {
        isDue = true;
    } 
    else {
        isDue = false;
    }
    haveDone = false;
}
baseTask::baseTask(Date date, Time time, const std::string& task) : dueDate(date), estimatedTime(time), task(task) {
    Date today;
    checkDueStatus();
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
Time baseTask::getEstimatedTime() const {
    return estimatedTime;
}
void baseTask::setEstimatedTime(Time time) {
    estimatedTime = time;
    checkDueStatus();
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
void baseTask::checkDueStatus() {
    Date today;
    if(today > dueDate) {
        isDue = true;
    } 
    else if(today == dueDate) {
        if(estimatedTime < currentTime()) {
            isDue = true;
        }
        else {
            isDue = false;
        }
    }
    else {
        isDue = false;
    }
}
void dailyTask::checkRefresh() {
    Date today;

    if(today > dueDate) {
        dueDate = today;
        haveDone = false;
        isDue = false;
    }
}
void oneTimeTask::checkRefresh() {
}