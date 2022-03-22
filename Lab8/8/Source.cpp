#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <vector>

const int lenght_buf = 30;
using namespace std;
class File;

class Time {
private:
	int m_hour;
	int m_minute;
	int m_second;
public:
	Time(int hour = 0, int minute = 0, int second = 0) :
		m_hour(hour), m_minute(minute), m_second(second) {}
	~Time() {}

	friend bool operator >(const Time type_1, const Time type_2);
	friend bool operator <(const Time type_1, const Time type_2);
	friend ostream& operator<<(ostream& out, const Time& time);
};

class Bus_flight {
private:
	int m_number_Bus;
	int m_type_Bus;
	string m_destination;
	Time m_departure_time;
	Time m_arrival_time;

public:
	Bus_flight(int number_Bus = 0, int type_Bus = 0, string destination = "", Time departure_time = (0, 0, 0), Time arrival_time = (0, 0, 0)) :
		m_number_Bus(number_Bus), m_type_Bus(type_Bus), m_destination(destination), m_departure_time(departure_time), m_arrival_time(arrival_time) {}

	~Bus_flight() {};

	friend bool operator <(const Bus_flight, const Bus_flight);
	friend bool operator >(const Bus_flight, const Bus_flight);
	friend bool operator ==(const Bus_flight, const Bus_flight);
	friend bool operator !=(const Bus_flight, const Bus_flight);
	friend ostream& operator<<(ostream&, const Bus_flight&);

	friend Time;
	friend File;
};

class Exception {
private:
	int m_error;
public:
	Exception(int error = 0) :
		m_error(error) {}

	void what() {
		switch (m_error) {
		case 0: cout << "Exception" << endl; break;
		case 1: cout << "Can't insert dublicate" << endl; break;
		case 2: cout << "No such value" << endl; break;
		case 3: cout << "Pointer is empty" << endl; break;
		case 4: cout << "Can't open such file" << endl; break;
		}
	}
};

template <class T>
class Iterator;
template <class T>
class List;

template <class T>
class Node {
private:
	T data;
	Node* prev;
	Node* next;
	Node* head;

	friend Iterator<T>;
	friend List<T>;
};

template <class T>
class Iterator {
private:
	Node<T>* m_nodePointer;

public:
	Iterator(Node<T>* nodePointer = nullptr) :
		m_nodePointer(nodePointer) {}
	~Iterator() {
		m_nodePointer = nullptr;
	}

	T GetValue() {
		if (m_nodePointer != nullptr) {
			return m_nodePointer->data;
		}
		else {
			throw 3;
		}
	}
	void Next() {
		if (m_nodePointer->next != nullptr) {
			m_nodePointer = m_nodePointer->next;
		}
		else {
			throw 3;
		}
	}
	void Prev() {
		if (m_nodePointer->prev != nullptr) {
			m_nodePointer = m_nodePointer->prev;
		}
		else {
			throw 3;
		}
	}

	bool operator == (const Iterator& el_1) {
		return m_nodePointer == el_1.m_nodePointer;
	}
	bool operator != (const Iterator& el_1) {
		return !(m_nodePointer == el_1.m_nodePointer);
	}
};

template <class T>
class List {
public:
	List() {
		head = nullptr;
		size = 0;
	}

	Iterator<T> Begin() {
		Node<T>* temp = head;
		while (temp->prev) {
			temp = temp->prev;
		}
		return temp;
	}

	Iterator<T> End() {
		Node<T>* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		return temp;
	}

	Node<T>* GetNodeByValue(T value) {
		Node<T>* temp = head;
		while (temp) {
			if (temp->data != value) {
				temp = temp->next;
				continue;
			}
			else {
				return temp;
			}
		}
		throw 2;
	}

	void InsertNode(T value) {
		if (!head) {
			head = GetFreeNode(value, nullptr);
			size++;
		}
		else {
			Node<T>* node = head;
			while (node) {
				if (node->next) {
					node = node->next;
					continue;
				}
				else if (node->data == value) {
					throw 1;
				}
				else {
					node->next = GetFreeNode(value, node);
					size++;
					return;
				}
			}
		}
	}

