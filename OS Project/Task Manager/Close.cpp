#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    string name;
    int priority;
    int burstTime;
    int memoryUsage;
    int cpuUsage;
    bool completed;
    bool isProgram;
};

vector<Task> tasks;

void addTask() {
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


void displayTasks() {
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

void fcfs() {
    if (tasks.empty()) {
        cout << "No tasks to sort." << endl;
        return;
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.burstTime < b.burstTime;
    });

    cout << "Tasks sorted successfully (FCFS)." << endl;
}

void sjf() {
    if (tasks.empty()) {
        cout << "No tasks to sort." << endl;
        return;
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.burstTime < b.burstTime && a.priority < b.priority;
    });

    cout << "Tasks sorted successfully (SJF)." << endl;
}

void completeTask() {
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

    cout << "Task not found." << endl;
}

void killTask() {
    string name;
    cout << "Enter task name to kill: ";
    cin >> name;

    string command = "taskkill /f /im " + name;
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Task killed successfully." << endl;
    } else {
        cout << "Error: Unable to kill task." << endl;
    }
}
void displayTaskDetails(string taskName) {
    for (Task t : tasks) {
        if (t.name == taskName) {
            cout << "Task Details:" << endl;
            cout << "Name: " << t.name << endl;
            cout << "Priority: " << t.priority << endl;
            cout << "Burst Time: " << t.burstTime << endl;
            cout << "Memory Usage: " << t.memoryUsage << "%" << endl;
            cout << "CPU Usage: " << t.cpuUsage << "%" << endl;
            return;
        }
    }

    cout << "Task not found." << endl;
}
int main() {
    int choice;
    string taskName; // Declare taskName variable here

    do {
        cout << "Task Manager" << endl;
        cout << "------------" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Display Tasks" << endl;
        cout << "3. Sort Tasks (FCFS)" << endl;
        cout << "4. Sort Tasks (SJF)" << endl;
        cout << "5. Mark Task as Completed" << endl;
        cout << "6. Kill Task" << endl;
        cout << "7. Display Task Details" << endl;
        cout << "8. Exit" << endl;

        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                displayTasks();
                break;

            case 3:
                fcfs();
                break;

            case 4:
                sjf();
                break;

            case 5:
                completeTask();
                break;

            case 6:
                killTask();
                break;

            case 7:
                cout << "Enter task name: ";
                cin >> taskName;
                displayTaskDetails(taskName);
                break;

            case 8:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 8);

    return 0;
}
