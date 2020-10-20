// 05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{

    setlocale(LC_ALL, "Russian");
        cout << "Введите значения Xo, Vo, t\n";
        double xo, vo, t;  int a;
        cin >> xo >> vo >> t;
        cout << "Расстояние равно:\n" << xo+vo*t-(9.8*t*t/2);
}

