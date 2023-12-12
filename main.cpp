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
    tm due_datetime; // Структура для зберігання дати та часу
};

class TodoApp {
private:
    Task tasks[100];
    int taskCount = 0;

public:
    // Додавання нової справи
    void addTask() {
        Task task;
        cout << "Назва: ";
        getline(cin >> ws, task.title);



        cout << "Пріоритет: ";
        getline(cin, task.priority);

        cout << "Опис: ";
        getline(cin, task.description);

        cout << "Дата та час виконання (рік місяць день година хвилина): ";
        cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

        tasks[taskCount++] = task;
        cout << "Справа додана.\n";
    }

    // Видалення справи
    void deleteTask() {
        if (taskCount == 0) {
            cout << "Список справ порожній.\n";
            return;
        }

        displayTasks();

        int index;
        cout << "Введіть номер справи для видалення: ";
        cin >> index;

        if (index >= 1 && index <= taskCount) {
            cout << "Ви видалили справу: " << tasks[index - 1].title << "\n";
            for (int i = index - 1; i < taskCount - 1; ++i) {
                tasks[i] = tasks[i + 1];
            }
            taskCount--;
        }
        else {
            cout << "Невірний номер справи.\n";
        }
    }

    // Редагування справи
    void editTask() {
        if (taskCount == 0) {
            cout << "Список справ порожній.\n";
            return;
        }

        cout << "Оберіть номер справи для редагування:\n";
        displayTasks();

        int index;
        cin >> index;

        if (index >= 1 && index <= taskCount) {
            Task& task = tasks[index - 1];

            cout << "Нова назва: ";
            getline(cin >> ws, task.title);

            cout << "Новий пріоритет: ";
            getline(cin, task.priority);

            cout << "Новий опис: ";
            getline(cin, task.description);

            cout << "Нова дата та час виконання (рік місяць день година хвилина): ";
            cin >> get_time(&task.due_datetime, "%Y %m %d %H %M");

            cout << "Справа відредагована.\n";
        }
        else {
            cout << "Невірний номер справи.\n";
        }
    }

    // Пошук справ за назвою
    void searchTasksByTitle() {
        string query;
        cout << "Введіть назву для пошуку: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.title.find(query) != string::npos;
            }, "Matching tasks by title:");
    }

    // Пошук справ за пріоритетом
    void searchTasksByPriority() {
        string query;
        cout << "Введіть пріоритет для пошуку: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.priority.find(query) != string::npos;
            }, "Matching tasks by priority:");
    }

    // Пошук справ за описом
    void searchTasksByDescription() {
        string query;
        cout << "Введіть опис для пошуку: ";
        getline(cin >> ws, query);

        displayMatchingTasks([&](const Task& task) {
            return task.description.find(query) != string::npos;
            }, "Matching tasks by description:");
    }

    // Пошук справ за датою та часом виконання
    void searchTasksByDueDateTime() {
        tm queryDateTime;
        cout << "Введіть дату та час для пошуку (рік місяць день година хвилина): ";
        cin >> get_time(&queryDateTime, "%Y %m %d %H %M");

        displayMatchingTasks([&](const Task& task) {
            return compareDateTime(task.due_datetime, queryDateTime);
            }, "Matching tasks by due date and time:");
    }

    // Відобразити всі справи
    void displayTasks() {
        if (taskCount == 0) {
            cout << "Список справ порожній.\n";
            return;
        }

        cout << "Список справ:\n";
        for (int i = 0; i < taskCount; ++i) {
            cout << i + 1 << ". " << tasks[i].title << "\n";
        }
        cout << "--------------------------------------\n";
    }

private:
    // Порівняти дату та час двох об'єктів tm
    bool compareDateTime(const tm& lhs, const tm& rhs) {
        return (lhs.tm_year == rhs.tm_year &&
            lhs.tm_mon == rhs.tm_mon &&
            lhs.tm_mday == rhs.tm_mday &&
            lhs.tm_hour == rhs.tm_hour &&
            lhs.tm_min == rhs.tm_min);
    }

    // Відобразити справи, що задовольняють умову
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

    // Відобразити конкретну справу
    void displayTask(const Task& task) {
        cout << "Назва: " << task.title << "\n";
        cout << "Пріоритет: " << task.priority << "\n";
        cout << "Опис: " << task.description << "\n";
        cout << "Дата та час виконання: " << put_time(&task.due_datetime, "%Y-%m-%d %H:%M") << "\n";
        cout << "--------------------------------------\n";
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    TodoApp todoApp;

    while (true) {
        cout << "Оберіть опцію:\n";
        cout << "1. Додати справу\n";
        cout << "2. Видалити справу\n";
        cout << "3. Редагувати справу\n";
        cout << "4. Пошук справ за назвою\n";
        cout << "5. Пошук справ за пріоритетом\n";
        cout << "6. Пошук справ за описом\n";
        cout << "7. Пошук справ за датою та часом виконання\n";
        cout << "8. Відобразити справи\n";  // Відобразити всі справи
        cout << "9. Вийти\n";

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
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }

        cin.ignore();
        cin.clear();
    }

    return 0;
}
