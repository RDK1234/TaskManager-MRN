//Code for Task Manager
//Done using essentially FCFS algorithm and Priority Scheduling
//Code by:-
//Manas Tiwari
//Ritesh Dhiman
//Nitish Sharma1


#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <queue>
#include <chrono>
#include <fstream>
#include <time.h>
//to add time functionality

using namespace std;

const int MAX_PROCESSES = 10;

void getProcessName(string& process)
{
    cout << "Enter the name of the process to start (or 'done' to stop) (Max:10): ";
    getline(cin, process);
}

void trimProcessName(string& process)
{
    process.erase(process.begin(), find_if(process.begin(), process.end(), [](int c)
    {
        return !isspace(c);
    }));
    process.erase(find_if(process.rbegin(), process.rend(), [](int c)
    {
        return !isspace(c);
    }).base(), process.end());
}

bool isValidProcessName(const string& process)
{
    return (process.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-") == string::npos);
}

void addProcess(queue<string>& processes)
{
    string process;
    getProcessName(process);

    if (process == "done")
    {
        return;
    }

    trimProcessName(process);

    if (!isValidProcessName(process))
    {
        cerr << "Invalid process name: contains illegal characters." << endl;
        return;
    }

    processes.push(process);
    cout << "Process added successfully." << endl;
}

void addProcess(priority_queue<pair<int, string>>& processes)
{
    string process;
    int priority;
    cout << "Enter the name of the process to start (or 'done' to stop) (Max:10): ";
    getline(cin, process);

    if (process == "done")
    {
        return;
    }

    trimProcessName(process);

    if (!isValidProcessName(process))
    {
        cerr << "Invalid process name: contains illegal characters." << endl;
        return;
    }

    cout << "Enter the priority level for this process (1-10): ";
    cin >> priority;

    if (priority < 1 || priority > 10)
    {
        cerr << "Invalid priority level. Priority level must be between 1 and 10." << endl;
        return;
    }

    processes.push(make_pair(priority, process));
    cout << "Process added successfully." << endl;
}

void listProcesses(queue<string>& processes)
{
    cout << "List of processes added:" << endl;
    int i = 1;
    while (!processes.empty()) {
        cout << i << ". " << processes.front() << endl;

        // Start process
        system(processes.front().c_str());

        processes.pop();
        i++;
    }
}

void listProcesses(priority_queue<pair<int, string>>& processes)
{
    cout << "List of processes added:" << endl;
    int i = 1;
    while (!processes.empty())
    {
        cout << i << ". " << processes.top().second << " (priority: " << processes.top().first << ")" << endl;

        // Start process
        string proopen = "start " + processes.top().second;
        int ret = system(proopen.c_str());
        if (ret == -1)
        {
            cerr << "Error starting process: " << processes.top().second << endl;
        }

        processes.pop();
        i++;
    }
}

class FCFS
{
private:
    queue<string> processes;

public:
    void addProcess()
    {
        string process;
        getProcessName(process);
            if (process == "done")
    {
        return;
    }

    trimProcessName(process);

    if (!isValidProcessName(process))
    {
        cerr << "Invalid process name: contains illegal characters." << endl;
        return;
    }

    processes.push(process);
    cout << "Process added successfully." << endl;
}

void listProcesses()
{
    cout << "List of processes added:" << endl;
    int i = 1;
    while (!processes.empty()) {
        cout << i << ". " << processes.front() << endl;

        // Start process
        system(processes.front().c_str());

        processes.pop();
        i++;
    }
}
};

int main()
{
cout << "Welcome to the Task Manager" << endl;
cout << "Choose an option below:" << endl;
int choice = 0;

while (choice != 4)
{
    cout << "1. Add process (FCFS)" << endl;
    cout << "2. Add process (Priority Scheduling)" << endl;
    cout << "3. List processes" << endl;
//    cout << "4. Done" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
    {
        FCFS fcfs;
        fcfs.addProcess();
        break;
    }
    case 2:
    {
        priority_queue<pair<int, string>> processes;
        addProcess(processes);
        break;
    }
    case 3:
    {
        cout << "Choose an option below:" << endl;
        cout << "1. List processes (FCFS)" << endl;
        cout << "2. List processes (Priority Scheduling)" << endl;
        cout << "Enter your choice: ";
        int subChoice;
        cin >> subChoice;
        cin.ignore();
        switch (subChoice)
        {
        case 1:
        {
            FCFS fcfs;
            fcfs.listProcesses();
            break;
        }
        case 2:
        {
            priority_queue<pair<int, string>> processes;
            listProcesses(processes);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
        }
        break;
    }
    case 4:
        cout << "Goodbye!" << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}

return 0;
}

