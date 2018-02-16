// pets.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <iterator>
#include <Windows.h>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>

using namespace std;

struct petInfo {
	string kindOfAnimal;
	string nickname;
	unsigned int age;
};

char option() {
	char ch;
	cout << "[1] Подсчет количества различных видов животных у каждого владельца\n";
	cout << "[2] Вывод информации для конкретного вида животного\n";
	cout << "[3] Количество видов животных с определённой кличкой\n";
	cout << "[4] Данные о возрасте самого старого и самого молодого животного каждого вида\n";
	cout << "[0] Выход" << endl;
	while ((ch = _getch()) != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '0');
	system("cls");
	return ch;
}

int countKind(vector<petInfo> inf) {
	set<string> kinds;
	for (auto it = inf.begin(); it != inf.end(); ++it) {
		kinds.insert(it->kindOfAnimal);
	}
	return kinds.size();
}

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream fin("input.txt");
	string owner, kind, nickname, inputStr;
	char numb;
	unsigned age;
	unordered_map<string, vector<petInfo>> info;

	while (getline(fin, owner, ',')) {
		getline(fin, kind, ',');
		getline(fin, nickname, ',');
		fin >> age;
		petInfo pe;
		pe.kindOfAnimal = kind;
		pe.nickname = nickname;
		pe.age = age;
		auto iter = info.find(owner);
		if (iter != info.end())
			iter->second.push_back(pe);
		else {
			info[owner].push_back(pe);
		}
		fin.ignore();																              
	}

	fin.close();

	while (true) {
		numb = option();
		if (numb != '0') {
			switch (numb) {
			case '1': {
				for (auto it = info.begin(); it != info.end(); ++it) {
					cout << it->first << " : " << countKind(it->second) << " - количество различных видов животных" << endl;
				}
				break;
			}
			case '2': {
				cout << "Введите вид животного : ";
				getline(cin, inputStr);
				system("cls");
				set<pair<string, string>> ownerNick;
				for (auto it = info.begin(); it != info.end(); ++it) {
					for (int i = 0; i < it->second.size(); i++) {
						if (it->second[i].kindOfAnimal == inputStr) {
							ownerNick.insert(make_pair(it->first, it->second[i].nickname));
						}
					}
				}
				cout << "Вид животного : " << inputStr << endl;
				if (!ownerNick.empty()) {
					for (auto it = ownerNick.begin(); it != ownerNick.end(); ++it)
						cout << "Владелец: " << it->first << ", " << "кличка: " << it->second << endl;
				}
				else
					cout << "Такой вид во входных данных не найден" << endl;
				break;
			}
			case '3': {
				cout << "Введите кличку животного : ";
				getline(cin, inputStr);
				unordered_set<string> kinds;
				for (auto it = info.begin(); it != info.end(); ++it) {
					for (int i = 0; i < it->second.size(); i++) {
						if (it->second[i].nickname == inputStr)
							kinds.insert(it->second[i].kindOfAnimal);
					}
				}
				if (!kinds.empty())
					cout << "Видов животных с кличкой " << inputStr << " : " << kinds.size() << endl;
				else
					cout << "Такая кличка во входных данных не найдена" << endl;
				break;
			}
			case '4': {
				unordered_map<string,set<int>> kindAge;
				for (auto it = info.begin(); it != info.end(); ++it) {
					for (int i = 0; i < it->second.size(); i++) {
						kindAge[it->second[i].kindOfAnimal].insert(it->second[i].age);
					}
				}
				for (auto it = kindAge.begin(); it != kindAge.end(); ++it) {
					if (*it->second.rbegin() != *it->second.begin())
						cout << it->first << " : возраст самого старого " << *it->second.rbegin()
						<< ", возраст самого молодого " << *it->second.begin() << endl;
					else
						cout << it->first << " : возраст самого старого и самого молодого совподает и равен "
						<< *it->second.begin() << endl;
				}
				break;
			}
			}
			system("pause");
			system("cls");
		}
		else
			break;
	}
	return 0;
}