// 23.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Header1.h"
#include "Header2.h"

using namespace std;
int main()
{
    setlocale(0, "");
    int n; 
    cout << "Введите число для факториала: ";
    cin >> n;
    cout << "n!\n"; fact(n); cout << "\n";
    int x, k;
    cout << "Введите число и кол-во разложений для вычисления ряда тейлора: ";
    cin >> x >> k;
    cout << "x   |   sinx\n"; sinx(x, k);
}

