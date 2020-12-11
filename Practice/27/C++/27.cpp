#include <iostream>
#include <iterator>
#include <set> //подключаю библиотеку множества

using namespace std;

int main() {
    setlocale(0, "");
    int n;
    cout << "Введите количество сигалов n, 1<=n<=100000: ";
    cin >> n;
    if (1 > n || n > 100000) { cout << "Данные введены неверно!"; }
    else {
        set<int> a;
        cout << "Введите целые числа a, -1000000<=a<=1000000: ";
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            if (-1000000 > t || t > 1000000) { cout << "Данные не соответствуют условию!"; break; }
            a.insert(t);
            int j = 0;
            set<int> b;
            for (auto it = a.cbegin(); it != a.cend() && j < 5; ++it, ++j)
                b.insert(*it);
            copy(b.crbegin(), b.crend(), ostream_iterator<int>(cout, " "));
            cout << '\n';
        }
    }
}