#include <iostream>
#include <string>

using namespace std;

int main()
{
    setlocale(0, "");
    int kolvo, vibor;  string res, prob; char n1, n4, n5, n6, n7, n8;
    res = ""; prob = " ";
    cout << "Установить параметры для проверки по умолчанию (a***55661) - 1, \nустановить свои собственные значения(?***?????) - 2\n"; 
    cin >> vibor;                               //Выбор значений, по умолчанию значения из условия, или новые значения
    if (vibor == 1)
    {
        n1 = 'a'; n4 = '5'; n5 = '5'; n6 = '6'; n7 = '6'; n8 = '1';
    }
    else
    {
        cout << "Введите символьное значение 1 элемента, и численные значения 4, 5, 6, 7, 8 элементов\n";
        cin >> n1 >> n4 >> n5 >> n6 >> n7 >> n8;
        cout << "Вы ввели ключ: \n" << n1 << "***" << n4 << n5 << n6 << n7 << n8 <<"\n";
    }
    cout << "Введите количество билетов: ";
    cin >> kolvo;
    cout << "Введите номера билетов: ";
    for (int i = 0; i < kolvo; i++)
    {
       string bilet;
       cin >> bilet;
       if (bilet[0]==n1 && bilet[4] == n4 && bilet[5] == n5 && bilet[6] == n6 && bilet[7] == n7 && bilet[8] == n8) //сравнение символа с заданными для проверки
       { 
           res = res + bilet + prob;
       }
    }
    if (res == "")
    {
        cout << -1;
    }
    else 
    { 
        cout << res; 
    }
    return 0;
}