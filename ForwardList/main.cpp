#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "---------------------------------------------"
//#define DESTRUCTOR_CHECK
//#define INDEX_OPERATOR_CHECK
//#define BASE_CHECK
//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
#define RANGE_BASED_FOR

class ForwardList
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count;
	public:
		Element(int Data, Element* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			count++;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
			count--;
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}

		operator int()
		{
			return this->Data;
		}

		friend class ForwardList;
		friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	};
private:
	Element* Head;
	int size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Element* old = Temp;
			Temp = Temp->pNext;
			return old;
		}

		int& operator*()
		{
			return Temp->Data;
		}

		bool operator==(const Iterator& other)
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const Iterator& other)
		{
			return this->Temp != other.Temp;
		}
	};
public:
	const int get_size() const
	{
		return this->size;
	}

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//���������� ������� ������ ������.
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(int());
#ifdef DEBUG
		cout << "FLConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(initializer_list<int>il) :ForwardList()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			// it - iterator;
			//begin() - ���������� ����� ������ ���������� il;
			//end() - ���������� ����� ����� ���������� il;
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		this->Head = nullptr;
		this->size = 0;
		//Element* Temp = other.Head; // �������� ����� ��� ����, ����� �������������
		//while (Temp)
		//{
		//	push_back(Temp->Data);
		//	Temp = Temp->pNext;
		//}
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		//
		//for (Element* Temp = other.Head; Temp != nullptr; Temp++)push_back(*Temp);
		//
		cout << "FLCopyConstructor:\t" << this << endl;
	}

	ForwardList(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head != nullptr)pop_front();
		cout << "FLDestructor:\t" << this << endl;
	}
	//Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = nullptr;
		this->size = 0;
		Element* Temp = other.Head; // �������� ����� ��� ����, ����� �������������
		/*while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}

	int& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	// Adding elements:
	void push_front(int Data)
	{
		//��������� �������� � ������ ������.
		//1)������� �������, � ������� ����� �������� ����������� �������� (Data).
		//Element* New = new Element(Data);
		//2)"��������������" ����� ������� � ������ ������.
		//New->pNext = Head;
		//Head = New;

		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head; //Temp- ��� ��������
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;// ��������� �� ��������� �������
		}
		Temp->pNext = new Element(Data);
	}

	void insert(int Index, int Data)
	{
		if (Index = 0)
		{
			push_front(Data);
			return;
		}
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	// deleting elements
	void pop_front()
	{
		Element* Temp = Head; //���������� ����� ���������� ��������
		Head = Head->pNext;  //��������� ������� �� ������
		delete Temp;         //������� �������
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		//while (Temp->pNext->pNext != nullptr)
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void erase(int Index)
	{
		if (Index == 0) {
			pop_front();
			return;
		}
		if (Index >= Element::count)
		{
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		Element* toDel = Temp->pNext;
		Temp = Temp->pNext->pNext;
		delete toDel;
		size--;
	}

	void print()
	{
		Element* Temp = Head;//Temp- ��� ��������
		//��������- ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;// ��������� �� ��������� �������
		//}
		for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "����������� ��������� ������: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int ForwardList::Element::count = 0;

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	for (ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->pNext)result.push_back(Temp->Data);
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ���������� ���������:"; cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	fl.push_back(123);
	fl.print();
	cout << delimiter << endl;
	fl.pop_front();
	fl.print();
	cout << delimiter << endl;
	fl.pop_back();
	fl.print();
	int Index;
	int Data;
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	cout << "������� ������ ������������ ��������: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	fl.erase(Index);
	fl.print();
#endif // BASE_CHECK

#ifdef DESTRUCTOR_CHECK
	ForwardList chain;
	for (int i = 0; i < n; i++)
	{
		chain.push_front(rand() % 100);
	}
	//chain.print();
	cout << "list full" << endl;

#endif // DESTRUCTOR_CHECK

#ifdef INDEX_OPERATOR_CHECK
	ForwardList fl(n);
	fl.print();
	for (int i = 0; i < fl.get_size(); i++)
	{
		fl[i] = rand() % 100;
	}
	for (int i = 0; i < fl.get_size(); i++)
	{
		cout << fl[i] << "\t";
	}
	cout << endl;
#endif INDEX_OPERATOR_CHECK
#ifdef CONSTRUCTORS_CHECK

	ForwardList fl1 = { 3, 5, 8, 13, 21 }; // Initializer_list constructor
	for (int i = 0; i < fl1.get_size(); i++)
		cout << fl1[i] << tab;
	cout << endl;

	ForwardList fl2 = fl1; // Copy constructor
	fl2.print();
#endif // CONSTRUCTORS_CHECK
#ifdef OPERATORS_CHECK
	ForwardList fl1 = { 3, 5, 8, 13, 21 };
	ForwardList fl2 = { 34, 55, 89 };
	for (int i = 0; i < fl1.get_size(); i++)
	{
		cout << fl2[i] << tab;
	}
	cout << endl;
	ForwardList fl3;
	fl3 = fl1 + fl2;
	fl3.print();

	/*ForwardList fl2;
	fl2 = fl1;
	fl2.print();*/

#endif // OPERATORS_CHECK

	/*int Arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(Arr) / sizeof(int); i++)
	{
		cout << Arr[i] << tab;
	}
	cout << endl;

	for (int i : Arr)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << sizeof(Arr) << endl;*/

	ForwardList fl = { 3, 5, 8, 13, 21 };
	/*for (ForwardList::Iterator it = fl.begin(); it != fl.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	for (int i : fl)
	{
		cout << i << tab;
	}
	cout << endl;
}