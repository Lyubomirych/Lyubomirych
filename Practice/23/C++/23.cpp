// 23.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip> 
#include "Header1.h"
#include "Header2.h"
#include "Header3.h"

using namespace std;
int main()
{
    setlocale(0, "");
    const double pi = 3.141592653589783;
    //Факториал
    int n = 10;
    //cout << "Введите число для факториала: ";          //<-----------Для ручного ввода раскоментировать-
    //cin >> n;
    cout << "n!\n"; 
    for (int i = 1; i < n + 1; i++) 
    { 
        cout << i << " " << fact(i) << "\n"; 
    }
    //Второе условие
    int k = 5;
    //cout<<"Введите количество членов разложения: ";          //<-----------Для ручного ввода раскоментировать-
    //cin >> k;
    cout << "\nx" << "\t" << "sinx" << endl;
    for (float i = 0; i < 0.7854; i += pi / 180)
    {
        cout << setprecision(4) << i << "\t" << sinx(i, k) << endl;
    }
    //Третье условие
    int m = 10;
    //cout<<"последнее число диапазона: ";          //<-----------Для ручного ввода раскоментировать-
    //cin >> m;
    cout << "\nk" << "\t" << "C(k,10)" << endl;
    for (int i = 1; i < 11; i++)
    {
        cout << i << "\t" << soch(i, m) << endl;
    }
    
}

