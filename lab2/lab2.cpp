#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <ctime>
#define PRIME_SIZE 50

using namespace std;


class Person
{
public:
	string name;
	string surname;
	int age;

	Person(string name, string surname, int age = 0)
	{
		this->name = name;
		this->surname = surname;
		this->age = age;
	}
};

class HashTable
{
	Person *table[PRIME_SIZE];

	static int hash(string str)
	{
		int asciisum = 0;
		for (int i = 0; i < str.length(); i++)
		{
			asciisum += str[i];
		}
		return asciisum % PRIME_SIZE;
	}

public:

	HashTable()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			table[i] = NULL;
		}
	}

	~HashTable()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			delete table[i];
		}
	}


	void push(string name, string surname, int age)
	{
		int hashNumber = hash(name);
		Person *pers = new Person(name, surname, age);
		Person *place = table[hashNumber];
		if (place == NULL)
		{
			table[hashNumber] = pers;
			return;
		}

		for (int i = 0; i < PRIME_SIZE; i++)  if (table[i] == NULL) { table[i] = pers; return; }

	}

	Person* find(string name)
	{
		int hashNumber = hash(name);
		Person *result = table[hashNumber];
		if (!result)
		{
			cout << "Element not found" << endl;
			return NULL;
		}
		bool is_find = false;
		if (result->name != name)
		{
			for (int i = 0; i < PRIME_SIZE; i++)
			{
				if (table[i] && table[i]->name == name)
				{
					result = table[i];
					is_find = true;
					break;
				}
			}
		}
		else
		{
			return result;
		}
		if (is_find) return result;
		else
		{
			cout << "Element not found" << endl;
			return NULL;
		}
	}
};

class PersonOpen
{
public:
	PersonOpen *next; 
	string name;
	string surname;
	int age;

	PersonOpen()
	{
		this->next = NULL;
	}

	PersonOpen(string name, string surname, int age = 0)
	{
		this->name = name;
		this->surname = surname;
		this->age = age;
		this->next = NULL;
	}

	~PersonOpen()
	{

		if (this->next != NULL)
		{
			delete this->next;
		}
	}
};

class HashTableOpen
{
	PersonOpen *table[PRIME_SIZE];

	static int hash(string str)
	{
		int asciisum = 0;
		for (int i = 0; i < str.length(); i++)
		{
			asciisum += str[i];
		}
		return asciisum % PRIME_SIZE;
	}

public:

	HashTableOpen()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			table[i] = NULL;
		}
	}

	~HashTableOpen()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			delete table[i];
		}
	}

	void push(string name, string surname, int age)
	{
		int hashNumber = hash(name);
		PersonOpen *pers = new PersonOpen(name, surname, age);
		PersonOpen *place = table[hashNumber];
		if (place == NULL)
		{
			table[hashNumber] = pers;
			return;
		}

		while (place->next != NULL)
		{
			place = place->next;
		}
		place->next = pers;
	}

	PersonOpen* find(string name)
	{
		int hashNumber = hash(name);
		PersonOpen *result = table[hashNumber];
		if (!result)
		{
			cout << "Element not found" << endl;
			return NULL;
		}

		while (result->name != name)
		{
			if (!result->next)
			{
				cout << "Element not found" << endl;
				break;
			}
			result = result->next;
		}
		return result;
	}
};


int main()
{
	cout << "-----------------Add names to hashtable----------------\n";
	HashTable newTable;
	double  finish_time;
	finish_time = 0;
	newTable.push("abc", "Alexey", 18);
	newTable.push("bca", "Diana", 19); 
	newTable.push("bac", "Alexey", 17);//Collision
	newTable.push("qwe", "Fedor", 21);
	newTable.push("eqw", "Adrey", 44);//Collision
	finish_time = (double)clock();
	cout << "Add elements with collision: " << (finish_time )<< "mcs\n";
	finish_time = 0;
	newTable.push("rty", "Danyl", 32);
	newTable.push("hgf", "Maria", 24);
	newTable.push("nbn", "Dmitry", 54);
	newTable.push("iuy", "Anton", 21);
	newTable.push("kjh", "Adrey", 44);
	finish_time = (double)clock();

	cout << "Add elements without collision: " << (finish_time)<< "mcs\n";

	finish_time = 0;
	cout << "-----------------------Find element----------------------\n";
	Person * search = newTable.find("iuy");
	if (search)
	{
		cout << search->surname << endl;
	}
	finish_time = (double)clock();
	cout << "Search elements: " << finish_time << "mcs\n";

	cout << "-----------------Add names to open hashtable----------------\n";
	HashTableOpen newTableOpen;
	finish_time = 0;
	newTableOpen.push("abc", "Alexey", 18);
	newTableOpen.push("bca", "Diana", 19);
	newTableOpen.push("bac", "Alexey", 17);//Collision
	newTableOpen.push("qwe", "Fedor", 21);
	newTableOpen.push("eqw", "Adrey", 44);//Collision
	finish_time = (double)clock();
	cout << "Add elements with collision: " << (finish_time) << "mcs\n";
	finish_time = 0;
	newTableOpen.push("rty", "Danyl", 32);
	newTableOpen.push("hgf", "Maria", 24);
	newTableOpen.push("nbn", "Dmitry", 54);
	newTableOpen.push("iuy", "Anton", 21);
	newTableOpen.push("kjh", "Adrey", 44);
	finish_time = (double)clock();

	cout << "Add elements without collision: " << (finish_time) << "mcs\n";

	finish_time = 0;
	cout << "-----------------------Find element----------------------\n";
	PersonOpen * searchOpen = newTableOpen.find("abc");
	if (search)
	{
		cout << searchOpen->surname << endl;
	}
	finish_time = (double)clock();
	cout << "Search elements: " << finish_time << "mcs\n";

	return 0;
}