	void EraseNodeByValue(T l_value) {
		Node<T>* target = GetNodeByValue(l_value);
		RawEraseNode(target);
	}

	void bubble_sort() {
		Node<T>* ptr;

		for (int i = 0; i < size; i++) {

			Node<T>* elem_1 = head;
			Node<T>* elem_2 = head->next;

			for (int j = 0; j < size - 1; j++) {

				if (elem_1->data > elem_2->data) {

					if (elem_1->prev)
						ptr = elem_1->prev;
					else
						ptr = nullptr;

					if (elem_1 == head) {
						head = elem_2;
						head->prev = nullptr;
					}

					if (elem_1->prev)
						elem_1->prev->next = elem_2;

					if (elem_2->next) {
						elem_2->next->prev = elem_1;
						elem_1->next = elem_2->next;
					}
					else
						elem_1->next = nullptr;

					elem_1->prev = elem_2;
					elem_2->next = elem_1;

					if (ptr)
						elem_2->prev = ptr;

					ptr = elem_1;
					elem_1 = elem_2;
					elem_2 = ptr;
				}
				elem_1 = elem_1->next;
				elem_2 = elem_2->next;
			}
		}
	}

	void print() {
		Iterator<T> it = this->Begin();
		while (true) {
			if (it == this->End()) {
				std::cout << it.GetValue() << "; ";
				break;
			}
			std::cout << it.GetValue() << "; ";
			try {
				it.Next();
			}
			catch (int exIndex) {
				Exception ex(exIndex);
				ex.what();
			}
		}
		std::cout << std::endl;
	}
private:
	Node<T>* head;
	int size;

	void RawEraseNode(Node<T>* target) {
		if (target->prev && target->next) {
			target->prev->next = target->next;
			target->next->prev = target->prev;
		}
		else if (target->next == nullptr) {
			target->prev->next = nullptr;
		}
		else if (target->prev == nullptr) {
			head->next->prev = nullptr;
			head = head->next;
		}
		delete target;
		size--;
	}

	Node<T>* GetFreeNode(T value, Node<T>* node) {
		Node<T>* temp = new Node<T>;
		temp->data = value;
		temp->next = nullptr;
		temp->prev = node;
		return temp;
	}
};

bool operator <(const Time type_1, const Time type_2) {
	if (type_1.m_hour < type_2.m_hour)
		return true;
	else if (type_1.m_hour == type_2.m_hour) {
		if (type_1.m_minute < type_2.m_minute)
			return true;
		else if (type_1.m_minute == type_2.m_minute)
			if (type_1.m_second < type_2.m_second)
				return true;
			else return false;
		else return false;
	}
	else return false;
}
bool operator >(const Time type_1, const Time type_2) {
	return !(type_1 < type_2);
}
bool operator <(const Bus_flight type_1, const Bus_flight type_2) {
	return type_1.m_arrival_time < type_2.m_arrival_time;
}
bool operator >(const Bus_flight type_1, const Bus_flight type_2) {
	return !(type_1 < type_2);
}
bool operator ==(const Bus_flight type_1, const Bus_flight type_2) {
	return type_1.m_number_Bus == type_2.m_number_Bus;
}
bool operator !=(const Bus_flight type_1, const Bus_flight type_2) {
	return !(type_2 == type_2);
}

std::ostream& operator<<(std::ostream& out, const Bus_flight& bus_flight) {
	out << "Number_Bus: " << bus_flight.m_number_Bus << endl;
	out << "Type_Bus: " << bus_flight.m_type_Bus << endl;
	out << "Destination: " << bus_flight.m_destination << endl;
	out << endl << "Departure_time: " << bus_flight.m_departure_time << endl;
	out << "Arrival_time: " << bus_flight.m_arrival_time << endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Time& time) {
	out << endl;
	out << "Hour: " << time.m_hour << endl;
	out << "Minute: " << time.m_minute << endl;
	out << "Second: " << time.m_second << endl;
	return out;
}

