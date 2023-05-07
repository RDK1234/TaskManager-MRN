
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
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

string ipToString(DWORD ip) {
    in_addr addr;
    addr.S_un.S_addr = ip;
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr, buf, sizeof(buf));
    return string(buf);
}

void showNetworkUsage() {
    MIB_TCPTABLE_OWNER_PID tcpTable;
    DWORD size = 0;
    if (GetTcpTable(&tcpTable, &size, TRUE) == ERROR_INSUFFICIENT_BUFFER) {
        tcpTable = *reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(new char[size]);
        if (GetTcpTable(&tcpTable, &size, TRUE) != NO_ERROR) {
            cerr << "Failed to get TCP table: " << GetLastError() << endl;
            delete[] reinterpret_cast<char*>(&tcpTable);
            return;
        }
    } else {
        cerr << "Failed to get TCP table size: " << GetLastError() << endl;
        return;
    }

    cout << "Process\t\tLocal Address\t\tRemote Address\t\tState" << endl;

    for (DWORD i = 0; i < tcpTable.dwNumEntries; ++i) {
        auto& row = tcpTable.table[i];
        string processName = "Unknown";
        if (row.dwOwningPid != 0) {
            HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, row.dwOwningPid);
            if (process) {
                char buf[MAX_PATH];
                DWORD size = MAX_PATH;
                if (QueryFullProcessImageNameA(process, 0, buf, &size)) {
                    processName = buf;
                }
                CloseHandle(process);
            }
        }
        string localAddr = ipToString(row.dwLocalAddr) + ":" + to_string(htons(row.dwLocalPort));
        string remoteAddr = ipToString(row.dwRemoteAddr) + ":" + to_string(htons(row.dwRemotePort));
        cout << processName << "\t\t" << localAddr << "\t\t" << remoteAddr << "\t\t" << row.dwState << endl;
    }

    delete[] reinterpret_cast<char*>(&tcpTable);
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
    string taskName;

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
        cout << "8. Show All Processes" << endl;
        cout << "9. Show Network Usage" << endl;
        cout << "10. Exit" << endl;

        cout << "Enter your choice (1-9): ";
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
                cout << "Enter the name of the task to display details: ";
                cin >> taskName;
                displayTaskDetails(taskName);
                break;

            case 8:
                system("tasklist");
                break;
            case 9:
                showNetworkUsage();
                break;
            case 10:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                break;
        }

        cout << endl;

    } while (choice != 10);

    return 0;
}

