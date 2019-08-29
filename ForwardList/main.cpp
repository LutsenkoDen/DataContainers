#include <iostream>
using namespace std;
#define tab "\t"
#define delimiter "---------------------------------------------"
//#define DESTRUCTOR_CHECK
//#define INDEX_OPERATOR_CHECK
//#define BASE_CHECK
//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define RANGE_BASED_FOR
//#define ITERATORS_CHECK

template<typename T>
class ForwardList
{
	//public:
	template<typename T>
	class Element
	{
		T Data;
		Element<T>* pNext;
		//static int count;
	public:
		Element(T Data, Element<T>* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			//count++;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
			//count--;
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}

		operator T&()
		{
			return this->Data;
		}

		friend class ForwardList;
		friend class Iterator;
		//friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	};
private:
	Element<T>* Head;
	int size;
public:
	class Iterator
	{
		Element<T>* Temp;
	public:
		Iterator(Element<T>* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Element<T>* old = Temp;
			Temp = Temp->pNext;
			return old;
		}

		T& operator*()
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
	Iterator begin() const
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}
	Iterator end() const
	{
		return nullptr;
	}

	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		//Изначально создаем пустой список.
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(int size) :ForwardList<T>()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(T());
#ifdef DEBUG
		cout << "FLConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(initializer_list<T>il) :ForwardList<T>()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			// it - iterator;
			//begin() - возвращает адрес начала контейнера il;
			//end() - возвращает адрес конца контейнера il;
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other)
	{
		this->Head = nullptr;
		this->size = 0;
		//Element* Temp = other.Head; // Итератор нужен для того, чтобы передвигаться
		//while (Temp)
		//{
		//	push_back(Temp->Data);
		//	Temp = Temp->pNext;
		//}
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		//
		//for (Element* Temp = other.Head; Temp != nullptr; Temp++)push_back(*Temp);
		//
		cout << "FLCopyConstructor:\t" << this << endl;
	}

	ForwardList(ForwardList<T>&& other)
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
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = nullptr;
		this->size = 0;
		Element<T>* Temp = other.Head; // Итератор нужен для того, чтобы передвигаться
		/*while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	ForwardList<T>& operator=(ForwardList<T>&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}

	T& operator[](int Index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	// Adding elements:
	void push_front(T Data)
	{
		//Добавляет значение в начало списка.
		//1)Создаем элемент, в который будет помещено добавляемое значение (Data).
		//Element* New = new Element(Data);
		//2)"Пристыковываем" новый элемент к началу списка.
		//New->pNext = Head;
		//Head = New;

		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head; //Temp- это итератор
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;// Переходим на следующий элемент
		}
		Temp->pNext = new Element<T>(Data);
	}

	void insert(int Index, T Data)
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

		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	// deleting elements
	void pop_front()
	{
		Element<T>* Temp = Head; //Запоминаем адрес удаляемого элемента
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
		Element<T>* Temp = Head;
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
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr) break;
			Temp = Temp->pNext;
		}
		Element<T>* toDel = Temp->pNext;
		Temp = Temp->pNext->pNext;
		delete toDel;
		size--;
	}

	void print()
	{
		Element<T>* Temp = Head;//Temp- это итератор
		//Итератор- это указатель, при помощи которого можно получить доступ к элементам структуры данных
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;// Переходим на следующий элемент
		//}
		for (Element<T>* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Колличество элементов списка: " << this->size << endl;
	}
	//friend ForwardList<T> operator+(const ForwardList& left, const ForwardList& right);
	
//template<typename T>
//int ForwardList<T>::Element<T>::count = 0;

//template<typename T>
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
	{
		ForwardList<T> result = left;
		//for (ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->pNext)result.push_back(Temp->Data);
		for (ForwardList<T>::Iterator it = right.begin(); it != right.end(); it++)result.push_back(*it);
		return result;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов:"; cin >> n;
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
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	cout << "Введите индекс добавляемого элемента: "; cin >> Data;
	fl.insert(Index, Data);
	fl.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
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
#ifdef ITERATORS_CHECK
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

	ForwardList<int> fl = { 3, 5, 8, 13, 21 };
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

	ForwardList<double> fld = { 2.7, 3.14, 5.5 };
	for (double i : fld)
	{
		cout << i << tab;
	}
	cout << endl;

	//fld.print();

	for (ForwardList<double>::Iterator it = fld.begin(); it != fld.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif// ITERATORS_CHECK

	ForwardList<int> fl1 = { 3, 5, 8, 13, 21 };
	ForwardList<int> fl2 = { 21, 34, 55, 89 };
	for (ForwardList<int>::Iterator it = fl1.begin(); it != fl1.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (ForwardList<int>::Iterator it = fl2.begin(); it != fl2.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;

	ForwardList<int> lsd = fl1 + fl2;
	lsd.print();
}