class File {
public:
	File(string filePath);
	void ReadTextFormat();
	void WriteTextFormat(const Bus_flight&);
	void ReadBinFormat();
	void WriteBinFormat(const Bus_flight&);
	void Alk_1_Find_flight(Time);
	void DelByName(string name);
	void FindByName(string name);
	void quicksort_number_Bus(int, int);
	void quicksort_type_Bus(int, int);
	void quicksort_D_time(int, int);
	void quicksort_A_time(int, int);
	void quicksort_destination(int, int);
	int CountElementOfBinFile();

	friend Time;

private:
	string filePath;
	fstream ioFile;

	void GetElementOfBinFile(Bus_flight&);
};

int main() {
	File file1("yeee.txt");
	File file2("yeee1.txt");
	File file3("yeee2.bin");

	List<Bus_flight> list;

	Time For_Alk_1{ 20,20,0 };

	list.InsertNode(Bus_flight(5, 1, "Minsk", Time(15, 15, 15), Time(17, 20, 55)));
	list.InsertNode(Bus_flight(4, 2, "Brest", Time(16, 15, 15), Time(19, 20, 15)));
	list.InsertNode(Bus_flight(3, 3, "Grodno", Time(15, 15, 15), Time(20, 15, 15)));
	list.InsertNode(Bus_flight(2, 4, "Mogilev", Time(15, 15, 15), Time(19, 15, 15)));
	list.InsertNode(Bus_flight(1, 5, "Gomel", Time(15, 15, 15), Time(21, 16, 15)));

	Iterator<Bus_flight> it = list.Begin();

	while (true) {
		if (it == list.End()) {
			file1.WriteTextFormat(it.GetValue());
			break;
		}
		file1.WriteTextFormat(it.GetValue());
		it.Next();
	}

	it = list.Begin();
	while (true) {
		if (it == list.End()) {
			file2.WriteBinFormat(it.GetValue());
			break;
		}
		file2.WriteBinFormat(it.GetValue());
		it.Next();
	}

	it = list.Begin();
	while (true) {
		if (it == list.End()) {
			file3.WriteBinFormat(it.GetValue());
			break;
		}
		file3.WriteBinFormat(it.GetValue());
		it.Next();
	}


	std::cout << "Text File, Text format:\n" << "-------------------------\n";
	file1.ReadTextFormat();
	std::cout << "\nText File, bin format:\n" << "-------------------------\n";
	file2.ReadBinFormat();
	std::cout << "Bin File:\n" << "-------------------------\n";
	file3.ReadBinFormat();

	std::cout << "Alk_1_Find_flight:\n" << "-------------------------\n";
	file3.Alk_1_Find_flight(For_Alk_1);


	file1.DelByName("Minsk");
	std::cout << "Quicksort_Number_Bus\n" << "-------------------------\n";
	int filesize = file3.CountElementOfBinFile();
	file3.quicksort_number_Bus(0, --filesize);
	file3.ReadBinFormat();

	/*std::cout << "Sorted by name:\n" << "-------------------------\n";
	file3.ReadBinFormat();*/
	std::cout << "Find by name:\n" << "-------------------------\n";
	file3.FindByName("Brest");
	cout << "---------------------------------------------------------------------\n";
	file1.ReadTextFormat();
}

