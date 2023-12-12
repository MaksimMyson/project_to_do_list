#include "TodoApp.h"
using namespace std;

int main() {

    TodoApp todoApp;

    while (true) {
        cout << "Choose an option:\n";
        cout << "1. Add a task\n";
        cout << "2. Delete a task\n";
        cout << "3. Edit a task\n";
        cout << "4. Search tasks by title\n";
        cout << "5. Search tasks by priority\n";
        cout << "6. Search tasks by description\n";
        cout << "7. Search tasks by due date and time\n";
        cout << "8. Display tasks\n";
        cout << "9. Exit\n";

        int choice;
        cin >> choice;

        // Clear the input buffer after reading the choice
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}