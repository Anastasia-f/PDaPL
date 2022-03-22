// одномерный массив с элементами типа int. сортировка Шелла. операторы-члены класса-индексация элемента[],пересечение массивов &.  дружественные функции-операторы-вывод в поток(<<)
#include <iostream>
#include <iomanip>
using namespace std;
class carray {
private:
	int* ms;
	int size;
public:
	carray() {//конструктор по умолчанию
		size = 0;
		ms = new int[size];
	}
	carray(int size_1) {// конструктор инициализации
		size = size_1;
		ms = new int[size];
		for (int i = 0; i < size; i++) {
			ms[i] = 0;
		}
	}
	carray(const carray& array_copy) {// конструктор копирования
		size = array_copy.size;
		ms = new int[size];
		for (int i = 0; i < size; i++) {
			ms[i] = array_copy.ms[i];
		}
	}
	~carray() {// деструктор
		delete[] ms;
	}
	void input() {// ввод элементов в массив
		cout <<endl<< "input the nember of elements in array: " << endl;
		cin >> size;
		ms = new int[size];
		cout << "input elements" << endl;
		for (int i = 0; i<size;i++) {
			cin >> ms[i];
		}
	}
	void output() {
		cout <<endl<< "array" << endl;
		for (int i = 0; i < size; i++) {
			cout << ms[i]<<" ";
		}
	}
	void input_one_element() {//вывод по элементу 
		int element;
		do {
			cout << endl << "enter the number of element" << endl;
			cin >> element;
		} while (element<1 || element>size);

			cout << "enter the element"<<endl;
			if (element == 0)   cin >> ms[element - 1];
		 	else 	            cin >> ms[element - 1];
		
	}
	void output_one_element(){
		int element;
		do {
			cout << endl << "eneter the number of element: " << endl;
			cin >> element;
		} while(element<1 || element>size);
			
				if (element == 0) cout << ms[element-1];
				else              cout << ms[element-1];

	}
	int & operator[] (int index) {//перегрузка оператора []
		return ms[index];
	}
	int array_size() {
		return size;
	}
	bool operator &(carray& ms2) {// перегрузка оператора пересечения массивов &
		int fl = 0;
		carray ms3(ms2.size);
		for (int l = 0; l < ms2.size; l++) {
			ms3[l] = ms2[l];
		}
		int i = 0, j = 0;
		for (i = 0; i < size; i++) {
			if (ms3[j] == ms[i]) {
				for (int k = 0; k < ms3.size; k++) {
					ms3[k] = ms3[k + 1];
				}
				ms3.size--;
			}
			if (ms3.size == 0)  return true;
		}
		return false;

	}
	friend ostream& operator<<(ostream& out, const carray& array);
	//friend bool operator &(carray& ms1, carray& ms2);
	friend void sort(carray& array, int size);
};

ostream& operator <<(ostream& out, const carray& array) {//перегрузка оператора вывода <<
	for (int i = 0; i < array.size; i++) {
		out << array.ms[i] << " ";
	}
	return out;
}
int main() {
	carray ms1(5),ms2(ms1);
	int size;
	cout << "work with 1 array" << endl;
	ms1.output();
	ms1.input();
	ms1.output();
	cout <<endl<<"operator []"<<endl<< ms1[3]<<endl;// оператор[]
	ms1.input_one_element();
	ms1.output();
	ms1.output_one_element();
	size=ms1.array_size();
	sort(ms1,size);// сортировка
	ms1.output();
	cout<< endl <<"operator << "<<endl<< ms1;
	/////////////////////////////////////////////
	carray ms5,ms6;
	cout << "now we work with ms5 and ms6 " << endl;
	ms5.input();
	ms5.output();
	ms6.input();
	ms6.output();
	int size_ms5,size_ms6;
	size_ms5=ms5.array_size();
	size_ms6 = ms6.array_size();
	sort(ms5, size_ms5);
	sort(ms6, size_ms6);
	if (size_ms5 >= size_ms6) {
		if (ms5 & ms6)   cout << "ms1&ms2  -_-" << endl;
		else cout << "ms1 not& ms2  -    _-" << endl;
	}
	else {
		if (ms6 & ms5)   cout << "ms1&ms2  -_-" << endl;
		else cout << "ms1 not& ms2  -    _-" << endl;
	}
	/////////////////////////////////////////////
	carray* ms3,*ms4;
	ms3 = new carray();
	ms3->input();
	ms3->output();
	ms4 = new carray(*ms3);
	ms3->input_one_element();
	ms3->output();
	ms4->output();
	delete ms3;
	delete ms4;
	
	////////////////////////////////////////////
	int n;
	cout <<endl<< " input the number of arrays " << endl;
	cin >> n;
	carray* ms = new carray[n];
	for (int i = 0; i < n; i++) {
		ms[i].input();
	}
	for (int i = 0; i < n; i++) {
		ms[i].output();
	}
	delete[] ms;
	return 0;
}
void sort(carray& array, int size) {
	int i, j, k, increment, temp;
	int swp = 0, comp = 0; increment = size / 2;
	while (increment > 0)
	{
		for (i = 0; i < increment; i++)
		{
			for (j = 0; j < size; j += increment)
			{
				temp = array.ms[j];
				for (k = j - increment; k >= 0 && temp < array.ms[k]; k -= increment)
				{
					comp++;
					swp++;
					array.ms[k + increment] = array.ms[k];
				}
				array.ms[k + increment] = temp;
				swp++;
			}
		}
		comp++;
		if (increment / 2 != 0)
			increment = increment / 2;
		else if (increment == 1)
			increment = 0;
		else
			increment = 1;
	}
}

