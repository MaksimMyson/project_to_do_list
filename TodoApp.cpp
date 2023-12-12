#include "TodoApp.h"
using namespace std;

void TodoApp::addTask() {
    Task task;
    cout << "Title: ";
    getline(cin >> ws, task.title);

    cout << "Priority (high/medium/low): ";
    while (true) {
        getline(cin, task.priority);
        if (task.priority == "high" || task.priority == "medium" || task.priority == "low") {
            break;
        }
        else {
            cout << "Invalid priority. Please enter high, medium, or low: ";
        }
    }

    cout << "Description: ";
    getline(cin, task.description);

    cout << "Due date and time (year month day hour minute): ";
    cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

    tasks[taskCount++] = task;
    cout << "Task added.\n";
}

void TodoApp::deleteTask() {
    if (taskCount == 0) {
        cout << "The task list is empty.\n";
        return;
    }

    displayTasks();

    int index;
    cout << "Enter the task number to delete: ";
    cin >> index;

    if (index >= 1 && index <= taskCount) {
        cout << "You have deleted the task: " << tasks[index - 1].title << "\n";
        for (int i = index - 1; i < taskCount - 1; ++i) {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void TodoApp::editTask() {
    if (taskCount == 0) {
        cout << "The task list is empty.\n";
        return;
    }

    cout << "Choose the task number to edit:\n";
    displayTasks();

    int index;
    cin >> index;

    if (index >= 1 && index <= taskCount) {
        Task& task = tasks[index - 1];

        cout << "New title: ";
        getline(cin >> ws, task.title);

        cout << "New priority (high/medium/low): ";
        while (true) {
            getline(cin, task.priority);
            if (task.priority == "high" || task.priority == "medium" || task.priority == "low") {
                break;
            }
            else {
                cout << "Invalid priority. Please enter high, medium, or low: ";
            }
        }

        cout << "New description: ";
        getline(cin, task.description);

        cout << "New due date and time (year month day hour minute): ";
        cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

        cout << "Task edited.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}

void TodoApp::searchTasksByTitle() {
    string query;
    cout << "Enter the title for search: ";
    getline(cin >> ws, query);

    displayMatchingTasks([&](const Task& task) {
        return task.title.find(query) != string::npos;
        }, "Matching tasks by title:");
}

void TodoApp::searchTasksByPriority() {
    string query;
    cout << "Enter the priority for search: ";
    getline(cin >> ws, query);

    displayMatchingTasks([&](const Task& task) {
        return task.priority.find(query) != string::npos;
        }, "Matching tasks by priority:");
}

void TodoApp::searchTasksByDescription() {
    string query;
    cout << "Enter the description for search: ";
    getline(cin >> ws, query);

    displayMatchingTasks([&](const Task& task) {
        return task.description.find(query) != string::npos;
        }, "Matching tasks by description:");
}

void TodoApp::searchTasksByDueDateTime() {
    tm queryDateTime;
    cout << "Enter the date and time for search (year month day hour minute): ";
    cin >> get_time(&queryDateTime, "%Y %m %d %H %M");

    displayMatchingTasks([&](const Task& task) {
        return compareDateTime(task.due_datetime, queryDateTime);
        }, "Matching tasks by due date and time:");
}

void TodoApp::displayTasks() {
    if (taskCount == 0) {
        cout << "The task list is empty.\n";
        return;
    }

    cout << "Task list:\n";
    for (int i = 0; i < taskCount; ++i) {
        cout << i + 1 << ". " << tasks[i].title << "\n";
    }
    cout << "--------------------------------------\n";
}

bool TodoApp::compareDateTime(const tm& lhs, const tm& rhs) {
    return (lhs.tm_year == rhs.tm_year &&
        lhs.tm_mon == rhs.tm_mon &&
        lhs.tm_mday == rhs.tm_mday &&
        lhs.tm_hour == rhs.tm_hour &&
        lhs.tm_min == rhs.tm_min);
}

void TodoApp::displayMatchingTasks(const function<bool(const Task&)>& condition, const string& message) {
    cout << message << "\n";

    for (int i = 0; i < taskCount; ++i) {
        const Task& task = tasks[i];
        if (condition(task)) {
            displayTask(task);
        }
    }

    cout << "--------------------------------------\n";
}

void TodoApp::displayTask(const Task& task) {
    cout << "Title: " << task.title << "\n";
    cout << "Priority: " << task.priority << "\n";
    cout << "Description: " << task.description << "\n";
    cout << "Due date and time: " << put_time(&task.due_datetime, "%Y-%m-%d %H:%M") << "\n";
    cout << "--------------------------------------\n";
}
