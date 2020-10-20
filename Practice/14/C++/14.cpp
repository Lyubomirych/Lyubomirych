// 14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
    setlocale(0, "");
    double n, x;
    cout << "Введите число:\n";
    cin >> n;
    x = 0;
    if ((n >= 0) && (n <= pow(10,15)))
    {
        
        for (int i = 0; pow(2, i) <= n; i++)
            x++;
        cout << "степеней двойки начиная с нулевой:" << x;
    }
    else 
    { 
        cout << "не удовлетворяет условие"; 
    }
   return 0;
}

