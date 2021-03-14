
#include <iostream>

using namespace std;

void create(int*& arr, int dlina, int first_element = 0, int shag = 0) {
    arr = new int[dlina];

    for (int i = 0, current = first_element; i < dlina; i++, current += shag) {
        arr[i] = current;
    }
}

int* sort(int* arr, int dlina)
{
    int value, j;
    for (int i = 1; i < dlina; ++i)
    {
        value = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > value)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = value;
    }
    return arr;
}

int* print(int* arr, int dlina)
{
    printf("[%d", *arr);
    for (int i = 1; i < dlina; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
    return arr;
}

void destroy(int** arr)
{
    if (!*arr)
    {
        delete[] * arr;
        *arr = nullptr;
    }
}

void destroy(int*& arr) {
    if (arr != nullptr) {
        delete[] arr;
    }
}

int main(int argc, char* argv[])
{
    setlocale(0, "");
    int dlina, first_element, shag;
    cout << ("Введите длинну массива, первый элемент и шаг: ");
    cin >> dlina >> first_element >> shag;
    int* arr;
    create(arr, dlina, first_element, shag);
    sort(arr, dlina);
    print(arr, dlina);
    destroy(&arr);
    return 0;
}