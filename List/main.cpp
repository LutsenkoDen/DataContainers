
#include "List.h";



//#define BASE_CHECK
#define CONSTRUCTORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
	int n = 5;
	//cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> Data;
	list.insert(Index, Data);
	list.print();
	list.print_revers();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
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