void File::quicksort_number_Bus(int first, int last) {
	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next, mid_elem, cur_f, cur_l;

	int f = first, l = last;
	int mid = (f + l) / 2;

	vector<int> Pos;
	ioFile.seekg(0, ios::beg);
	for (int i = 0; i < last + 1; i++) {
		Pos.push_back(ioFile.tellg());
		GetElementOfBinFile(cur);
	}

	for (int i = 0; i < mid; i++) {
		ioFile.seekg(Pos[i], ios::beg);
		GetElementOfBinFile(cur);
	}
	GetElementOfBinFile(mid_elem);

	do
	{
		do {
			ioFile.seekg(Pos[f], ios::beg);
			GetElementOfBinFile(cur_f);
			f++;
		} while (cur_f.m_number_Bus < mid_elem.m_number_Bus);

		do {
			ioFile.seekg(Pos[l], ios::beg);
			GetElementOfBinFile(cur_l);
			l--;
		} while (cur_l.m_number_Bus > mid_elem.m_number_Bus);

		--f; ++l;
		if (f <= l)
		{
			int cur_f_Pos = Pos[f];
			int cur_l_Pos = Pos[l];

			ioFile.seekg(cur_f_Pos, ios::beg);
			GetElementOfBinFile(cur);
			ioFile.seekg(cur_l_Pos, ios::beg);
			GetElementOfBinFile(next);

			ioFile.seekp(cur_f_Pos, ios::beg);

			ioFile.write((char*)&next.m_number_Bus, sizeof(int));
			ioFile.write((char*)&next.m_type_Bus, sizeof(int));

			ioFile.write(next.m_destination.data(), lenght_buf);

			ioFile.write((char*)&next.m_departure_time, sizeof(Time));
			ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

			ioFile.seekp(cur_l_Pos, ios::beg);

			ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
			ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

			ioFile.write(cur.m_destination.data(), lenght_buf);

			ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
			ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

			f++;
			l--;
		}
	} while (f < l);

	for (int i = 0; i < last + 1; i++) {
		Pos.pop_back();
	}
	ioFile.close();

	if (first < l) quicksort_number_Bus(first, l);
	if (f < last) quicksort_number_Bus(f, last);
}

void File::Alk_1_Find_flight(Time time) {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, ios::in | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight temp;
	for (int i = 0; i < fileSize; i++) {
		GetElementOfBinFile(temp);
		if (temp.m_arrival_time < time) {
			cout << temp << endl;
		}
	}

	ioFile.close();
}

void File::quicksort_D_time(int first, int last) {
	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next, mid_elem, cur_f, cur_l;

	int f = first, l = last;
	int mid = (f + l) / 2;

	vector<int> Pos;
	ioFile.seekg(0, ios::beg);
	for (int i = 0; i < last + 1; i++) {
		Pos.push_back(ioFile.tellg());
		GetElementOfBinFile(cur);
	}

	for (int i = 0; i < mid; i++) {
		ioFile.seekg(Pos[i], ios::beg);
		GetElementOfBinFile(cur);
	}
	GetElementOfBinFile(mid_elem);

	do
	{
		do {
			ioFile.seekg(Pos[f], ios::beg);
			GetElementOfBinFile(cur_f);
			f++;
		} while (cur_f.m_departure_time < mid_elem.m_departure_time);

		do {
			ioFile.seekg(Pos[l], ios::beg);
			GetElementOfBinFile(cur_l);
			l--;
		} while (cur_l.m_departure_time > mid_elem.m_departure_time);

		--f; ++l;
		if (f <= l)
		{
			int cur_f_Pos = Pos[f];
			int cur_l_Pos = Pos[l];

			ioFile.seekg(cur_f_Pos, ios::beg);
			GetElementOfBinFile(cur);
			ioFile.seekg(cur_l_Pos, ios::beg);
			GetElementOfBinFile(next);

			ioFile.seekp(cur_f_Pos, ios::beg);

			ioFile.write((char*)&next.m_number_Bus, sizeof(int));
			ioFile.write((char*)&next.m_type_Bus, sizeof(int));

			ioFile.write(next.m_destination.data(), lenght_buf);

			ioFile.write((char*)&next.m_departure_time, sizeof(Time));
			ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

			ioFile.seekp(cur_l_Pos, ios::beg);

			ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
			ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

			ioFile.write(cur.m_destination.data(), lenght_buf);

			ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
			ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

			f++;
			l--;
		}
	} while (f < l);

	for (int i = 0; i < last + 1; i++) {
		Pos.pop_back();
	}
	ioFile.close();

	if (first < l) quicksort_number_Bus(first, l);
	if (f < last) quicksort_number_Bus(f, last);
}

