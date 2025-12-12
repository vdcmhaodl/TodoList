#include "add_Task.h"
#include <iostream>
#include <vector>
#include <iomanip> // Thư viện để căn lề bảng (frontend)

// Một số mã màu để làm đẹp (Frontend)
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BOLD = "\033[1m";

void printLine(int width) {
    std::cout << "  +" << std::string(width - 4, '-') << "+\n";
}

void showHeader() {
    std::cout << "\n  " << BOLD << "MY TODO LIST" << RESET << "\n";
    printLine(60);
    std::cout << "  | " << std::left << std::setw(4) << "ID"
              << "| " << std::setw(25) << "Task Name"
              << "| " << std::setw(12) << "Due Date"
              << "| " << std::setw(10) << "Status" << " |\n";
    printLine(60);
}

void showTasks(const std::vector<baseTask*>& list) {
    if (list.empty()) {
        std::cout << "  | " << std::setw(54) << "No tasks yet! Let's add some." << " |\n";
    } else {
        for (size_t i = 0; i < list.size(); ++i) {
            std::string status = list[i]->getHaveDone() ? (GREEN + "DONE" + RESET) : (list[i]->getIsDue() ? (RED + "LATE" + RESET) : (YELLOW + "TODO" + RESET));
            
            // Tính toán độ dài chuỗi thực tế để căn chỉnh vì mã màu làm lệch setw
            int padding = list[i]->getHaveDone() ? 9 : 0; 

            std::cout << "  | " << std::left << std::setw(4) << i + 1
                      << "| " << std::setw(25) << list[i]->getTask()
                      << "| " << std::setw(12) << list[i]->getDueDate().getDate()
                      << "| " << std::setw(10 + padding) << status << " |\n";
        }
    }
    printLine(60);
}

int main() {
    std::vector<baseTask*> todoList;
    int choice;

    while (true) {
        // Clear màn hình (tuỳ hệ điều hành, system("cls") cho Win, "clear" cho Mac/Linux)
        // std::cout << "\033[2J\033[1;1H"; 
        for (auto& task : todoList) {
            task->checkRefresh();
        }
        showHeader();
        showTasks(todoList);

        std::cout << "\n  [1] Add daily Task  [2] Add one-time Task  [3] Mark Done  [0] Exit\n";
        std::cout << "  Select option: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            std::cin.ignore(); // Xóa bộ nhớ đệm
            std::string name;
            Date date = Date();
            
            std::cout << "\n  Enter task name: ";
            std::getline(std::cin, name);
            dailyTask* newTask = new dailyTask(date, name);
            todoList.push_back(newTask);
            std::cout << "  " << GREEN << "Task added successfully!" << RESET << "\n";
        }
        else if (choice == 2) {
            std::cin.ignore();
            std::string name;
            Date date;
            
            std::cout << "\n  Enter task name: ";
            std::getline(std::cin, name);
            std::cout << "  Enter due date (dd/mm/yyyy): ";
            std::cin >> date;
            
            oneTimeTask* newTask = new oneTimeTask(date, name);
            todoList.push_back(newTask);
            std::cout << "  " << GREEN << "Task added successfully!" << RESET << "\n";
        }
        else if (choice == 3) {
            int id;
            std::cout << "  Enter ID to mark done: ";
            std::cin >> id;
            if (id > 0 && id <= (int)todoList.size()) {
                todoList[id - 1]->setHaveDone();
                std::cout << "  " << GREEN << "Great job! Task completed." << RESET << "\n";
            } else {
                std::cout << "  " << RED << "Invalid ID!" << RESET << "\n";
            }
        }
    }

    return 0;
}