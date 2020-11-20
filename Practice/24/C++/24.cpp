// 24.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include "nlohmann/json.hpp"
using json = nlohmann::json; //подключаем используемую библиотеку, предворительно поместив ее в папку с проектом
using namespace std;

int main() 
{
    ifstream input("in.json");
    json jinput; //создаем далее выводимый объект, потом получаем id и статус для каждого задания
    input >> jinput;
    input.close();
    map < int, int > users;
    for (auto& task : jinput) 
    {
        int userId = task["userId"];
        bool completed = task["completed"]; //ищем пользователя с id
        users.try_emplace(userId, 0);
        if (completed) 
        {
            ++users[userId];
        }
    }
    json joutput;
    for (auto& pair : users) {//если пользователя нет, добавляем новый объект в joutput
        joutput.push_back
        ({
            {
            "userId", pair.first
            },
            {
            "task_completed", pair.second
            }
        });
    }
    ofstream output("out.json"); // выводим результат в файл
    output << setw(2) << joutput << endl;
    output.close();
}