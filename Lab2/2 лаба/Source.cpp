#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
using namespace std;

class cdeath_stranding {
	friend class cgamer;
private:
	static int id;
	int idcl=0;
	int level;
	float time;
public:
	cdeath_stranding() {
		level = 1;
		time = 0;
		idcl = id;

	}
	cdeath_stranding(int a) {
		level = a;
		idcl = id;
	}
	int getlevel() {
		return level;
	}
	void setlevel(int level) {
		this->level = level;
		id++;
		idcl = id;
	}
	
	friend int getpart(cdeath_stranding& object);
	friend void zeroing(cdeath_stranding& object);
	~cdeath_stranding() {
		cout << "~cdeath_stranding" << endl;
	}

};
int cdeath_stranding::id;
class cgamer {

public:
	void set_time(cdeath_stranding& object);
	void showpart(cdeath_stranding& object);
};
void showpart(cdeath_stranding& object);
int getpart(cdeath_stranding& object);
int main() {
	int choice;
	int number;
	cdeath_stranding object1, object2;
	cgamer gamer;
	object1.setlevel(getpart(object1));
	gamer.showpart(object1);
	object2.setlevel(getpart(object2));
	gamer.showpart(object2);
	cdeath_stranding object[3];
	for (int i = 0; i < 3; i++) {
		object[i].setlevel(getpart(object[i]));
		gamer.showpart(object[i]);
	}	
	gamer.set_time(object1);
	gamer.set_time(object2);
	for (int i = 0; i < 3; i++) {
		gamer.set_time(object[i]);
	}
	gamer.showpart(object1);
	gamer.showpart(object2);
	for (int i = 0; i < 3; i++) {
		gamer.showpart(object[i]);
	}

}
int getpart(cdeath_stranding& object) {
	int a, i = 0;
	do {
		cout << "input your level" << endl;
		cin >> a;
	} while (a < 0);
	cdeath_stranding objecttwo(a);
	return objecttwo.getlevel();
}
void cgamer::showpart(cdeath_stranding& object) {
	cout << endl;
	cout << setw(5) << "  ID:  " << setw(5) << object.idcl
		<< setw(5) << "  Time:  " << setw(5) << object.time
		<< setw(5) << "  Level:  " << setw(5) << object.level << endl;
}
void cgamer::set_time(cdeath_stranding &object) {
	double time = 0;
	do {
		cout << "input time "<<endl;
		cin >> object.time;
	} while (object.time < 0);
}

void zeroing(cdeath_stranding& object)
{
	object.id = 0;
}