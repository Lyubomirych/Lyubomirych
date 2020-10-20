// 03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
        cout << "Введите значения переменных типа int \n";
            int xi, yi;
            cin >> xi >> yi;
        cout << "Введите значения переменных типа double \n";
            double xd, yd;
            cin >> xd >> yd;

    cout << "first int +, -, *, / second int \n" << xi + yi << "\n"<< xi - yi << "\n"<< xi * yi << "\n" << xi / yi << "\n"; //математические действия с значениями переменных int, int
    cout << "first double +, -, *, / second double \n" << xd + yd << "\n"<< xd - yd << "\n"<< xd * yd << "\n" << xd / yd << "\n"; //математические действия с значениями переменных double, double
    cout << "first int +, -, *, / second double \n" << xi + yd << "\n"<< xi - yd << "\n"<< xi * yd << "\n" << xi / yd << "\n"; //математические действия с значениями переменных int, double
    cout << "first double +, -, *, / second int \n" << xd + yi << "\n"<< xd - yi << "\n"<< xd * yi << "\n" << xd / yi << "\n"; //математические действия с значениями переменных double, int
}

