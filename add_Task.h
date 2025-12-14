#pragma once
#include <string>
#include "handle_date.h"

class baseTask {
protected:
    Date dueDate;
    std::string task;
    bool isDue;
    bool haveDone;
public:
    baseTask(Date date, const std::string& task, bool done);
    baseTask(Date date, const std::string& task);
    baseTask(int day, int month, int year, const std::string& task);
    bool isValid();
    std::string getTask() const;
    Date getDueDate() const;
    bool getIsDue() const;
    void setIsDue();
    bool getHaveDone() const;
    virtual void checkRefresh() = 0;
    void setHaveDone();
    virtual ~baseTask() = default;
};

class dailyTask : public baseTask {
public:
    dailyTask(Date date, const std::string& task, bool done) : baseTask(date, task, done) {}
    dailyTask(Date date, const std::string& task) : baseTask(date, task) {}
    dailyTask(int day, int month, int year, const std::string& task) : baseTask(day, month, year, task) {}
    dailyTask(const std::string& task) : baseTask(Date(), task) {}
    void checkRefresh() override;
};
class oneTimeTask : public baseTask {
public:
    oneTimeTask(Date date, const std::string& task, bool done) : baseTask(date, task, done) {}
    oneTimeTask(Date date, const std::string& task) : baseTask(date, task) {}
    oneTimeTask(int day, int month, int year, const std::string& task) : baseTask(day, month, year, task) {}
    void checkRefresh() override;
};