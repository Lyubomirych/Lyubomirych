// 09.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
   setlocale(LC_ALL, "Russian");
   int h1, h2, m1, m2, vrem;
   char ch;
   cout << "время прихода первого: \n";
   cin >> h1 >> ch >> m1;
   cout << "время прихода второго: \n";
   cin >> h2 >> ch >> m2;
   if (0 > h1 || h1 > 23 || 0 > h2 || h2 > 23 || 0 > m1 || m1 > 59 || 0 > m2 || m2 > 59) { cout << "неккоретно введены данные"; }
   else
   {
       vrem = (h1 * 60 + m1) - (h2 * 60 + m2);
       if (-15 <= vrem && vrem <= 15)
       {
           cout << "Встреча состоится";
       }
       else { cout << "Встреча не состоится"; }
   }
}

