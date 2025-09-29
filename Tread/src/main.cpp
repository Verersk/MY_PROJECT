#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <atomic>
#include "../lib/tread.h"

using namespace std;

string fileName;    


int main() {

    queue<string> queue; // Очередь для передачи данных
    mutex mtx; // Мьютекс для синхронизации
    condition_variable cv; // Условная переменная для уведомлений
    atomic<bool> done(false); // Флаг завершения

    init_tread(fileName);

    thread input(inputThread, ref(queue), ref(mtx), ref(cv), ref(done));
    thread output(writeThread, ref(queue), ref(mtx), ref(cv), ref(done), ref(fileName));

    // Ждём завершения потоков
    input.join();
    output.join();

    cout << "Finish programm! " << endl;

    return 0;
}
