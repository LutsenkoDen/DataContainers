#include <iostream>
using namespace std;

#define tab "\t"

//#define BASE_CHECK
#define CONSTRUCTORS_CHECK

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

List::Element::Element(int Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t\t" << this << endl;
}
List::Element::~Element()
{
	cout << "EDestructor:\t\t" << this << endl;
}

List::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;
	cout << "ITConstructor:\t\t" << this << endl;
}
List::Iterator::~Iterator()
{
	cout << "ItDestructor:\t\t" << this << endl;
}


List::Iterator& List::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

const int& List::Iterator::operator*() const
{
	return Temp->Data;
}

int& List::Iterator::operator*()
{
	return Temp->Data;
}

bool List::Iterator::operator==(const Iterator& other)
{
	return this->Temp == other.Temp;
}

bool List::Iterator::operator!=(const Iterator& other)
{
	return this->Temp != other.Temp;
}

int List::get_size() const
{
	return this->size;
}

const List::Iterator List::begin() const
{
	return this->Head;
}

List::Iterator List::begin()
{
	return this->Head;
}

const List::Iterator List::end() const
{
	return nullptr;
}

List::Iterator List::end()
{
	return nullptr;
}

List::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t\t" << this << endl;
}

List::List(initializer_list<int> il) :List()
{
	for (const int* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}

List::~List()
{
	while (Head)pop_front();
	cout << "LDestructor:\t\t" << this << endl;
}

// Operators:
int& List::operator[](int Index)
{
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = size - 1; i > Index; i--)Temp = Temp->pPrev;
	}
	return Temp->Data;
}

const int& List::operator[](int Index) const
{
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = size - 1; i > Index; i--)Temp = Temp->pPrev;
	}
	return Temp->Data;
}

// Adding elements:
void List::push_front(int Data)
{
	Element* New = new Element(Data);
	size++;
	if (Head == nullptr&&Tail == nullptr)
	{
		Head = Tail = New;
		return;
	}
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;
}

void List::push_back(int Data)
{
	Element* New = new Element(Data);
	size++;
	if (Head == nullptr&&Tail == nullptr)
	{
		Head = Tail = New;
		return;
	}
	New->pPrev = Tail;
	Tail->pNext = New;
	Tail = New;
}

void List::insert(int Index, int Data)
{
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	if (Head == nullptr && Tail == nullptr)
	{
		push_back(Data);
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - 1 - Index; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

// Deleting elements:
void List::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}

void List::pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		return;
	}
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

void List::erase(int Index)
{
	if (Index == 0)
	{
		pop_front();
		return;
	}
	if (Index >= size - 1)
	{
		pop_back();
		return;
	}
	if (Head == nullptr || Head == Tail)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - 1 - Index; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}

void List::print()
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "� ������: " << size << " ���������. " << endl;
}
void List::print_revers()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
	}
	cout << "� ������: " << size << " ���������. " << endl;
}

void main()
{
	setlocale(LC_ALL, "");
	int n = 5;
	//cout << "������� ������ ������: "; cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_front(123);
	list.print();
	int Index;
	int Data;
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ ��������: "; cin >> Data;
	list.insert(Index, Data);
	list.print();
	list.print_revers();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	list.erase(Index);
	list.print();
	list.print_revers();
#endif // BASE_CHECK
#ifdef CONSTRUCTORS_CHECK
	List lst1 = { 3, 5, 8, 13, 21 };
	lst1.print();
	//for (int i = 0; i < lst1.get_size(); i++)lst1[i] = rand() % 100;
	for (int i = 0; i < lst1.get_size(); i++)
		cout << lst1[i] << tab;
	cout << endl;
	for (int i : lst1)
	{
		cout << i << tab;
	}

	/*List lst2 = { 34, 55, 89 };
	for (int i = 0; i < lst2.get_size(); i++)
		cout << lst2[i] << tab;
	List lst3 = lst1 + lst2;
	for (int i : lst3)
	{
		cout << i << tab;
	}
	cout << endl;*/

#endif // CONSTRUCTORS_CHECK
}