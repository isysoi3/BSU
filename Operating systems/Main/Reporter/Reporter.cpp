// Reporter.cpp : Defines the entry point for the console application.
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

	if (argc < 3) {
		cout << "arguments error\n";
		system("pause");
		return 1;
	}

	fstream fbin(argv[0], ios::in | ios:: binary);
	ofstream fout(argv[1]);
	float averageScore = atof(argv[2]);

	fout << "Отчет по файлу " << argv[0] << "\n";
	fout << "Список студентов со средним балом выше " << argv[2] << "\n";
	student s;
	while (fbin.read((char*)&s, sizeof(struct student))) {
		if (averageScore < s.grade) {
			fout << "Name: " << s.name << "\n";
			fout << "Group number: " << s.num << "\n";
			fout << "Grade: " << s.grade << "\n";
			fout << endl;
		}
	}

	fout.close();
	fbin.close();
	system("pause");
    return 0;
}

