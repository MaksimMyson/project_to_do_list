#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <functional>

using namespace std;

struct Task {
    string title;
    string priority;
    string description;
    tm due_datetime; // ��������� ��� ��������� ���� �� ����
};

class TodoApp {
private:
    Task tasks[100];
    int taskCount = 0;

public:
    // ��������� ���� ������
    void addTask() {
        Task task;
        cout << "�����: ";
        getline(cin >> ws, task.title);



        cout << "��������: ";
        getline(cin, task.priority);

        cout << "����: ";
        getline(cin, task.description);

        cout << "���� �� ��� ��������� (�� ����� ���� ������ �������): ";
        cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

        tasks[taskCount++] = task;
        cout << "������ ������.\n";
    }

    // ��������� ������
    void deleteTask() {
        if (taskCount == 0) {
            cout << "������ ����� �������.\n";
            return;
        }

        displayTasks();

        int index;
        cout << "������ ����� ������ ��� ���������: ";
        cin >> index;

        if (index >= 1 && index <= taskCount) {
            cout << "�� �������� ������: " << tasks[index - 1].title << "\n";
            for (int i = index - 1; i < taskCount - 1; ++i) {
                tasks[i] = tasks[i + 1];
            }
            taskCount--;
        }
        else {
            cout << "������� ����� ������.\n";
        }
    }

    // ����������� ������
    void editTask() {
        if (taskCount == 0) {
            cout << "������ ����� �������.\n";
            return;
        }

        cout << "������ ����� ������ ��� �����������:\n";
        displayTasks();

        int index;
        cin >> index;

        if (index >= 1 && index <= taskCount) {
            Task& task = tasks[index - 1];

            cout << "���� �����: ";
            getline(cin >> ws, task.title);

            cout << "����� ��������: ";
            getline(cin, task.priority);

            cout << "����� ����: ";
            getline(cin, task.description);

            cout << "���� ���� �� ��� ��������� (�� ����� ���� ������ �������): ";
            cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

            cout << "������ ������������.\n";
        }
        else {
            cout << "������� ����� ������.\n";
        }
    }

    // ����� ����� �� ������
    void searchTasksByTitle() {
        string query;
        cout << "������ ����� ��� ������: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.title.find(query) != string::npos;
            }, "Matching tasks by title:");
    }

    // ����� ����� �� ����������
    void searchTasksByPriority() {
        string query;
        cout << "������ �������� ��� ������: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.priority.find(query) != string::npos;
            }, "Matching tasks by priority:");
    }

    // ����� ����� �� ������
    void searchTasksByDescription() {
        string query;
        cout << "������ ���� ��� ������: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.description.find(query) != string::npos;
            }, "Matching tasks by description:");
    }

    // ����� ����� �� ����� �� ����� ���������
    void searchTasksByDueDateTime() {
        tm queryDateTime;
        cout << "������ ���� �� ��� ��� ������ (�� ����� ���� ������ �������): ";
        cin >> get_time(&queryDateTime, "%Y %m %d %H %M");

        displayMatchingTasks([&](const Task& task) {
            return compareDateTime(task.due_datetime, queryDateTime);
            }, "Matching tasks by due date and time:");
    }

    // ³��������� �� ������
    void displayTasks() {
        if (taskCount == 0) {
            cout << "������ ����� �������.\n";
            return;
        }

        cout << "������ �����:\n";
        for (int i = 0; i < taskCount; ++i) {
            cout << i + 1 << ". " << tasks[i].title << "\n";
        }
        cout << "--------------------------------------\n";
    }

private:
    // �������� ���� �� ��� ���� ��'���� tm
    bool compareDateTime(const tm& lhs, const tm& rhs) {
        return (lhs.tm_year == rhs.tm_year &&
            lhs.tm_mon == rhs.tm_mon &&
            lhs.tm_mday == rhs.tm_mday &&
            lhs.tm_hour == rhs.tm_hour &&
            lhs.tm_min == rhs.tm_min);
    }

    // ³��������� ������, �� ������������� �����
    void displayMatchingTasks(const function<bool(const Task&)>& condition, const string& message = "Matching tasks:") {
        cout << message << "\n";

        for (int i = 0; i < taskCount; ++i) {
            const Task& task = tasks[i];
            if (condition(task)) {
                displayTask(task);
            }
        }

        cout << "--------------------------------------\n";
    }

    // ³��������� ��������� ������
    void displayTask(const Task& task) {
        cout << "�����: " << task.title << "\n";
        cout << "��������: " << task.priority << "\n";
        cout << "����: " << task.description << "\n";
        cout << "���� �� ��� ���������: " << put_time(&task.due_datetime, "%Y-%m-%d %H:%M") << "\n";
        cout << "--------------------------------------\n";
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    TodoApp todoApp;

    while (true) {
        cout << "������ �����:\n";
        cout << "1. ������ ������\n";
        cout << "2. �������� ������\n";
        cout << "3. ���������� ������\n";
        cout << "4. ����� ����� �� ������\n";
        cout << "5. ����� ����� �� ����������\n";
        cout << "6. ����� ����� �� ������\n";
        cout << "7. ����� ����� �� ����� �� ����� ���������\n";
        cout << "8. ³��������� ������\n";  // ³��������� �� ������
        cout << "9. �����\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            todoApp.addTask();
            break;
        case 2:
            todoApp.deleteTask();
            break;
        case 3:
            todoApp.editTask();
            break;
        case 4:
            todoApp.searchTasksByTitle();
            break;
        case 5:
            todoApp.searchTasksByPriority();
            break;
        case 6:
            todoApp.searchTasksByDescription();
            break;
        case 7:
            todoApp.searchTasksByDueDateTime();
            break;
        case 8:
            todoApp.displayTasks();
            break;
        case 9:
            return 0;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }

        cin.ignore();
        cin.clear();
    }

    return 0;
}
