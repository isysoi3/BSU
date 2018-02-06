// Creator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>

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
		system("pause");
		return 0;
	}
	fstream binout(argv[0], ios::out | ios:: binary);
	int n = atoi(argv[1]);

	for (int i = 0; i < n; i++) {
		student s;
		cout << "Enter name>";
		cin >> s.name;
		cout << "Enter group number>";
		cin >> s.num;
		cout << "Enter grade>";
		cin >> s.grade;
		cout << endl;
		binout.write((char*)&s, sizeof(student));
	}
	binout.close();


	system("pause");
    return 0;
}

