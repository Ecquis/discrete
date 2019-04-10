#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;


bool puzirik() {
	int start = clock();
	
	int *arr; // указатель для выделения памяти под массив
	int size = 10000; // размер массива

	arr = new int[size]; // выделение памяти под массив

	for (int i = 0; i < size; i++) {
		arr[i] = rand();
	}

	int temp; // временная переменная для обмена элементов местами

	// Сортировка массива пузырьком
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// меняем элементы местами
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// Вывод отсортированного массива на экран
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	delete[] arr; // освобождение памяти;

	int finish = clock();
	int time = finish - start;
	cout << time;
	cout << endl;
	return true;
}

void quickSort(int arr[], int left, int right) {

	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);


}

bool quick() {
	int start = clock();
	int size = 10000;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand();
	}
	quickSort(arr, 0, size - 1);
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	int finish = clock();
	int time = finish - start;
	cout << time;
	return true;
}

int main()
{
	puzirik();
	quick();
	return 0;
}
