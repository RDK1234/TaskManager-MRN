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