void File::quicksort_A_time(int first, int last) {
	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next, mid_elem, cur_f, cur_l;

	int f = first, l = last;
	int mid = (f + l) / 2;

	vector<int> Pos;
	ioFile.seekg(0, ios::beg);
	for (int i = 0; i < last + 1; i++) {
		Pos.push_back(ioFile.tellg());
		GetElementOfBinFile(cur);
	}

	for (int i = 0; i < mid; i++) {
		ioFile.seekg(Pos[i], ios::beg);
		GetElementOfBinFile(cur);
	}
	GetElementOfBinFile(mid_elem);

	do
	{
		do {
			ioFile.seekg(Pos[f], ios::beg);
			GetElementOfBinFile(cur_f);
			f++;
		} while (cur_f.m_arrival_time < mid_elem.m_arrival_time);

		do {
			ioFile.seekg(Pos[l], ios::beg);
			GetElementOfBinFile(cur_l);
			l--;
		} while (cur_l.m_arrival_time > mid_elem.m_arrival_time);

		--f; ++l;
		if (f <= l)
		{
			int cur_f_Pos = Pos[f];
			int cur_l_Pos = Pos[l];

			ioFile.seekg(cur_f_Pos, ios::beg);
			GetElementOfBinFile(cur);
			ioFile.seekg(cur_l_Pos, ios::beg);
			GetElementOfBinFile(next);

			ioFile.seekp(cur_f_Pos, ios::beg);

			ioFile.write((char*)&next.m_number_Bus, sizeof(int));
			ioFile.write((char*)&next.m_type_Bus, sizeof(int));

			ioFile.write(next.m_destination.data(), lenght_buf);

			ioFile.write((char*)&next.m_departure_time, sizeof(Time));
			ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

			ioFile.seekp(cur_l_Pos, ios::beg);

			ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
			ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

			ioFile.write(cur.m_destination.data(), lenght_buf);

			ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
			ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

			f++;
			l--;
		}
	} while (f < l);

	for (int i = 0; i < last + 1; i++) {
		Pos.pop_back();
	}
	ioFile.close();

	if (first < l) quicksort_number_Bus(first, l);
	if (f < last) quicksort_number_Bus(f, last);
}

void File::quicksort_destination(int first, int last) {
	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next, mid_elem, cur_f, cur_l;

	int f = first, l = last;
	int mid = (f + l) / 2;

	vector<int> Pos;
	ioFile.seekg(0, ios::beg);
	for (int i = 0; i < last + 1; i++) {
		Pos.push_back(ioFile.tellg());
		GetElementOfBinFile(cur);
	}

	for (int i = 0; i < mid; i++) {
		ioFile.seekg(Pos[i], ios::beg);
		GetElementOfBinFile(cur);
	}
	GetElementOfBinFile(mid_elem);

	do
	{
		do {
			ioFile.seekg(Pos[f], ios::beg);
			GetElementOfBinFile(cur_f);
			f++;
		} while (cur_f.m_destination < mid_elem.m_destination);

		do {
			ioFile.seekg(Pos[l], ios::beg);
			GetElementOfBinFile(cur_l);
			l--;
		} while (cur_l.m_destination > mid_elem.m_destination);

		--f; ++l;
		if (f <= l)
		{
			int cur_f_Pos = Pos[f];
			int cur_l_Pos = Pos[l];

			ioFile.seekg(cur_f_Pos, ios::beg);
			GetElementOfBinFile(cur);
			ioFile.seekg(cur_l_Pos, ios::beg);
			GetElementOfBinFile(next);

			ioFile.seekp(cur_f_Pos, ios::beg);

			ioFile.write((char*)&next.m_number_Bus, sizeof(int));
			ioFile.write((char*)&next.m_type_Bus, sizeof(int));

			ioFile.write(next.m_destination.data(), lenght_buf);

			ioFile.write((char*)&next.m_departure_time, sizeof(Time));
			ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

			ioFile.seekp(cur_l_Pos, ios::beg);

			ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
			ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

			ioFile.write(cur.m_destination.data(), lenght_buf);

			ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
			ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

			f++;
			l--;
		}
	} while (f < l);

	for (int i = 0; i < last + 1; i++) {
		Pos.pop_back();
	}
	ioFile.close();

	if (first < l) quicksort_number_Bus(first, l);
	if (f < last) quicksort_number_Bus(f, last);
}

