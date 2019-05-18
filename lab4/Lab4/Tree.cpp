#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

struct elem
{
	int data;
	elem *par;
	elem *left, *right;
	elem(int value = 0) : par(NULL), left(NULL),
		right(NULL), data(value) {}
};

struct binary_tree
{
	elem *top;
	binary_tree(void) : top(NULL) {}
};

void add(binary_tree &bin_tr, int x)
{
	if (!bin_tr.top)
	{
		bin_tr.top = new elem(x);
		return;
	}

	elem *p = bin_tr.top;
	while (p)
		if (x < p->data)
			if (!(p->left)) {
				p->left = new elem(x);
				p->left->par = p;
				return;
			}
			else p = p->left;
		else if (x > p->data)
			if (!(p->right)) {
				p->right = new elem(x);
				p->right->par = p;
				return;
			}
			else p = p->right;
		else if (p->data == x)
			return;
}

void del(binary_tree &bin_tr, int x)
{
	elem *p = bin_tr.top,
		*prev = NULL;
	char h;
	while (p && p->data != x) {
		prev = p;
		if (p->data > x) {
			p = p->left;
			h = 'l';
		}
		else if (p->data < x) {
			p = p->right;
			h = 'r';
		}
	}
	if (!p) {
		cout << "Not found" << endl;
		return;
	}

	if (!p->left && !p->right) {

		delete p;
		if (h == 'l') prev->left = NULL;
		else prev->right = NULL;
		cout << "Deleted" << endl;
		return;
	}
	if (p->left && p->right) {
		elem *el = p->right;
		while (el->left)
			el = el->left;
		p->data = el->data;
		if (el == p->right) el->par->right = el->right;
		else el->par->left = el->right;
		delete el;
		cout << "Deleted" << endl;
		return;
	}

	if (p->left)
	{
		if (h == 'l') prev->left = p->left;
		else  prev->right = p->left;
		delete p;
		cout << "Deleted" << endl;
		return;
	}
	if (p->right)
	{
		if (h == 'l') prev->left = p->right;
		else prev->right = p->right;
		cout << "Deleted" << endl;
		delete p;
	}
}

void infix(elem *top)
{
	if (!top) return;
	infix(top->left);
	cout << top->data << " ";
	infix(top->right);
}

void main() {
	ifstream fin;
	fin.open("F:\\TREE.txt");

	binary_tree Tree;

	string str;
	str = "";
	clock_t start = clock();
	for (int i = 0; i < 1000000; i++) {
		getline(fin, str);
		int num = stoi(str);
		add(Tree, num);
	}
	clock_t end = clock();
	fin.close();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Runtime Add: " << seconds << endl;

	int elem;
	double seconds1 = 0;
	for (int i = 0; i < 100; i++)
	{
		elem = rand() % 1001;
		cout << "Enter -  " << elem << endl;
		clock_t start1 = clock();
		del(Tree, elem);
		clock_t end1 = clock();
		seconds1 += (double)(end1 - start1) / CLOCKS_PER_SEC;

	}
	cout << "Runtime Delete: " << seconds1 << endl;

	system("pause");

}
