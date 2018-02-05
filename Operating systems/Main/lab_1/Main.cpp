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

void CreatorStart() {
	char appName[] = "Creator.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	char p1[] = "demo.bin 4";
	CreateProcess(appName, p1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);


	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
}

void printD(string name) {
	ifstream fin(name);
	string str;
	cout << "Otchet:\n";
	while (getline(fin,str)) {
		cout << str  << "\n";
	}
	fin.close();
}

void ReportetStart() {
	char appName[] = "Reporter.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piApp;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	char p1[] = "demo.bin out.txt 100";
	CreateProcess(appName, p1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp);


	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
}

int main()
{
	string binaryFileName, numberOfStudents;
	
	cout << "Enter bianry file name: ";
	cin >> binaryFileName;
	cout << "Enter number of students: ";
	cin >> numberOfStudents;

	//appName += binaryFileName + " " + numberOfStudents;

	
	//CreatorStart();
	readBinaryFile("demo.bin");


	ReportetStart();
	printD("out.txt");


	system("pause");
    return 0;
}

