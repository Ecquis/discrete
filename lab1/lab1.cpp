#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Stack
{
	int element;
	Stack *next, *start;
};
void Add(int x, Stack *&Stack_link)
{
	Stack *temp = new Stack;
	temp->element = x;
	temp->next = Stack_link->start;
	Stack_link->start = temp;
}
// used for debug
/*void Show(Stack *Stack_link)
{
	Stack *temp = Stack_link->start;
	
	while (temp != NULL)
	{
		cout << temp->element << " ";
		temp = temp->next;
	}
}*/

struct element
{
	int x;
	element *Next;
};
class List
{
	element *Head;
public:
	List() { Head = NULL; }
	void Add(int x);
	void Show();
};
void List::Add(int x)
{
	element *temp = new element;
	temp->x = x;
	temp->Next = Head;
	Head = temp;
}
// used for debug
/*void List::Show()
{
	element *temp = Head;


	while (temp != NULL)
	{
		cout << temp->x << " ";
		temp = temp->Next;
	}
}*/

int main()
{
	cout << "------Stack algorithms time measurement------\n";
	cout << "Adding elements to stack time:\n";

	Stack *Stack_link = new Stack; 
	Stack_link->start = NULL;	
	
	ifstream fin;
	int n = 10;
	unsigned int scores[10];
	unsigned int sum = 0;
	int x;
	unsigned int start_time, finish_time;
	for (int i = 0; i < n; i++) {
		fin.open("input.txt");
		start_time = clock();
		while (!fin.eof()) {
			fin >> x;
			Add(x, Stack_link);
		}
		finish_time = clock();
		fin.close();
		scores[i] = finish_time - start_time;
		sum += scores[i];
		cout << "loop " << i << ": " << scores[i] << " ms\n";
	}
	cout << "Average time: " << sum / n << " ms\n";
	cout << "---------------------------------------------\n";

	cout << "-----Single linked list time measurement-----\n";
	List list;
	sum = 0;
	for (int i = 0; i < n; i++) {
		fin.open("input.txt");
		start_time = clock();
		while (!fin.eof()) {
			fin >> x;
			Add(x, Stack_link);
		}
		finish_time = clock();
		fin.close();
		scores[i] = finish_time - start_time;
		sum += scores[i];
		cout << "loop " << i << ": " << scores[i] << " ms\n";
	}
	cout << "Average time: " << sum / n << " ms\n";
	cout << "---------------------------------------------";

}