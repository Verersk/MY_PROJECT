#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <atomic>
#include <regex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;    // HIGH LOW

enum msgPrioritet {
    LOW,
    MIDDLE,
    HIGH
};

void inputThread(queue<string>& queue, mutex& mtx, condition_variable& cv, atomic<bool>& done);

void writeThread(queue<string>& queue, mutex& mtx, condition_variable& cv, atomic<bool>& done, string& filename);

void init_tread(string &filename);

