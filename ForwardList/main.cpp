#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "---------------------------------------------"
//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define INDEX_OPERATOR_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK

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
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	int size;
public:
	const int get_size() const
	{
		return this->size;
	}
	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//Изначально создаем пустой список.
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(int());
	}
	ForwardList(std::initializer_list<int> il) :ForwardList()
	{
		//std::cout << typeid(il.begin()).name() << std::endl;
		for (int const * it = il.begin(); it != il.end(); it++)
		{
			//it - iterator;
			//begin() - возвращает адрес начала контейнера il;
			//end()   - возвращает адрес конца контейнера il;
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		this->Head = nullptr;
		this->size = 0;
		//Element* Temp = other.Head;	//Итератор нужен для того, чтобы перемещаться по ДРУГОМУ списку
		//while (Temp)
		//{
		//	push_back(Temp->Data);
		//	Temp = Temp->pNext;
		//}
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
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
	// Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveAssignemtn:\t" << this << endl;
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
		//Добавляет значение в начало списка.
		//1)Создаем элемент, в который будет помещено добавляемое значение (Data).
		//Element* New = new Element(Data);
		//2)"Пристыковываем" новый элемент к началу списка.
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
		Element* Temp = Head; //Temp- это итератор
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;// Переходим на следующий элемент
		}
		Temp->pNext = new Element(Data);
		size++;
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
		size++;
	}
	// Deleting elements:
	void pop_front()
	{
		Element* Temp = Head; //Запоминаем адрес удаляемого элемента
		Head = Head->pNext;  //Исключаем элемент из списка
		delete Temp;         //Удаляем элемент
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
		size--;
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
		size--;
	}
	void print()
	{
		Element* Temp = Head;//Temp- это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;// Переходим на следующий элемент
		//}
		for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
	int n;  //Количество элементов списка.
	cout << "Введите количество элементов:"; cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;	//Создаем пустой список.
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
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << delimiter << endl;
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	fl.erase(Index);
	fl.print();
	/*ForwardList fl1;
	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		fl1.push_back(rand() % 100);
	}
	fl1.print();*/
#endif // BASE_CHECK

#ifdef DESTRUCTOR_CHECK
	ForwardList chain;
	for (int i = 0; i < n; i++)
	{
		chain.push_front(rand() % 100);
	}
	//chain.print();
	cout << "List full" << endl;
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
#endif // INDEX_OPERATOR_CHECK

#ifdef CONSTRUCTORS_CHECK
	ForwardList fl1 = { 3, 5, 8, 13, 21 };	//initializer_list constructor
	fl1 = fl1;
	for (int i = 0; i < fl1.get_size(); i++)
		cout << fl1[i] << tab;
	cout << endl;
	ForwardList fl2;
	fl2 = fl1;	//Copy constructor
	fl2.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	ForwardList fl1 = { 3, 5, 8, 13, 21 };
	ForwardList fl2 = { 34, 55, 89 };
	for (int i = 0; i < fl1.get_size(); i++)
	{
		cout << fl1[i] << tab;
	}
	cout << endl;
	for (int i = 0; i < fl2.get_size(); i++)
	{
		cout << fl2[i] << tab;
	}
	cout << endl;

	ForwardList fl3;
	fl3 = fl1 + fl2;
	fl3.print();
	cout << sizeof(Element) << endl;
#endif
}