void File::quicksort_type_Bus(int first, int last) {
	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next, mid_elem, cur_f, cur_l;

	int f = first, l = last;
	int mid = (f + l) / 2;

	vector<int> Pos;
	ioFile.seekg(0, ios::beg);
	for (int i = 0; i < last + 1; i++) {
		Pos.push_back(ioFile.tellg());
		GetElementOfBinFile(cur);
	}

	for (int i = 0; i < mid; i++) {
		ioFile.seekg(Pos[i], ios::beg);
		GetElementOfBinFile(cur);
	}
	GetElementOfBinFile(mid_elem);

	do
	{
		do {
			ioFile.seekg(Pos[f], ios::beg);
			GetElementOfBinFile(cur_f);
			f++;
		} while (cur_f.m_type_Bus < mid_elem.m_type_Bus);

		do {
			ioFile.seekg(Pos[l], ios::beg);
			GetElementOfBinFile(cur_l);
			l--;
		} while (cur_l.m_type_Bus > mid_elem.m_type_Bus);

		--f; ++l;
		if (f <= l)
		{
			int cur_f_Pos = Pos[f];
			int cur_l_Pos = Pos[l];

			ioFile.seekg(cur_f_Pos, ios::beg);
			GetElementOfBinFile(cur);
			ioFile.seekg(cur_l_Pos, ios::beg);
			GetElementOfBinFile(next);

			ioFile.seekp(cur_f_Pos, ios::beg);

			ioFile.write((char*)&next.m_number_Bus, sizeof(int));
			ioFile.write((char*)&next.m_type_Bus, sizeof(int));

			ioFile.write(next.m_destination.data(), lenght_buf);

			ioFile.write((char*)&next.m_departure_time, sizeof(Time));
			ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

			ioFile.seekp(cur_l_Pos, ios::beg);

			ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
			ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

			ioFile.write(cur.m_destination.data(), lenght_buf);

			ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
			ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

			f++;
			l--;
		}
	} while (f < l);

	for (int i = 0; i < last + 1; i++) {
		Pos.pop_back();
	}
	ioFile.close();

	if (first < l) quicksort_number_Bus(first, l);
	if (f < last) quicksort_number_Bus(f, last);
}


File::File(string filePath) {
	this->filePath = filePath;
	ioFile.open(filePath, ios::out | ios::trunc);
	ioFile.close();
}

