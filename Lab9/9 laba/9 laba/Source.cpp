#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <functional>
#include <set>

using namespace std;
namespace ooo {
    class Death_Stranding;

    class Algoritms {
    public:
        void Algoritm1();
        std::list<Death_Stranding>::iterator Algoritm2(std::list<Death_Stranding>::iterator begin_1, std::list<Death_Stranding>::iterator end_1,
            std::list<Death_Stranding>::iterator begin_2, std::list<Death_Stranding>::iterator end_2);
        void Algoritm3(std::list<Death_Stranding>::iterator begin_1, std::list<Death_Stranding>::iterator end_1,
            std::list<Death_Stranding>::iterator begin_2, std::list<Death_Stranding>::iterator end_2);
        void Print(std::list<Death_Stranding>::iterator begin, std::list<Death_Stranding>::iterator end);

    };

    class Death_Stranding {
    public:
        Death_Stranding(int id = 0, int time = 0, int level = 0) :
            m_id(id), m_time(time), m_level(level) {}

        friend Algoritms;

        friend std::ostream& operator<< (std::ostream& out, const Death_Stranding& Death_Stranding) {
            out << "Id: " << Death_Stranding.m_id << std::endl;
            out << "Time: " << Death_Stranding.m_time << std::endl;
            out << "Level: " << Death_Stranding.m_level << std::endl;
            return out;
        }

    private:
        int m_id;
        int m_time;
        int m_level;
    };

    class Exception {
    public:
        Exception() {
            this->errorIndex = 0;
        }
        Exception(int errorIndex) {
            this->errorIndex = errorIndex;
        }
        void what() {
            if (errorIndex == 0) {
                std::cout << "Input error! Enter int!" << std::endl;
            }
            else if (errorIndex == 1) {
                std::cout << "!" << std::endl;
            }
            else if (errorIndex == 2) {
                std::cout << "Stack is empty!" << std::endl;
            }
            else {
                std::cout << "EXCEPTION" << std::endl;
            }
        }

    private:
        int errorIndex;
    };
}

int main() {
    ooo::Algoritms alg;
    std::list<ooo::Death_Stranding> test;
    std::list<ooo::Death_Stranding> test_new;

    test.push_back(ooo::Death_Stranding(15, 15, 11));
    test.push_back(ooo::Death_Stranding(15, 15, 11));
    test.push_back(ooo::Death_Stranding(15, 15, 10));
    test_new.push_back(ooo::Death_Stranding(15, 15, 11));
    test_new.push_back(ooo::Death_Stranding(15, 15, 11));
    test_new.push_back(ooo::Death_Stranding(15, 15, 10));

    std::cout << "Algoritm 1\n" << endl;
    alg.Algoritm1();
    std::cout << std::endl;

    std::cout << "Primary set\n" <<endl;
    alg.Print(test.begin(), test.end());


    std::cout << "Algoritm 2\n" << "------------------------------------\n";
    auto it = alg.Algoritm2(test.begin(), test.end(), test_new.begin(), test_new.end());
    if (it == test.end()) {
        std::cout << "Elements identical" << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Primary set\n" << "------------------------------------\n";

    alg.Print(test.begin(), test.end());
    alg.Print(test_new.begin(), test_new.end());

    std::cout << "Algoritm 3\n" << "------------------------------------\n";

    alg.Algoritm3(test.begin(), test.end(), test_new.begin(), test_new.end());

    alg.Print(test.begin(), test.end());
    alg.Print(test_new.begin(), test_new.end());

    return 0;
}


void ooo::Algoritms::Print(std::list<Death_Stranding>::iterator begin,
    std::list<Death_Stranding>::iterator end) {
    auto it = begin;
    while (it != end) {
        std::cout << *it << std::endl;
        ++it;
    }
    std::cout << std::endl;
}

void ooo::Algoritms::Algoritm3(std::list<Death_Stranding>::iterator begin_1, std::list<Death_Stranding>::iterator end_1,
    std::list<Death_Stranding>::iterator begin_2, std::list<Death_Stranding>::iterator end_2) {
    auto it_1 = begin_1;
    auto it_2 = begin_2;
    while (it_1 != end_1 && it_2 != end_2) {
        if ((it_1->m_id == it_2->m_id) && (it_1->m_level == it_2->m_level) && (it_1->m_time == it_2->m_time)) {
            it_1->m_id = it_2->m_id = 1;
            it_1->m_time = it_2->m_time = 2;
            it_1->m_level = it_2->m_level = 3;
        }
        ++it_1;
        ++it_2;
    }
}

std::list<ooo::Death_Stranding>::iterator ooo::Algoritms::Algoritm2(std::list<Death_Stranding>::iterator begin_1, std::list<Death_Stranding>::iterator end_1,
    std::list<Death_Stranding>::iterator begin_2, std::list<Death_Stranding>::iterator end_2) {
    auto it_1 = begin_1;
    auto it_2 = begin_2;
    while (it_1 != end_1 && it_2 != end_2) {
        if (it_1->m_id != it_2->m_id || it_1->m_level != it_2->m_level || it_1->m_time != it_2->m_time) {
            return it_1;
        }
        ++it_1;
        ++it_2;
    }
    return it_1;
}

void ooo::Algoritms::Algoritm1() {
    std::cout << "Checking given symbol" << std::endl;
    std::fstream outFile;
    outFile.open("string.txt");

    try {
        if (!outFile.is_open()) {
            throw 1;
        }
        std::cout << "File is opened" << std::endl;
    }
    catch (int index) {
        Exception ex(index);
        ex.what();
        return;
    }

    std::string buffer;
    std::list<std::string> strList;
    int i = 0, amount_received_symbol = 0;
    char received_symbol; char* mass = new char[10];
    std::cout << "Print symbol: ";
    std::cin >> received_symbol;

    while (!outFile.eof()) {
        std::getline(outFile, buffer);
        std::cout << buffer << std::endl;
        while (i < buffer.length()) {
            if (buffer[i] == received_symbol) {
                amount_received_symbol++;
            }
            i++;
        }
        _itoa_s(amount_received_symbol, mass, 10, 10);
        strList.push_back(buffer + " amount of amount_received_symbol: " + mass);
        amount_received_symbol = 0; i = 0;
    }

    std::cout << "Algoritm is ended" << std::endl;
    outFile.close();
    std::cout << "Data file is closed" << std::endl;

    std::ofstream inFile("string2.txt");

    try {
        if (!inFile.is_open()) {
            throw 1;
        }
        std::cout << "Result file is opened" << std::endl << std::endl;
    }
    catch (int index) {
        Exception ex(index);
        ex.what();
        return;
    }

    std::list<std::string>::const_iterator it = strList.begin();
    while (it != strList.end()) {
        inFile << *it << "\n";
        std::cout << *it << std::endl;
        ++it;
    }
    std::cout << std::endl << "Data was writen" << std::endl;
    inFile.close();
    std::cout << "Result file is closed" << std::endl;
}