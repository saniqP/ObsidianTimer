#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include "libs/json.hpp"
#include <pwd.h>
#include <unistd.h>
#include <regex>

using namespace std;
using json = nlohmann::json;



std::string get_home_dir() {
    struct passwd *pw = getpwuid(getuid());
    if (pw != nullptr) {
        return std::string(pw->pw_dir);
    }
    return ""; 
}

json parse_json(string jsonname){
    ifstream file(jsonname);

    json datas = json::parse(file);

    file.close();

    return datas;
}

void save_json(const json& data, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << data.dump(4); 
        file.close();
        cout << "Данные сохранены в " << filename << endl;
    } else {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << endl;
    }
}


bool is_valid_time(const std::string& time_str) {
    std::regex time_pattern(R"(^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$)");
    return std::regex_match(time_str, time_pattern);
}


vector<vector<string>> send_tasks(json& tasks){
    vector<vector<string>> asksList;

    for (auto& [key, value] : tasks.items()) {
        asksList.push_back(vector<string>{value["text"], value["startTime"], value["endTime"]});
    }

    return asksList;
}





void draw(json& tasks){
    string welcome_strings[3] = {"\033[34m===============================\033[0m", "\033[35m=  O B S I D I A N  T I M E   =\033[0m", "\033[34m===============================\033[0m"};

    for (string x : welcome_strings){
        cout << x << endl;
    }

     for (auto& [key, value] : tasks.items()) {
        cout << "\033[35m" << key << "| " << "\033[37m" << "задача:  " << "\033[35m" << value["text"] << "\033[37m" << "  " << "начинается: " << "\033[31m" << value["startTime"] << "\033[37m" << "  " << "заканчивается:  " << "\033[33m" << value["endTime"] << "\033[0m" << endl;
    }

    send_tasks(tasks);
}

void update(json& tasks, vector<vector<string>>& tasks_list){
    string user_task;
    string user_startTime;
    string user_endTime;

    while (true){
        cout << "Введите номер задачи: ";
        cin >> user_task;
        if (stoi(user_task) >= tasks_list.size()){
            continue;
        }
        else{
            break;
        }
    }

    int user_task_num = stoi(user_task);

    while (true){
        cout << "началась: ";
        cin >> user_startTime;
        if (!is_valid_time(user_startTime)){
            continue;
        }
        else {
            tasks_list[user_task_num][1] = user_startTime;
            break;
        }
        
    }

    while (true){
        cout << "закончилась: ";
        cin >> user_endTime;

        if (!is_valid_time(user_endTime)){
            continue;
        }

        else {
            tasks_list[user_task_num][2] = user_endTime;
            break;
        }
    }

    

    for (auto& [key, value] : tasks.items()){
        if (key == user_task){
            value["startTime"] = user_startTime;
            value["endTime"] = user_endTime;
        }
    }
    save_json(tasks, get_home_dir() + "/.taskrc.jsonc");

}




int main(){

    json tasks = parse_json(get_home_dir() + "/.taskrc.jsonc");
    vector<vector<string>> tasks_list = send_tasks(tasks);

    while (true) {
        draw(tasks);
        update(tasks, tasks_list);
        system("clear");
    }
}