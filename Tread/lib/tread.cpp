#include "tread.h"

msgPrioritet msgPriorDefault = msgPrioritet::MIDDLE;


static bool isOnlyDigit(string & str) {
    return regex_match(str, regex("[0-2]"));
}

static string GetNowTime() {
    string time_string;

    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    
    ostringstream oss;

    oss << put_time(localtime(&current_time), " %H:%M:%S");
    
    return time_string = oss.str();
}

void inputThread(queue<string>& queue, mutex& mtx, condition_variable& cv, atomic<bool>& done) {
    string input;
    string line;
    int prior;
    int user_msg_prior;
    smatch match;
    regex pattern(R"(.*Prior:([0-2])\s*$)");
    ostringstream stream_match_prior;
    
    cout << "To terminate the program, enter - \"exit\" " << endl;
    cout << "To change the default priority level, enter - \"prior\" " << endl;
    cout << "Input your data: " << endl;

    while (true) {
        getline(cin, input); // Считываем строку из терминала

        if (input == "exit") { // Проверяем условие завершения
            done = true; // Устанавливаем флаг завершения
            cv.notify_one(); // Уведомляем поток записи
            break;
        }

        if (input == "prior") {

            cout << endl;
            cout << "Select new priority level" << endl;

            while (1) {
                cout << "priority level:\n" << "HIGH - 2\n" << "MIDDLE - 1\n" << "LOW - 0\n" << endl;
                cout << "Input priority level: ";

                getline(cin, line);

                if (isOnlyDigit(line)) {
                    cout << "Only digit " << endl;
                    prior = stoi(line);
                    msgPriorDefault = static_cast<msgPrioritet>(prior);
                    continue;
        
                    //cout << msgPriorDefault << endl;
                }
                else {
                    cout << "Not only digit try again " << endl;
                }
            }
            
        }
        else {
            lock_guard<mutex> lock(mtx); // Блокируем очередь

            if (regex_search(input, match, pattern)) {
                cout << "correct" << endl;

                stream_match_prior << match[1];

                cout << "match prior = " << match[1] << endl;

                line = stream_match_prior.str();
                user_msg_prior = stoi(line);
                line.clear();

                cout << "user msg prior =  " << user_msg_prior << endl;
                cout << "msgPriorDefault = " << msgPriorDefault << endl;

                if (user_msg_prior < msgPriorDefault) {

                }
                else {
                    input += GetNowTime();
                    queue.push(input); // Добавляем строку в очередь
                }

                
            }
            else {
                cout << "Not have prior " << endl;

                input += " Prior:" + msgPriorDefault + GetNowTime();
                queue.push(input); // Добавляем строку в очередь
            }

            stream_match_prior.str(""); // Сбрасываем содержимое
            stream_match_prior.clear(); // Сбрасываем состояние (на случай ошибок)

            
        }

        cv.notify_one(); // Уведомляем поток записи о новых данных

        
    }
}



void writeThread(queue<string>& queue, mutex& mtx, condition_variable& cv, atomic<bool>& done, string& filename) {

    string filepath = "../" + filename + ".txt";

    ofstream file(filepath); // Открываем файл в режиме добавления
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    while (true) {
        unique_lock<mutex> lock(mtx); // Блокируем очередь
        cv.wait(lock, [&queue, &done] { return !queue.empty() || done; }); // Ждём данные или завершение

        // Если очередь пуста и установлен флаг завершения, выходим
        if (queue.empty() && done) {
            break;
        }

        // Обрабатываем все доступные строки в очереди
        while (!queue.empty()) {
            string line = queue.front() + "\n" ; // Берём строку из очереди
            queue.pop();
            lock.unlock(); // Разблокируем очередь перед записью в файл
            file << line; // Записываем строку в файл
            lock.lock(); // Блокируем очередь снова
        }
    }

    file.close(); // Закрываем файл
}

void init_tread(string &filename) {
    string line;
    int prior;

    cout << " Enter journal name: ";
    getline(cin, filename);

    cout << "Select a priority level.\n" << "Messages with a priority lower than the selected one will not be logged " << endl; 
    cout << endl;

    while (1) {
        cout << "priority level:\n" << "HIGH - 2\n" << "MIDDLE - 1\n" << "LOW - 0\n" << endl;
        cout << "Input priority level: ";
        getline(cin, line);

        if (isOnlyDigit(line)) {
         //   cout << "Only digit " << endl;
            prior = stoi(line);
            cout << endl;
            cout << "Enter def prior = " << prior << endl;
            msgPriorDefault = static_cast<msgPrioritet>(prior);
            cout << msgPriorDefault << endl;
            return;

            //cout << msgPriorDefault << endl;
        }
        else {
            cout << "Not only digit try again " << endl;
        }
    }

    
}