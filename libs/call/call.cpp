int welcome_message(json& tasks){

    vector<string> strings {"\033[34m===============================\033[0m", "\033[35m   O B S I D I A N  T I M E \033[0m", "\033[34m===============================\033[0m"};
    for (string x : strings){
        cout << x << endl;
    }

    for (auto& [key, value] : tasks.items()) {
        cout << key << "| " << "задача:  " << value["text"] << "  " << "начинается: " << value["startTime"] << "  " << "заканчивается:  " << value["endTime"] << endl;
    }

    return 1;
}