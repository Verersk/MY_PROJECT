#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <regex>

using namespace std;


vector<string> ReadFromFile(string &filename) {

    vector<string> data;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << " Not found file " << endl;
        return data;
    }

    string line;

    while (getline(inFile, line)) {
        data.push_back(line);
    }

    inFile.close();
    return data;
}

void writeToFile(const string& filename, const vector<string>& data) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << " Can't open file " << endl;
        return;
    }

    for (const auto& line : data) {
        outFile << line << "\n";
    }

    outFile.close();
    cout << "Data successfully written to " << filename << endl;
}


int main() {

    string time_string;

    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    
    ostringstream oss;

    oss << put_time(localtime(&current_time), " %H:%M:%S");
    
    time_string = oss.str();

    ostringstream stream_match_prior;

    string prior;
    int P;


      string line = "ACDHF24 qwes fks @@@ Prior:4";
   // string line = "ACDHF24 SDJSsdj78";

      regex pattern(R"(.*Prior:([0-2])\s*$)");

      smatch match;

    if (regex_search(line, match, pattern)) {
        stream_match_prior << match[1];
        prior = stream_match_prior.str();

        P = stoi(prior);

        cout << "Prior = " << P << endl;

       // cout << match[1] << endl;
        cout << "found" << endl;
    }
    else {
        cout << "Not found" << endl;
    }




    // Форматируем время
    // cout << "Текущее время: " 
    //           << put_time(localtime(&current_time), " %H:%M:%S") 
    //           << endl;

   // cout << "Now time: " << time_string << endl;

//     string filenameIN = "/home/vlad/Test_Task/ReadWrite/INfile.txt";

   // string filenameOut = "/home/vlad/Test_Task/ReadWrite/INfile.txt";

//    // vector<string> readData = ReadFromFile(filenameIN);

//     cout << "Input data " << endl;
//     string data;

//     getline(cin, data);

//     vector<string> WriteData = {"Line 1", "Line 2"};

//     WriteData.push_back(data);

//    // cout << "Data from file " << endl;

//    writeToFile(filenameOut, WriteData);

//    cout << "Write succes " << endl;

    // for (auto &line : readData) {
    //     cout << line << endl;
    // }


    return 0;
}