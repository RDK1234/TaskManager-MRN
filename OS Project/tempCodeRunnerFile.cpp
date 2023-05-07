#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Task {
public:
    string name;
    int priority;
    int burstTime;
    int memoryUsage;
    int cpuUsage;
    bool completed;
    bool isProgram;
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask();
    void displayTasks();
    void fcfs();
    void sjf();
    void completeTask();
    void killTask();
    void displayTaskDetails(string taskName);
};

void TaskManager::addTask() {
    Task t;

    cout << "Enter task name: ";
    cin >> t.name;

    cout << "Enter task priority (1-10): ";
    cin >> t.priority;

    cout << "Enter task burst time: ";
    cin >> t.burstTime;

    cout << "Enter task memory usage: ";
    cin >> t.memoryUsage;

    cout << "Enter task CPU usage: ";
    cin >> t.cpuUsage;

    t.completed = false;

    tasks.push_back(t);

    cout << "Task added successfully!" << endl;

    // Launch the program if its name is entered as a task
    if (t.name.find(".exe") != string::npos) {
        cout << "Launching program: " << t.name << endl;
        system(t.name.c_str());
        t.isProgram = true;  // set flag to true if task is a program
    }
}

void TaskManager::displayTasks() {
    if (tasks.empty()) {
        cout << "No tasks to display." << endl;
        return;
    }

    cout << "Task\tPriority\tBurst Time\tMemory Usage\tCPU Usage\tCompleted" << endl;

    for (Task t : tasks) {
        cout << t.name << "\t" << t.priority << "\t\t" << t.burstTime << "\t\t"
             << t.memoryUsage << "\t\t" << t.cpuUsage << "\t\t";

        if (t.completed) {
            cout << "Yes";
        } else {
            cout << "No";
        }

        cout << endl;
    }
}

void TaskManager::fcfs() {
    if (tasks.empty()) {
        cout << "No tasks to sort." << endl;
        return;
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.burstTime < b.burstTime;
    });

    cout << "Tasks sorted successfully (FCFS)." << endl;
}

void TaskManager::sjf() {
    if (tasks.empty()) {
        cout << "No tasks to sort." << endl;
        return;
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.burstTime < b.burstTime && a.priority < b.priority;
    });

    cout << "Tasks sorted successfully (SJF)." << endl;
}

void TaskManager::completeTask() {
    string taskName;

    cout << "Enter the name of the task to mark as completed: ";
    cin >> taskName;

    for (Task& t : tasks) {
        if (t.name == taskName) {
            t.completed = true;
            cout << "Task marked as completed successfully." << endl;

            // close the opened task if it was completed
            if (t.name == "chrome.exe") {
                system("taskkill /f /im chrome.exe");
                cout << "Chrome task killed successfully." << endl;
            }

            return;
        }
    }

    void TaskManager::killTask() {
    string taskName;
    cout << "Enter the name of the task to kill: ";
    cin >> taskName;

    for (Task& t : tasks) {
        if (t.name == taskName) {
            // close the opened task if it is a program
            if (t.isProgram) {
                system("taskkill /f /im " + t.name);
                cout << t.name << " killed successfully." << endl;
            } else {
                cout << t.name << " cannot be killed as it is not a program." << endl;
            }

            return;
        }
    }

    cout << "Task not found." << endl;
    }

    void TaskManager::displayTaskDetails(string taskName) {
    bool taskFound = false;
    for (Task t : tasks) {
    if (t.name == taskName) {
        taskFound = true;
        cout << "Task Details:" << endl;
        cout << "Name: " << t.name << endl;
        cout << "Priority: " << t.priority << endl;
        cout << "Burst Time: " << t.burstTime << endl;
        cout << "Memory Usage: " << t.memoryUsage << endl;
        cout << "CPU Usage: " << t.cpuUsage << endl;
        cout << "Completed: " << (t.completed ? "Yes" : "No") << endl;

        break;
    }
}

if (!taskFound) {
    cout << "Task not found." << endl;
}
}

int main() {
TaskManager taskManager;
int choice;

do {
    cout << endl << "Task Manager Menu" << endl;
    cout << "1. Add a new task" << endl;
    cout << "2. Display all tasks" << endl;
    cout << "3. Sort tasks (FCFS)" << endl;
    cout << "4. Sort tasks (SJF)" << endl;
    cout << "5. Mark a task as completed" << endl;
    cout << "6. Kill a task" << endl;
    cout << "7. Display task details" << endl;
    cout << "8. Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            taskManager.addTask();
            break;

        case 2:
            taskManager.displayTasks();
            break;

        case 3:
            taskManager.fcfs();
            break;

        case 4:
            taskManager.sjf();
            break;

        case 5:
            taskManager.completeTask();
            break;

        case 6:
            taskManager.killTask();
            break;

        case 7: {
            string taskName;
            cout << "Enter the name of the task: ";
            cin >> taskName;
            taskManager.displayTaskDetails(taskName);
            break;
        }

        case 8:
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
} while (choice != 8);

return 0;
}