#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <functional>

struct Task {
    std::string title;
    std::string priority;
    std::string description;
    tm due_datetime;
};

class TodoApp {
private:
    Task tasks[100];
    int taskCount = 0;

public:
    void addTask();
    void deleteTask();
    void editTask();
    void searchTasksByTitle();
    void searchTasksByPriority();
    void searchTasksByDescription();
    void searchTasksByDueDateTime();
    void displayTasks();

private:
    bool compareDateTime(const tm& lhs, const tm& rhs);
    void displayMatchingTasks(const std::function<bool(const Task&)>& condition, const std::string& message = "Matching tasks:");
    void displayTask(const Task& task);
};
