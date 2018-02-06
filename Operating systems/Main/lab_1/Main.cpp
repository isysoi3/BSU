// lab_1.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

struct student
{
	char name[10]; // имя студента
	int num; // номер группы
	double grade; // средний балл
};

void readBinaryFile(string name) {
	fstream binin(name, ios::in | ios::binary);
		student s;
	while (binin.read((char*)&s, sizeof(struct student))) {
		cout << "Name: " << s.name << "\n";
		cout << "Group number: " << s.num << "\n";
		cout << "Grade: " << s.grade << "\n";
		cout << endl;
	}
	binin.close();
}

void CreatorStart(string fileName, string n) {
	char appName[] = "Creator.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	auto arguments = fileName + " " + n;//"demo.bin 4";

	LPSTR s = const_cast<char *>(arguments.c_str());

	CreateProcess(appName, s, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);


	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
}

void printD(string name) {
	ifstream fin(name);
	string str;
	while (getline(fin,str)) {
		cout << str  << "\n";
	}
	fin.close();
}

void ReportetStart(string otchetFileName, string binaryFileName, string averagePoint) {
	char appName[] = "Reporter.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	auto arguments = binaryFileName + " " + otchetFileName + " " + averagePoint;//"demo.bin 4";

	LPSTR s = const_cast<char *>(arguments.c_str());

	CreateProcess(appName, s, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);


	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
}

int main()
{
	setlocale(LC_ALL, "RUS");

	string binaryFileName, numberOfStudents;
	
	cout << "Enter bianry file name: ";
	cin >> binaryFileName;
	cout << "Enter number of students: ";
	cin >> numberOfStudents;
	
	CreatorStart(binaryFileName, numberOfStudents);
	readBinaryFile(binaryFileName);

	string oychetFileName, avaragePoint;
	cout << "Enter otchet file name: ";
	cin >> oychetFileName;
	cout << "Enter average point of students: ";
	cin >> avaragePoint;

	ReportetStart(oychetFileName, binaryFileName, avaragePoint);
	printD(oychetFileName);


	system("pause");
    return 0;
}

