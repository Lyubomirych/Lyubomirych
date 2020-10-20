// 12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;
int main(int argc, char* argv[])
{
    setlocale(0, "");
    double i, x, fact;
    cout << "введите положительное число\n";
    cin >> x;
    if (x < 1) 
    { 
        cout << "ошибка, число меньше 1 \n"; 
        system(argv[0]); //при неправильном вводе начинаем сначала
    }
    else
    {   
        fact = 1;
        for (i = 1; i <= x; i++)
        {
            fact = fact * i;
        }
        if (fact > pow(10, 9)) { cout << "значение слишком велико, оно больше 1 миллиарда"; }
        else cout << "факториал " << x << " равен: " << fact;
    }

    return 0;
}

