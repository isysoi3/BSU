// lab7.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>
#include <Windows.h>
#include "Dictionary.h"
#include <conio.h>
#include <map>
#include <string>
using namespace std;

string en_input() {
	string str;
	cout << "¬ведите английское слово ";
	getline(cin, str);
	return str;
}

string rus_input() {
	string str;
	cout << "¬ведите русское слово ";
	getline(cin, str);
	return str;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Dictionary my, mu1, rez;
	mu1.insertWord("hot", "гор€чий");
	char  numb;
	string en, rus;
	while (true) {
		cout << "[1] дл€ добавлени€ слова в словарь\n";
		cout << "[2] дл€ ввода через поток\n";
		cout << "[3] дл€ объединение словорей\n";
		cout << "[4] вывод словор€\n";
		cout << "[5] удаление слова из словар€\n";
		cout << "[6] дл€ изменени€ перевода\n";
		cout << "[7] присваивание \n";
		cout << "[8] размер словар€\n";
		cout << "[9] просмотр перевода\n";
		cout << "[0] exit\n";
		numb = _getch();
		system("cls");
		if (numb != '0') {
			switch (numb) {
			case '1': {
				en = en_input();
				rus = rus_input();
				my.insertWord(en, rus);
				break;
			}
			case '2': {
				cin >> my;
				break;
			}
			case '3': {
				my = my + mu1;
				break;
			}
			case '4': {
				cout << my;
				break;
			}
			case '5': {
				en = en_input();
				my.deleteWord(en);
				break;
			}
			case '6': {
				en = en_input();
				rus = rus_input();
				my.setWord(en, rus);
				break;
			}
			case '7': {
				my = mu1;
				break;
			}
			case '8': {
				cout << my.getSize() << endl;
				break;
			}
			case '9': {
				en = en_input();
				cout << my.getWord(en) << endl;
				break;
			}
			default: {
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

