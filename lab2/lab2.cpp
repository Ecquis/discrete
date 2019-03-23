#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class Identifier
{
public:
	Identifier(const string &name) :
		m_name(name)
	{
	}

public:
	string name() const
	{
		return m_name;
	}

private:
	string m_name;
};
bool operator==(const Identifier &left, const Identifier &right)
{
	return left.name() == right.name();
}

size_t my_hash(const Identifier &id)
{

	if (id.name().length() == 1)
		return 2 * size_t(id.name()[0]);
	return size_t(id.name()[0]) + size_t(id.name()[1]);
}

size_t two_hash(const Identifier &id)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;

	for (size_t i = 0; i < id.name().length(); i++)
	{
		hash = hash * a + id.name()[i];
		a = a * b;
	}

	return (hash & 0x7FFFFFFF);
}
class IDNotFoundException : exception
{
public:
	IDNotFoundException(const string id_name) :
		m_what(string("Identifier \'") + id_name + "\' not found!")
	{
	}

	virtual ~IDNotFoundException() throw()
	{
	}

public:
	const char *what() const throw()
	{
		return m_what.c_str();
	}

private:
	string m_what;
};
class HashTable
{
public:
	static const size_t min_hash_value = int('A') + int('0');
	static const size_t max_hash_value = int('z') + int('z');
	static const size_t hash_table_size = max_hash_value - min_hash_value;

public:
	void add(const Identifier &id)
	{
		m_hash_table[my_hash(id) - min_hash_value].push_back(id);
	}

	Identifier &get(const string &id_name)
	{
		list<Identifier>& line = m_hash_table[my_hash(id_name) - min_hash_value];
		list<Identifier>::iterator it = find(line.begin(), line.end(), id_name);

		if (it == line.end())
			throw IDNotFoundException(id_name);
		return *it;
	}

private:
	list<Identifier> m_hash_table[hash_table_size];
};
class HashTableClose {

};
int main()
{
	HashTable ht;

	ht.add(Identifier("a"));
	ht.add(Identifier("aa"));
	ht.add(Identifier("if"));
	ht.add(Identifier("fi"));
	ht.add(Identifier("abbbraaadaws"));

	try
	{
		cout << ht.get("a").name() << endl;
		cout << ht.get("aa").name() << endl;
		cout << ht.get("if").name() << endl;
		cout << ht.get("fi").name() << endl;
		cout << ht.get("abbbraaadaws").name() << endl;

		cout << ht.get("hello").name() << endl;
	}
	catch (const IDNotFoundException &ex)
	{
		cerr << ex.what() << endl;
	}

	return 0;
}
