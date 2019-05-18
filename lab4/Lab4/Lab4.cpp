#include "pch.h"
#include <iostream>
#include <iostream>;
#include <fstream>;
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;
struct node {
	int key;
	int height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

struct avl_tree
{
	node *top;
	avl_tree(void) : top(NULL) {}
};

int height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p)
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q)
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* insert(node* p, int k)
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else if (k > p->key)
		p->right = insert(p->right, k);
	return balance(p);
}

void add(avl_tree &avl_tr, int k)
{

	avl_tr.top = insert(avl_tr.top, k);
}

node* findmin(node* p)
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k)
{
	if (!p)
	{
		cout << "Not found" << endl;
		return 0;
	}
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else {
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r)
		{
			cout << "Deleted" << endl;
			return q;

		}

		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		cout << "Deleted" << endl;
		return balance(min);

	}
	return balance(p);
}

void del(avl_tree &avl_tr, int r)
{
	avl_tr.top = remove(avl_tr.top, r);
}



int main() {
	ifstream fin;
	fin.open("F:\\TREE.txt");

	avl_tree Tree;

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
	return 0;
}