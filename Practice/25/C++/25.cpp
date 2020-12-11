// 25.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace  std;
typedef vector<int> new_vector;
typedef vector<vector<int>> new_matrix;

bool sort(new_vector v, bool direction = true)//--------------------------------------------------------------------------------по умолчанию
{
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

new_vector BozoSort(new_matrix v_dvumer, bool direction = true) { //----------------------------------------------------------------------Матрица
	new_vector v_dvumer2;
	for (new_vector i : v_dvumer) {
		for (int j : i) {
			v_dvumer2.push_back(j);
		}
	}
	int vect_len = v_dvumer2.size();
	while (!sort(v_dvumer2, direction))
	{
		int index1 = rand() % vect_len;
		int index2 = rand() % vect_len;
		int temp = v_dvumer2[index2];
		v_dvumer2[index2] = v_dvumer2[index1];
		v_dvumer2[index1] = temp;

	}
	return v_dvumer2;
}

new_vector BozoSort(vector <int> v, bool direction = true) //-------------------------------------------------------------------------------------------------------------вектор
{
	int vect_len = v.size();
	while (!sort(v, direction))
	{
		int index1 = rand() % vect_len;
		int index2 = rand() % vect_len;
		int temp = v[index2];
		v[index2] = v[index1];
		v[index1] = temp;

	}
	return v;
}
	

new_vector BozoSort(int x, int y, int z, bool direction = true) //-------------------------------------------------------------------------------------------------------------3 числа
{
	new_vector v3;
	v3 = { x, y, z };
	int vect_len = v3.size();
	    while (!sort(v3, direction)) {
		    int index1 = rand() % vect_len;
		    int index2 = rand() % vect_len;
		    int temp = v3[index2];
		    v3[index2] = v3[index1];
		    v3[index1] = temp;
	    }

    return v3;
}
int main()
{
    setlocale(0, "");
    int a, element;
	new_vector v;				//вектор
	new_matrix vector_matrix;	//двумерный массив
	new_vector formatrix;		//для внесения элементов в двумерный
    cout << "Введите количество элементов от 4 до 100, из которых можно извлечь целый квадратный корень:\n";
    cin >> a; 
    cout << "введите элементы через пробел: ";
	for (int i = 1; i <= a; i++)
    {
		int element;
		cin >> element;
		v.push_back(element);
		formatrix.push_back(element);
		if (i % int(std::sqrt(a)) == 0)
		{
			vector_matrix.push_back(formatrix);
			formatrix.clear();
		}
    }

	for (int i : BozoSort(v, true)) {                                  //вызовы функций с различными аргументами
		cout << i << " ";
	}
	cout << endl;
	for (int i : BozoSort(v, false)) {
		cout << i << " ";
	}
	cout << endl;
	for (int i : BozoSort(vector_matrix, true)) {
		cout << i << " ";
	}
	cout << endl;
	for (int i : BozoSort(vector_matrix, false)) {
		cout << i << " ";
	}
	cout << endl;
	for (int i : BozoSort(v[0], v[1], v[2], true)) {
		cout << i << " ";
	}
	cout << endl;
	for (int i : BozoSort(v[0], v[1], v[2], false)) {
		cout << i << " ";
	}
	cout << endl;
}

