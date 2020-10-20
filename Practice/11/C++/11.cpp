// 11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int main()
{
   setlocale(0, "");
   double x, y, s;
   int i;
   i = 0;
   s = 1;
   cout << "введите число и степень\n";
   cin >> x >> y;
   while (i<y)
   { 
       s = s * x;
       i++;
   }
   cout << x << " в степени "<< y <<" равно : " << s;
}

