// 08.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double x, y; 
    char op;
    cout << "введите пример: \n";
    cin >> x >> op >> y;
    if (op == '*') 
    { 
        cout << x << op << y << "=" << x * y; 
    }
    else if (op == '/')
    {
        cout << x << op << y << "=" << x / y;
    }
    else if (op == '+')
    {
        cout << x << op << y << " = " << x + y;
    }
    else 
    {
        cout << x << op << y << "=" << x - y;
    }

    return 0;
}

