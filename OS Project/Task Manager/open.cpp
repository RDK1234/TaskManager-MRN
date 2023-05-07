//Code for Task Manager
//Done using esentially FCFS algorithm
//Code by:-
//Manas Tiwari
//Ritesh Dhiman
//Nitish Sharma


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

class FCFS 
{
private:
    queue<string> processes;

public:
    void addProcess() 
    {
        ::addProcess(processes);
    }

    void runProcesses() 
{
    cout << "Executing processes using FCFS scheduling algorithm..." << endl;

    int i = 1;
    while (!processes.empty()) 
    {
        auto start_time = chrono::steady_clock::now();

        cout << i << ". " << processes.front() << " is running..." << endl;

        // Start process
        string proopen = "start " + processes.front();
        int ret = system(proopen.c_str());
        if (ret == -1) 
        {
            cerr << "Error starting process: " << processes.front() << endl;
        }

        // Get current time and store as start time
        start_time = chrono::steady_clock::now();

        // Wait for process to finish
        while (system(nullptr) && (system(("tasklist | find /i \"" + processes.front() + "\" > nul").c_str()) == 0)) 
        {
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        // Get end time and calculate elapsed time
        auto end_time = chrono::steady_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

        cout << "Elapsed time: " << elapsed_time.count() << "ms" << endl;

        // Remove process from queue
        processes.pop();
        i++;
    }
}
};

int main() 
{
    FCFS fcfs;
    bool ex = false;

    while (!ex) 
    {
        cout << "1. Add process"<<endl;
        cout << "2. Run processes"<<endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        switch (choice) 
        {
            case 1:
                fcfs.addProcess();
                break;
            case 2:
                fcfs.runProcesses();
                break;
            case 3:
                ex = true;
                break;
            default:
                cerr << "Invalid choice." << endl;
                break;
        }
    }

    return 0;
}
