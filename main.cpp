#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "libs/json.hpp"
#include <pwd.h>
#include <unistd.h>
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
        cout << key << "| " << "задача:  " << value["text"] << "  " << "начинается: " << value["startTime"] << "  " << "заканчивается:  " << value["endTime"] << endl;
    }

    send_tasks(tasks);
}

void update(json& tasks, vector<vector<string>>& tasks_list){
    string user_task;
    string user_startTime;
    string user_endTime;

    cout << "Введите номер задачи: ";
    cin >> user_task;

    int user_task_num = stoi(user_task);

    cout << "началась: ";
    cin >> user_startTime;
    tasks_list[user_task_num][1] = user_startTime;

    cout << "закончилась: ";
    cin >> user_endTime;
    tasks_list[user_task_num][2] = user_endTime;

    

    for (auto& [key, value] : tasks.items()){
        if (key == user_task){
            value["startTime"] = user_startTime;
            value["endTime"] = user_endTime;
        }
    }

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