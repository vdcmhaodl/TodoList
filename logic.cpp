#include "logic.h"
#include <fstream>
#include <sstream>

void Platform::addTask(baseTask* task) {
    tasks.push_back(task);
}
const std::vector<baseTask*>& Platform::getTasks() const {
    return tasks;
}
void Platform::deleteTask(size_t index) {
    if(index < tasks.size()) {
        delete tasks[index];
        tasks.erase(tasks.begin() + index);
    }
} 
void Platform::saveData(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    file << tasks.size() << "\n";
    
    for (auto task : tasks) {
        Date dueDate = task->getDueDate();
        Time estimatedTime = task->getEstimatedTime();
        std::string taskName = task->getTask();
        bool isDone = task->getHaveDone();
        std::string taskType = (dynamic_cast<dailyTask*>(task) != nullptr) ? "daily" : "onetime";
        
        file << taskType << "|" 
             << dueDate.getDate() << "|" 
             << estimatedTime.getHours() << "|"
             << estimatedTime.getMinutes() << "|"
             << estimatedTime.getSeconds() << "|"
             << (isDone ? "1" : "0") << "|" 
             << taskName << "\n";
    }
    
    file.close();
}
void Platform::loadData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    int taskCount;
    file >> taskCount;
    file.ignore();
    
    for (int i = 0; i < taskCount; ++i) {
        std::string line;
        if (!std::getline(file, line)) break;
        
        std::stringstream ss(line);
        std::string taskTypeStr, dateStr, hoursStr, minutesStr, secondsStr, doneStr, taskName;
        
        if (!std::getline(ss, taskTypeStr, '|')) continue;
        if (!std::getline(ss, dateStr, '|')) continue;
        if (!std::getline(ss, hoursStr, '|')) continue;
        if (!std::getline(ss, minutesStr, '|')) continue;
        if (!std::getline(ss, secondsStr, '|')) continue;
        if (!std::getline(ss, doneStr, '|')) continue;
        if (!std::getline(ss, taskName)) continue;
        
        // Parse date
        std::stringstream dateStream(dateStr);
        int day, month, year;
        char sep;
        dateStream >> day >> sep >> month >> sep >> year;
        
        // Parse time
        int hours = std::stoi(hoursStr);
        int minutes = std::stoi(minutesStr);
        int seconds = std::stoi(secondsStr);
        Time estimatedTime(hours, minutes, seconds);
        
        // Create task
        baseTask* loadedTask = nullptr;
        if (taskTypeStr == "daily") {
            loadedTask = new dailyTask(
                Date(day, month, year),
                estimatedTime,
                taskName
            );
        } 
        else {
            loadedTask = new oneTimeTask(
                Date(day, month, year),
                estimatedTime,
                taskName
            );
        }
        
        if (loadedTask->isValid()) {
            if (doneStr == "1") {
                loadedTask->setHaveDone();
            }
            tasks.push_back(loadedTask);
        } else {
            delete loadedTask;
        }
    }
    
    file.close();
}
Platform::~Platform() {
    for(auto task : tasks) {
        delete task;
    }
}