void File::ReadTextFormat() {
	try {
		ioFile.open(filePath, ios::in);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	string data;
	while (getline(ioFile, data)) {
		cout << data << endl;
	}
	ioFile.close();
}

void File::WriteTextFormat(const Bus_flight& bus_flight) {
	try {
		ioFile.open(filePath, ios::out | ios::app);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	ioFile << bus_flight;
	ioFile.close();
}

void File::FindByName(string name) {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, std::ios::in | std::ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight temp;
	for (int i = 0; i < fileSize; i++) {
		GetElementOfBinFile(temp);
		if (strcmp(temp.m_destination.data(), name.data()) == 0) {
			cout << temp << endl;
			return;
		}
	}

	ioFile.close();
}

void File::DelByName(string name) {
	int fileSize = CountElementOfBinFile();

	try {
		ioFile.open(filePath, ios::in | ios::out | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight cur, next;
	int curPos, nextPos;

	for (int i = 0; i < fileSize; i++) {
		curPos = ioFile.tellg();
		GetElementOfBinFile(cur);

		if (strcmp(cur.m_destination.data(), name.data()) == 0) {
			ioFile.seekg(curPos, ios::beg);
			int size = 0;
			for (i; i < fileSize - 1; i++) {
				curPos = ioFile.tellg();
				GetElementOfBinFile(cur);
				nextPos = ioFile.tellg();
				GetElementOfBinFile(next);
				size = curPos - nextPos;

				ioFile.seekp(curPos, ios::beg);

				ioFile.write((char*)&next.m_number_Bus, sizeof(int));
				ioFile.write((char*)&next.m_type_Bus, sizeof(int));

				ioFile.write(next.m_destination.data(), lenght_buf);

				ioFile.write((char*)&next.m_departure_time, sizeof(Time));
				ioFile.write((char*)&next.m_arrival_time, sizeof(Time));

				nextPos = ioFile.tellp();

				ioFile.write((char*)&cur.m_number_Bus, sizeof(int));
				ioFile.write((char*)&cur.m_type_Bus, sizeof(int));

				ioFile.write(cur.m_destination.data(), lenght_buf);

				ioFile.write((char*)&cur.m_departure_time, sizeof(Time));
				ioFile.write((char*)&cur.m_arrival_time, sizeof(Time));

				ioFile.seekg(nextPos, ios::beg);
			}

			//chsize(_fileno(ioFile.), size);

			ioFile.close();
			return;
		}
	}

	ioFile.close();
}

void File::ReadBinFormat() {
	try {
		ioFile.open(filePath, ios::in | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	Bus_flight temp;

	ioFile.seekg(0, ios::end);
	int size = ioFile.tellg();

	ioFile.seekg(0, ios::beg);
	while (ioFile.tellg() < size) {
		GetElementOfBinFile(temp);
		std::cout << temp << std::endl;
	}

	ioFile.close();
}

void File::WriteBinFormat(const Bus_flight& bus_flight) {
	try {
		ioFile.open(filePath, ios::out | ios::app | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return;
	}

	ioFile.write((char*)&bus_flight.m_number_Bus, sizeof(int));
	ioFile.write((char*)&bus_flight.m_type_Bus, sizeof(int));

	ioFile.write(bus_flight.m_destination.data(), lenght_buf);

	ioFile.write((char*)&bus_flight.m_departure_time, sizeof(Time));
	ioFile.write((char*)&bus_flight.m_arrival_time, sizeof(Time));

	ioFile.close();
}

void File::GetElementOfBinFile(Bus_flight& temp) {
	int lenght;
	ioFile.read((char*)&temp.m_number_Bus, sizeof(int));
	ioFile.read((char*)&temp.m_type_Bus, sizeof(int));

	char* buf = new char[lenght_buf + 1];
	ioFile.read(buf, lenght_buf);
	buf[lenght_buf] = 0;
	temp.m_destination = buf;

	ioFile.read((char*)&temp.m_departure_time, sizeof(Time));
	ioFile.read((char*)&temp.m_arrival_time, sizeof(Time));

	delete[] buf;
}

int File::CountElementOfBinFile() {
	int size = 0;

	try {
		ioFile.open(filePath, ios::in | ios::binary);
		if (!ioFile.is_open()) {
			throw 4;
		}
	}
	catch (int index) {
		Exception ex(index);
		ex.what();
		return 0;
	}

	ioFile.seekg(0, ios::end);
	int fileSize = ioFile.tellg();
	ioFile.seekg(0, ios::beg);

	while (ioFile.tellg() < fileSize) {
		Bus_flight temp;
		int lenght;
		ioFile.read((char*)&temp.m_number_Bus, sizeof(int));
		ioFile.read((char*)&temp.m_type_Bus, sizeof(int));

		char* buf = new char[lenght_buf + 1];
		ioFile.read(buf, lenght_buf);
		buf[lenght_buf] = 0;
		temp.m_destination = buf;

		ioFile.read((char*)&temp.m_departure_time, sizeof(Time));
		ioFile.read((char*)&temp.m_arrival_time, sizeof(Time));

		delete[] buf;
		size++;
	}

	ioFile.close();
	return size;
}