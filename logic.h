//platfrom here
#include "add_Task.h"
#include <vector>

class Platform {
private:
    std::vector<baseTask*> tasks;
public:
    void addTask(baseTask* task);
    const std::vector<baseTask*>& getTasks() const;
    void deleteTask(size_t index);

    void saveData(const std::string& filename);
    void loadData(const std::string& filename);
    ~Platform();
};