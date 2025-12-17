// To-do List - Interactive CLI AI generated for testing
#include "logic.h"
#include "add_Task.h"
#include <iostream>
#include <string>
#include <limits>

void displayMenu() {
    std::cout << "\n========== TO-DO LIST MENU ==========" << std::endl;
    std::cout << "1. Add a new task" << std::endl;
    std::cout << "2. Display all tasks" << std::endl;
    std::cout << "3. Delete a task" << std::endl;
    std::cout << "4. Mark task as done" << std::endl;
    std::cout << "5. Check due tasks" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Enter your choice (1-8): ";
}

void displayTaskTypeMenu() {
    std::cout << "\n--- Select Task Type ---" << std::endl;
    std::cout << "1. One-Time Task (specific due date)" << std::endl;
    std::cout << "2. Daily Task (repeats every day)" << std::endl;
    std::cout << "Enter your choice (1-2): ";
}

void displayTasks(const Platform& platform) {
    const auto& tasks = platform.getTasks();
    
    if (tasks.empty()) {
        std::cout << "\nNo tasks in the list." << std::endl;
        return;
    }
    
    std::cout << "\n========== YOUR TASKS ==========" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "No. | Task Name                     | Due Date   | Type  | Status" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::string status = tasks[i]->getHaveDone() ? "Done" : "Pending";
        std::string dueStatus = tasks[i]->getIsDue() ? "[OVERDUE]" : "";
        
        // Determine task type using RTTI
        std::string taskType = (dynamic_cast<dailyTask*>(tasks[i]) != nullptr) ? "Daily" : "Once";
        
        std::cout << (i + 1) << "   | " 
                  << tasks[i]->getTask().substr(0, 27) << std::string(27 - std::min(size_t(27), tasks[i]->getTask().length()), ' ')
                  << " | " << tasks[i]->getDueDate().getDate() 
                  << " | " << taskType << " | " << status << " " << dueStatus << std::endl;
    }
    std::cout << std::string(70, '-') << std::endl;
}

int main() {
    Platform platform;
    int choice = 0;
    
    std::cout << "============================================" << std::endl;
    std::cout << "  Welcome to the Interactive To-Do List CLI" << std::endl;
    std::cout << "============================================" << std::endl;

    std::cout << "\n--- Load Data ---" << std::endl;
    std::string filename = "tasks.txt";
    
    try {
        platform.loadData(filename);
        std::cout << "✓ Data loaded successfully from " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✗ Error loading data: " << e.what() << std::endl;
    }
    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                // Add a new task
                std::cout << "\n--- Add New Task ---" << std::endl;
                displayTaskTypeMenu();
                int taskTypeChoice;
                std::cin >> taskTypeChoice;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string description;
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                baseTask* newTask = nullptr;
                if (taskTypeChoice == 1) {
                    int day, month, year;
                    
                    std::cout << "Enter day (1-31): ";
                    std::cin >> day;
                    
                    std::cout << "Enter month (1-12): ";
                    std::cin >> month;
                    
                    std::cout << "Enter year: ";
                    std::cin >> year;
                    newTask = new oneTimeTask(day, month, year, description);
                } else if (taskTypeChoice == 2) {
                    newTask = new dailyTask(description);
                } else {
                    std::cout << "\n✗ Invalid task type! Task not added." << std::endl;
                    break;
                }
                
                if (newTask->isValid()) {
                    platform.addTask(newTask);
                    std::cout << "\n✓ Task added successfully!" << std::endl;
                } else {
                    std::cout << "\n✗ Invalid date! Task not added." << std::endl;
                    delete newTask;
                }
                break;
            }
            
            case 2: {
                // Display all tasks
                displayTasks(platform);
                break;
            }
            
            case 3: {
                // Delete a task
                const auto& tasks = platform.getTasks();
                
                if (tasks.empty()) {
                    std::cout << "\nNo tasks to delete." << std::endl;
                    break;
                }
                
                displayTasks(platform);
                std::cout << "Enter task number to delete (0 to cancel): ";
                int taskNum;
                std::cin >> taskNum;
                
                if (taskNum > 0 && taskNum <= (int)tasks.size()) {
                    platform.deleteTask(taskNum - 1);
                    std::cout << "✓ Task deleted successfully!" << std::endl;
                } else if (taskNum != 0) {
                    std::cout << "✗ Invalid task number." << std::endl;
                }
                break;
            }
            
            case 4: {
                // Mark task as done
                const auto& tasks = platform.getTasks();
                
                if (tasks.empty()) {
                    std::cout << "\nNo tasks available." << std::endl;
                    break;
                }
                
                displayTasks(platform);
                std::cout << "Enter task number to mark as done (0 to cancel): ";
                int taskNum;
                std::cin >> taskNum;
                
                if (taskNum > 0 && taskNum <= (int)tasks.size()) {
                    tasks[taskNum - 1]->setHaveDone();
                    std::cout << "✓ Task marked as done!" << std::endl;
                } else if (taskNum != 0) {
                    std::cout << "✗ Invalid task number." << std::endl;
                }
                break;
            }
            
            case 5: {
                // Check due tasks
                std::cout << "\n--- Checking Due Status ---" << std::endl;
                const auto& tasks = platform.getTasks();
                
                int overdueCount = 0;
                for (auto task : tasks) {
                    if (task->getIsDue()) {
                        overdueCount++;
                        std::cout << "⚠ OVERDUE: " << task->getTask() 
                                  << " (Due: " << task->getDueDate().getDate() << ")" << std::endl;
                    }
                }
                
                if (overdueCount == 0) {
                    std::cout << "✓ No overdue tasks!" << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "\n--- Save Data ---" << std::endl;
                std::string filename = "tasks.txt";
                
                try {
                    platform.saveData(filename);
                    std::cout << "✓ Data saved successfully to " << filename << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "✗ Error saving data: " << e.what() << std::endl;
                }
                std::cout << "\nThank you for using To-Do List CLI. Goodbye!" << std::endl;
                return 0;
            }
            
            default:
                std::cout << "\n✗ Invalid choice. Please enter a number between 1 and 8." << std::endl;
        }
    }

    return 0;
}
