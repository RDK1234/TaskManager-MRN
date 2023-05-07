#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_PROCESSES = 10; // maximum number of processes to store

class Scheduler
{
public:
    virtual void schedule(vector<string>& processes) = 0;
    // abstract method to schedule the given processes
};

class FirstComeFirstServe : public Scheduler
{
public:
    void schedule(vector<string>& processes)
    {
        cout << "Scheduling processes using First Come First Serve algorithm..." << endl;
        for (int i = 0; i < processes.size(); i++)
        {
            cout << "Starting process " << processes[i] << "..." << endl;
            string proopen = "start \"" + processes[i] + "\"";
            int ret = system(proopen.c_str());
            if (ret == -1)
            {
                cerr << "Error starting process: " << processes[i] << endl;
            }
            cout << "Process " << processes[i] << " completed." << endl;
        }
        cout << "All processes completed." << endl;
    }
};

class ProcessManager
{
private:
    Scheduler* scheduler;
public:
    ProcessManager(Scheduler* scheduler) : scheduler(scheduler) {}

    void pro()
    {
        vector<string> processes; // vector to store processes

        while (processes.size() < MAX_PROCESSES)
        {
            string process;
            cout << "Enter the name of the process to start (or 'done' to stop) (Max:10): ";
            getline(cin, process);

            if (process == "done")
            {
                break; // stop entering processes if user enters 'done'
            }

            process.erase(process.begin(), find_if(process.begin(), process.end(), [](int c)
            {
                return !isspace(c);
            }));
            process.erase(find_if(process.rbegin(), process.rend(), [](int c)
            {
                return !isspace(c);
            }).base(), process.end());

            if (process.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-") != string::npos)
            {
                cerr << "Invalid process name: contains illegal characters." << endl;
                continue;
            }

            processes.push_back(process); // add process to the vector

            cout << "Process added successfully." << endl;
        }

        cout << "List of processes added:" << endl;
        for (int i = 0; i < processes.size(); i++)
        {
            cout << i + 1 << ". " << processes[i] << endl;
        }

        scheduler->schedule(processes);
    }
};

int main()
{
    FirstComeFirstServe scheduler;
    ProcessManager obj(&scheduler);
    obj.pro();
    return 0;
}
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_PROCESSES = 10; // maximum number of processes to store

void getProcessName(string& process) {
    cout << "Enter the name of the process to start (or 'done' to stop) (Max:10): ";
    getline(cin, process);
}

void trimProcessName(string& process) {
    process.erase(process.begin(), find_if(process.begin(), process.end(), [](int c) {
        return !isspace(c);
    }));
    process.erase(find_if(process.rbegin(), process.rend(), [](int c) {
        return !isspace(c);
    }).base(), process.end());
}

bool isValidProcessName(const string& process) {
    return (process.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-") == string::npos);
}

void addProcess(string processes[], int& numProcesses) {
    string process;
    getProcessName(process);

    if (process == "done") {
        return; // stop entering processes if user enters 'done'
    }

    trimProcessName(process);

    if (!isValidProcessName(process)) {
        cerr << "Invalid process name: contains illegal characters." << endl;
        return;
    }

    if (numProcesses >= MAX_PROCESSES) {
        cerr << "Max number of processes reached." << endl;
        return;
    }

    processes[numProcesses] = process; // add process to the array
    numProcesses++;

    cout << "Process added successfully." << endl;
}

void listProcesses(const string processes[], const int& numProcesses) {
    cout << "List of processes added:" << endl;
    for (int i = 0; i < numProcesses; i++) 
    {
       cout << i+1 << ". " << processes[i] << endl;
           string proopen = "start " + processes[i];

    int ret = system(proopen.c_str());

    if (ret == -1) {
        cerr << "Error starting process: " << processes[i] << endl;
    }
}
}

int main()
{
string processes[MAX_PROCESSES]; // array to store processes
int numProcesses = 0; // number of processes stored

