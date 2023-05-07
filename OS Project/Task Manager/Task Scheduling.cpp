// // #include <boost/algorithm/string.hpp>
// #include <iostream>
// #include <string>
// // using namespace boost::algorithm;
// using namespace std;

// int main() 
// {
//     string process; 
//     cout << "Enter The Name of the Process to Start: ";
//     getline(cin, process);

//     string ght=trim(process);
//     cout << ght;
// }
    
//     if (process.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-") != string::npos) {
//         cerr << "Invalid process name: contains illegal characters." << endl;
//         return 1;
//     }

//     string proopen = "start " + process;

//     int ret = system(proopen.c_str());

//     if (ret == -1) {
//         cerr << "Error starting process: " << process << endl;
//         return 1;
//     }

//     return 0;
// }
