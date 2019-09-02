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
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t\t" << this << endl;
		}
		friend class List;
	};
	Element* Head;
	Element* Tail;
	int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t\t" << this << endl;
	}

	// Adding elements:
	void push_front(int Data)
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

	void push_back(int Data)
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

	void insert(int Index, int Data)
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
		if (Index > size / 2)
		{
			Element* Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
			Element* Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pPrev;
		}
		Temp->pPrev = new Element(Data, Temp->pPrev);
		size++;

	}

	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "В списке: " << size << " элементов. " << endl;
	}
	void print_revers()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
		}
		cout << "В списке: " << size << " элементов. " << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n = 5;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_front(123);
	list.print();
	list.print_revers();
	int Index;
	int Data;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> Data;
	list.insert(Index, Data);
	list.print();
}