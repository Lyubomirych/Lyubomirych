#include <iostream>

struct IntArray {
	int* data;
	int size;
};
/** Создаёт динамический массив размера size и сохраняет его в поле data переменной arr. Поле size структуры arr становится равным параметру size */
void create(IntArray* arr, int size) {
	arr->data = new int[size];
	arr->size = size;
}
void create(IntArray& arr, int size) {
	arr.data = new int[size];
	arr.size = size;
}
/** Возвращает элемент массива с индексом index, при этом проверяет выход за границы массива. Если index лежит за пределами массива, вывести сообщение об ошибке и прервать работу программы */
int get(IntArray* arr, int index) {
	return arr->data[index];
}
int get(IntArray& arr, int index) {
	return arr.data[index];
}
/** Изменяет значение элемента массива с индексом index на значение параметра value, при этом проверяет выход за границы массива. Если index лежит за пределами массива, вывести сообщение об ошибке и прервать работу программы */
void set(IntArray* arr, int index, int value) {
	arr->data[index] = value;
}
void set(IntArray& arr, int index, int value) {
	arr.data[index] = value;
}
/** Выводит на экран содержимое массива в формате: [1, 2, 3] */
void print(IntArray* arr) {
	std::cout << "[";
	for (int i = 0; i < arr->size - 1; i++)
		std::cout << arr->data[i] << ", ";
	std::cout << arr->data[arr->size - 1] << "]" << std::endl;
}
void print(IntArray& arr) {
	std::cout << "[";
	for (int i = 0; i < arr.size - 1; i++)
		std::cout << arr.data[i] << ", ";
	std::cout << arr.data[arr.size - 1] << "]" << std::endl;
}
/** Изменяет размер массива с сохранением элементов. Если новый размер меньше, хвостовые элементы обрезаются, если больше, то дополнительные элементы инициализируются нулём */
void resize(IntArray* arr, int newSize) {
	int* newArr = new int[newSize];

	if (newSize < arr->size) {
		for (int i = 0; i < newSize; i++)
			newArr[i] = arr->data[i];
	}
	else { // newSize >= arr->size
		for (int i = 0; i < arr->size; i++)
			newArr[i] = arr->data[i];
		for (int i = arr->size; i < newSize; i++)
			newArr[i] = 0;
	}

	delete arr->data;
	arr->data = newArr;
	arr->size = newSize;
}
void resize(IntArray& arr, int newSize) {
	int* newArr = new int[newSize];

	if (newSize < arr.size) {
		for (int i = 0; i < newSize; i++)
			newArr[i] = arr.data[i];
	}
	else { // newSize >= arr.size
		for (int i = 0; i < arr.size; i++)
			newArr[i] = arr.data[i];
		for (int i = arr.size; i < newSize; i++)
			newArr[i] = 0;
	}

	delete arr.data;
	arr.data = newArr;
	arr.size = newSize;
}
/** Освобождает память занятую массивом. Поле data становится равным nullptr, поле size становится равным нулю. Предусмотреть случай попытки удаления уже удалённого массива */
void destroy(IntArray* arr) {
	if (!arr->size) return;
	delete arr->data;
	arr->data = nullptr;
	arr->size = 0;
}
void destroy(IntArray& arr) {
	if (!arr.size) return;
	delete arr.data;
	arr.data = nullptr;
	arr.size = 0;
}
/**Вызывает функции*/
int main() {

	IntArray arr;
	create(arr, 30);

	for (int i = 0; i < arr.size; i++)
		set(arr, i, i + 1);

	print(arr);

	resize(arr, 50);
	print(arr);

	resize(arr, 10);
	print(arr);

	destroy(arr);

	return 0;
}