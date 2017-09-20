#include <iostream>
#include <conio.h>
#include "Stack.h"

using namespace std;

char information() {
	char tmp;
	cout << "[1] push\n";
	cout << "[2] pop\n";
	cout << "[3] top\n";
	cout << "[4] Is stack empty?\n";
	cout << "[5] size\n";
	cout << "[0] exit\n";
	tmp = _getch();
	return tmp;
}


int main() {
	char n;

	do {
		cout << "Enter 1, if you want use stack on array\n";
		cout << "Enter 2, if you want use stack on list\n";
		n = _getch();
		system("cls");
	} while (n != '1' && n != '2');

	switch (n) {
	case '1': {
		int size = 0;
		cout << "Enter size of stack ";
		cin >> size;
		try {
			StackArray<int> first(size);
			while (true) {
				n = information();
				if (n != '0') {
					switch (n) {
					case '1': {
						int ter = 0;
						cout << "Enter number ";
						cin >> ter;
						first.push(ter);
						break;
					}
					case '2': {
						first.pop();
						break;
					}
					case '3': {
						cout << "top : " << first.top() << " " << endl;
						break;
					}
					case '4': {
						if (first.isEmpty())
							cout << "stack is empty" << endl;
						else
							cout << "stack is not empty" << endl;
						break;
					}
					case '5': {
						cout << "size : " << first.size() << endl;
						break;
					}
					default:
						cout << "Incorrect input" << endl;
						break;
					}
					system("pause");
					system("cls");
				}
				else
					break;
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		break;
	}
	case '2': {
		StackList<int> list;
		try {
			while (true) {
				n = information();
				if (n != '0') {
					switch (n) {
					case '1': {
						int ter = 0;
						cout << "Enter number ";
						cin >> ter;
						list.push(ter);
						break;
					}
					case '2': {
						list.pop();
						break;
					}
					case '3': {
						cout << "top : " << list.top() << " " << endl;
						break;
					}
					case '4': {
						if (list.isEmpty())
							cout << "stack is empty" << endl;
						else
							cout << "stack is not empty" << endl;
						break;
					}
					case '5': {
						cout << "size : " << list.size() << endl;
						break;
					}
					default:
						cout << "Incorrect input" << endl;
						break;
					}
					system("pause");
					system("cls");
				}
				else
					break;
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		break;
	}
	}

	return 0;
}