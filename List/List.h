#pragma once
#include <iostream>
using namespace std;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	};
	Element* Head;
	Element* Tail;
	int size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		Iterator& operator++();
		const int& operator*() const;
		int& operator*();
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);
	};

	int get_size() const;

	const Iterator begin() const;

	Iterator begin();

	const Iterator end() const;

	Iterator end();

	List();

	List(initializer_list<int> il);

	~List();

	// Operators:
	int& operator[](int Index);

	const int& operator[](int Index) const;

	// Adding elements:
	void push_front(int Data);

	void push_back(int Data);

	void insert(int Index, int Data);

	// Deleting elements:
	void pop_front();

	void pop_back();

	void erase(int Index);

	void print();
	void print_revers();
};