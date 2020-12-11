#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
template<typename T>
using new_vector = vector<T>;
template<typename T>
using new_matrix = vector<vector<T>>;





template<typename T>
bool sort(new_vector<T> v, bool direction = true) {//Выражение в зависимости от значения умолчания

    int vect_len = v.size();
    if (direction) {
        for (int i = 1; i < vect_len; i++) {

            if (v[i - 1] > v[i]) {
                return false;
            }

        }
    }
    else {
        for (int i = 1; i < vect_len; i++) {

            if (v[i - 1] < v[i]) {
                return false;
            }

        }
    }
    return true;

}


template<typename T>
new_vector<T> BozoSort(new_vector<T> v, bool direction = true) { //Вектор
    int vect_len = v.size();
    while (!sort(v, direction))
    {
        int index1 = rand() % vect_len;
        int index2 = rand() % vect_len;
        swap(v[index1], v[index2]);

    }
    return v;
}


template<typename T>
new_vector<T> BozoSort(new_matrix<T> v_dvumer, bool direction = true) { //Двумерный массив
    new_vector<T> v_dvumer2;
    for (new_vector<T> i : v_dvumer) {
        for (T j : i) {
            v_dvumer2.push_back(j);
        }
    }
    int vect_len = v_dvumer2.size();
    while (!sort(v_dvumer2, direction))
    {
        int index1 = rand() % vect_len;
        int index2 = rand() % vect_len;
        swap(v_dvumer2[index1], v_dvumer2[index2]);

    }
    return v_dvumer2;
}


template<typename T>
new_vector<T> BozoSort(T x, T y, T z, bool direction = true) { // 3 элемента
    new_vector<T> v3;
    v3 = { x, y, z };
    int vect_len = v3.size();
    while (!sort(v3, direction)) {
        int index1 = rand() % vect_len;
        int index2 = rand() % vect_len;
        swap(v3[index1], v3[index2]);
    }

    return v3;
}


template<typename T>
pair<new_vector<T>, new_matrix<T>> get_user_info()
{
    int a; T element;
    cout << "Введите количество элементов от 4 до 100, из которых можно извлечь целый квадратный корень:\n";
    cin >> a;
    
    new_vector<T> v;            //вектор
    new_matrix<T> vector_matrix;//матрица
    new_vector<T> formatrix;    //вектор для заполнения двумерного вектора

    cout << "Введите элементы массива через пробел: ";
    for (int i = 1; i <= a; i++)
    {
        cin >> element;
        formatrix.push_back(element);
        v.push_back(element);
        if (i % int(sqrt(a)) == 0)
        {
            vector_matrix.push_back(formatrix);
            formatrix.clear();
        }
    }
    return { v, vector_matrix };
}

template<typename T>
void print_vector(new_vector<T> arr) { // Функция для вывода векторов
    for (T i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    setlocale(0, "");

    auto doubl = get_user_info<double>();
    auto str = get_user_info<string>();

    new_vector<double> vector_double = doubl.first;
    new_matrix<double> matrix_double = doubl.second;
    new_vector<string> vector_string = str.first;
    new_matrix<string> matrix_string = str.second;

    print_vector(BozoSort(vector_double, true));
    print_vector(BozoSort(vector_double, false));
    print_vector(BozoSort(matrix_double, true));
    print_vector(BozoSort(matrix_double, false));
    print_vector(BozoSort(vector_double[0], vector_double[1], vector_double[2], true));
    print_vector(BozoSort(vector_double[0], vector_double[1], vector_double[2], false));

    print_vector(BozoSort(vector_string, true));
    print_vector(BozoSort(vector_string, false));
    print_vector(BozoSort(matrix_string, true));
    print_vector(BozoSort(matrix_string, false));
    print_vector(BozoSort(vector_string[0], vector_string[1], vector_string[2], true));
    print_vector(BozoSort(vector_string[0], vector_string[1], vector_string[2], false));
}

