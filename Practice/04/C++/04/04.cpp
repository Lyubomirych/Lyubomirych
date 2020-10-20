// 04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
    int a, b, x;
    setlocale(LC_ALL, "Russian");
    cout << "Введите значения переменных a, b \n";
    cin >> a >> b;
    x = a; a = b; b = x;
    cout << "a = " << a << "\n" << "b = " << b << "\n";
    a = a + b; b = a - b; a = a - b; //замена значений без дополнительной переменной, путем математических вычислений
    cout << "a = " << a << "\n" << "b = " << b << "\n";
}

