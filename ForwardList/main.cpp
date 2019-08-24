#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "---------------------------------------------"
#define BASE_CHECK

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
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		this->Head = nullptr;
		//���������� ������� ������ ������.
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
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
		if (Index == 0)
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
	}
	// Deleting elements:
	void pop_front()
	{
		Element* Temp = Head; //���������� ����� ���������� ��������
		Head = Head->pNext;  //��������� ������� �� ������
		delete Temp;         //������� �������
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
		if (Index == 0)
		{
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
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element* toDel = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete toDel;
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
};

void main()
{
	setlocale(LC_ALL, "");
	int n;  //���������� ��������� ������.
	cout << "������� ���������� ���������:"; cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;	//������� ������ ������.
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
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ ��������: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << delimiter << endl;
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	fl.erase(Index);
	fl.print();
#endif // BASE_CHECK
}