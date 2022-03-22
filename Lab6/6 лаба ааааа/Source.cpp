// stack//
#include<iostream>
#include<string.h>
using namespace std;
 template <class T = int>//////
 class stack
 {
 private:
	 struct FILO {
		 T data;
		 FILO* next;
	 };

	 FILO* head;
	 FILO* list;
	 FILO* tail;
	 FILO* top;

 public:
	 stack()  {
		 head = nullptr;
		 list = nullptr;
		 tail = nullptr;
		 top = nullptr;
	 }
	 void AddToStart()// добавление
	 {
		 T element;
		 cout << "input element" << endl;
		 cin >> element;
		 FILO* p = new FILO();
		 p->data = element;
		 p->next = top;
		 top = p;
	 }
	 void Display()// вывод
	 {
		 FILO* p;
		 if (top != NULL) {
			 p = top;
			 while (p != NULL) {
				 cout << p->data;
				 p = p->next;
				 cout << endl;
			 }
		 }
	 }
	 void Delete()//удаление
	 {
		 FILO* p;
		 if (top != NULL) {
			 p = top;
			 top = top->next;
			 free(p);
		 }
	 }
	 void find_element() // нахождение элемента
	 {
		 FILO* p;
		 int fl = 1;
		 T element;
		 cout << "input element" << endl;
		 cin >> element;
		 if (top != NULL) {
			 p = top;
			 while (p != NULL) {
				 if (element == p->data)  {
					 cout << "its element in stack" << endl;
					 cout << p->data << endl;
				 }

				 p = p->next;
				 cout << endl;
			 }
		 }

	 }
	 void sort()// сортировка
	 {

		 FILO* t = NULL, * t1;
		 FILO* p = top;
		 T r;
		 do  {

			 for (t1 = p; t1->next != t; t1 = t1->next)

				 if (t1->data > t1->next->data)	 {

					 r = t1->data;

					 t1->data = t1->next->data;

					 t1->next->data = r;
				 }
			 t = t1;
		 } while (p->next != t);
	 }
	 T comparison() {// сравнение
		 FILO* p=head;
		 int fl = 0;
		 if (top != NULL) {
			 p = top;
			 while (p != NULL)	 {
				 p = p->next;
				 fl++;
			 }
		 }
		 return fl;
	 }
 };
class in :public stack<>///// наследование
{
public:
	void show(){
		cout << "inheritance works" << endl;
	}
};
template<>// char
class stack<char>
{
protected:
	struct FILO
	{
		char *data;
		FILO* next;
	};

	FILO* head;
	FILO* list;
	FILO* tail;
	FILO* top;

public:
	stack() {
		head = nullptr;
		list = nullptr;
		tail = nullptr;
		top = nullptr;
	}
	void AddToStart()
	{
		char *element1;
		cout << "input char: " << endl;
		element1 = new char[6];
		cin >> element1;
		FILO* p = new FILO();
		p->data = new char[6];
		p->data = element1;
		p->next = top;
		top = p;
	}
	void Display()
	{
		FILO* p;
		if (top != NULL){
			p = top;
			while (p != NULL)	{
				cout << p->data;
				p = p->next;
				cout << endl;
			}
		}
	}
	void Delete()
	{
		FILO* p;
		if (top != NULL)
		{
			p = top;
			top = top->next;
			free(p);
		}
	}
	void find_element()
	{
		FILO* p;
		int fl = 1;
		char *element1;
		element1 = new char[6];
		cout << "\nEnter the element: " << endl;
		cin >> element1;
		
		if (top != NULL)
		{
			p = top;
			p->data = new char[6];
			while (p != NULL)
			{
				int a = strcmp(element1, p->data);
				if (a==0)
				{
					cout << "its element in stack" << endl;
					break;
				}

				p = p->next;
				cout << endl;
			}
		}

	}
	void sort()
	{
		FILO* t = NULL, * t1;
		FILO* p = top;

		char* r;

		do	{
			for (t1 = p; t1->next != t; t1 = t1->next)
				if (t1->data > t1->next->data){
					r = t1->data;
					t1->data = t1->next->data;
					t1->next->data = r;
				}
			t = t1;
		} while (p->next != t);
	}
};
template <class T>
void menu(stack<T>& st) {
	int choice;
	do {
		cout << "input 1-input" << endl << "2-output" << endl << "3-delete" << endl << "4-find element" << endl <<"5-sort"<<endl<< "6-end" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			st.AddToStart();
			break;
		case 2:
			st.Display();
			break;
		case 3:
			st.Delete();
			break;
		case 4:
			st.find_element();
			break;
		case 5:
			st.sort();
			break;
		case 6: return;
		}


	} while (1);
}



int main() {
	int size1, size2;
	stack<int> st1;
	menu(st1);
	
	stack<> st2;//without argument int/double
	menu(st2);
	size1 = st1.comparison();
	cout << endl << "size1: " << size1 << endl;
	size2 = st2.comparison();
	cout << endl << "size2: " <<size2<< endl;
	if (size1 > size2)  cout << "size1>size2" << endl;
	if (size1 < size2)  cout << "size1<size2" << endl;
	if (size1 == size2) cout << "size1=size2" << endl;
	stack<double> st3;// with arument double
	menu(st3);
	stack<char> st4;// with argument char
	menu(st4);
	




	in a;
	a.show();
	return 0;
}
//1+ 2+ 3+ 4+ 5+ 6+ 7+