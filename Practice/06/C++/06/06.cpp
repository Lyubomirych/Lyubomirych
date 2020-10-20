// 06.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, c, D, x, x2;
    cout << "Введите значения a, b, c\n";
    cin >> a >> b >> c;
    D = sqrt(b * b - 4 * a * c);
    if (D > 0) 
         {
        x = (-1 * b + D) / (2 * a);
        x2 = (-1 * b - D) / (2 * a);
             cout << "Дискриминант равен : " << D << " \n Корень 1: " << x << "\n Корень 2: " << x2;
         }
    else if (D == 0) 
        {
            x = -b / (2 * a); 
            cout << "Дискриминант равен нулю, x = " << x << "\n";
        }   
    else 
        {
            cout << "Действительных корней нет, так как дискриминант меньше нуля\n";
        }
    return 0;
}

