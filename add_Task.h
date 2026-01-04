#pragma once
#include <string>
#include "handle_date.h"
#include "time.h"

Time currentTime();
class baseTask {
protected:
    Date dueDate;
    Time estimatedTime;
    std::string task;
    bool isDue;
    bool haveDone;
    void checkDueStatus(bool &isDue);
public:
    baseTask(Date date, const std::string& task, bool done);
    baseTask(Date date, const std::string& task);
    baseTask(int day, int month, int year, const std::string& task);
    baseTask(Date date, Time time, const std::string& task);
    
    bool isValid();
    std::string getTask() const;
    Date getDueDate() const;
    Time getEstimatedTime() const;
    bool getIsDue() const;
    void setIsDue();
    bool getHaveDone() const;
    virtual void checkRefresh() = 0;
    void setHaveDone();
    void setEstimatedTime(Time time);
    void checkDueStatus();
    virtual ~baseTask() = default;
};

class dailyTask : public baseTask {
public:
    dailyTask(Date date, const std::string& task, bool done) : baseTask(date, task, done) {}
    dailyTask(Date date, const std::string& task) : baseTask(date, task) {}
    dailyTask(int day, int month, int year, const std::string& task) : baseTask(day, month, year, task) {}
    dailyTask(const std::string& task) : baseTask(Date(), task) {}
    dailyTask(Date date, Time time, const std::string& task) : baseTask(date, time, task) {}
    void checkRefresh() override;
};
class oneTimeTask : public baseTask {
public:
    oneTimeTask(Date date, const std::string& task, bool done) : baseTask(date, task, done) {}
    oneTimeTask(Date date, const std::string& task) : baseTask(date, task) {}
    oneTimeTask(int day, int month, int year, const std::string& task) : baseTask(day, month, year, task) {}
    oneTimeTask(Date date, Time time, const std::string& task) : baseTask(date, time, task) {}
    void checkRefresh() override;
};