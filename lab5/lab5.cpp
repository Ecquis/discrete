#include "pch.h"
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <fstream>
#include <string>
#include <ctime>
#include "lab5.h"

using namespace std;

void countSort(vector <int> &arr)
{
	int max = *max_element(arr.begin(), arr.end());
	int min = *min_element(arr.begin(), arr.end());
	int range = max - min + 1;

	vector<int> count(range), output(arr.size());
	for (int i = 0; i < arr.size(); i++)
		count[arr[i] - min]++;

	for (int i = 1; i < count.size(); i++)
		count[i] += count[i - 1];

	for (int i = arr.size() - 1; i >= 0; i--)
	{
		output[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}

	for (int i = 0; i < arr.size(); i++)
		arr[i] = output[i];
}

int getMax(vector <int> &arr, int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort1(vector <int> &arr, int n, int exp)
{
	vector <int> output(n);
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

void radixsort(vector <int> &arr, int n)
{
	int m = getMax(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort1(arr, n, exp);
}

void printArray(vector <int> & arr)
{
	for (int i = 0; i < 6; i++) cout << arr[i] << "\n";
		cout << "...\n";
		cout << "...\n";
		cout << "...\n";
	for (int i = arr.size() - 6; i < arr.size(); i++)
		cout << arr[i] << "\n";
}

int main()
{

	cout << "-----------------Add to vector----------------\n";
	cout << "Adding elements to vector time:\n";
	vector<int> arr, arr1;
	ifstream fin;
	int x;
	unsigned int start_time, finish_time;
		fin.open("input.txt");
		start_time = clock();
		while (!fin.eof()) {
			fin >> x;
			arr.push_back(x);
		}
		finish_time = clock();
		fin.close();
	cout << "First Time: " << finish_time - start_time << "ms\n";
	fin.open("input.txt");
	start_time = clock();
	while (!fin.eof()) {
		fin >> x;
		arr1.push_back(x);
	}
	finish_time = clock();
	fin.close();
	cout << "Second Time: " << finish_time - start_time << "ms\n";
	cout << "---------------------------------------------\n";
	
	cout << "--------------Count Sort function------------\n";
		start_time = clock();
		countSort(arr);
		finish_time = clock();
	cout << "Time: " << finish_time - start_time << " ms\n";
	cout << "---------------------------------------------\n";
	cout << "------------------Print array----------------\n";
	
	printArray(arr);
	cout << "------------Radix Sort function-------------\n";
	int d = arr1.size();
	start_time = clock();
	radixsort(arr1, d);
	finish_time = clock();
	cout << "Time: " << finish_time - start_time << " ms\n";
	cout << "------------------Print array----------------\n";

	printArray(arr1);

	return 0;
}