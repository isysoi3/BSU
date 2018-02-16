// Creator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct student
{
	char name[10]; // имя студента
	int num; // номер группы
	double grade; // средний балл
};


int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "arguments error\n";
		system("pause");
		return 1;
	}
	fstream fbin(argv[0], ios::out | ios:: binary);
	int numberOfStudents = atoi(argv[1]);

	for (int i = 0; i < numberOfStudents; i++) {
		student s;
		cout << "Enter name> ";
		cin.getline(s.name, 10);
		cout <<"Enter group number> ";
		cin >> s.num;
		cout << "Enter grade> ";
		cin >> s.grade;
		fbin.write((char*)&s, sizeof(student));
		cout << endl;
		cin.ignore();
	}

	fbin.close();
	system("pause");
    return 0;
}

