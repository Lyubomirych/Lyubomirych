// 21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

double BMI(double weight, double height)    //функция подсчета BIM
{
    return ((weight / (pow(height, 2))) * pow(10, 4));
}
void printBMI(double BMI) //Функция выбора категории
{
    if (BMI < 18.5)
    {
        cout << "Underweight\n";
    }
    else if (18.5 <= BMI && BMI < 25)
    {
        cout << "Normal\n";
    }
    else if (25 <= BMI && BMI < 30)
    {
        cout << "Overweight\n";
    }
    else
    {
        cout << "Obesity\n";
    }
}
int main()
{ 
    setlocale(0, "");
    double ves, rost, n;
    int v = 0;
    do {
            cout << "Введите вес и рост:\n";
            cin >> ves >> rost;
            if (ves != 0 && rost != 0)  //проверка на положительность чисел
            {
                n = BMI(ves, rost); //вызов функций
                printBMI(n);
                cout << "закрыть программу? 1-да ";
                cin >> v;
            }
            else
            {
                cout<<"Введите положительные значения: \n";
            }
    } while (v != 1);
}



       
