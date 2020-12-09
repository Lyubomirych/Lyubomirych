// 25.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace  std;

int BozoSort(vector <int> v, int a )
{
	bool sorted = false; 
	while (!sorted) {
		int index1 = rand() % a;
		int index2 = rand() % a;
		int temp = v[index2];
		v[index2] = v[index1];
		v[index1] = temp;
		sorted = true;
		for (int i = 1; i < a; i++) {
			if (v[i - 1] > v[i]) {
				sorted = false;
				break;
			}
		}
	}
	for (int i = 0; i < a; i++)
	{
		cout << v[i] << " ";
	}
	cout << "\n";
	sorted = false; 
	while (!sorted) {
		int index1 = rand() % a;
		int index2 = rand() % a;
		int temp = v[index2];
		v[index2] = v[index1];
		v[index1] = temp;
		sorted = true;
		for (int i = 1; i < a; i++) {
			if (v[i] > v[i-1]) {
				sorted = false;
				break;
			}
		}
	}
	for (int i = 0; i < a; i++)
	{
		cout << v[i] << " ";
	}
    return 0;
}

int BozoSort(int x, int y, int z)
{
    int arr[3] = { x, y, z };
	    bool sorted = false; 
	    while (!sorted) {
		    int index1 = rand()%3;
		    int index2 = rand()%3;
		    int temp = arr[index2];
		    arr[index2] = arr[index1];
		    arr[index1] = temp;
		    sorted = true;
		    for (int i = 1; i < 3; i++) {
			    if (arr[i - 1] > arr[i]) {
				    sorted = false;
				    break;
			    }
		    }
	    }
    for (int i = 0; i < 3; i++)
        {
            cout << arr[i] << " ";
        }
	cout << "\n";
	sorted = false;
	while (!sorted) {
		int index1 = rand() % 3;
		int index2 = rand() % 3;
		int temp = arr[index2];
		arr[index2] = arr[index1];
		arr[index1] = temp;
		sorted = true;
		for (int i = 1; i < 3; i++) {
			if (arr[i] > arr[i - 1]) {
				sorted = false;
				break;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		cout << arr[i] << " ";
	}
    return 0;
}
int main()
{
    setlocale(0, "");
    int a, k = 0, element;
    vector <int> v;
    vector<vector<int>>vec;
    cout << "Введите количество элементов от 4 до 100, из которых можно \n";
    cin >> a; 
    while (k != a) 
    {
        cout << "введите элемент: ";
        cin >> element;
        v.push_back(element); 
        k++;
    }
    BozoSort(v, a);
    cout << "\n";
    //BozoSort(vec, a);
    BozoSort(v[0], v[1], v[2]);
}

