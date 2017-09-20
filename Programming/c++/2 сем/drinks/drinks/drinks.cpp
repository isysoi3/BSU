// drinks.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <conio.h>
#include "Drink.h"
#include "Soft_Drink.h"
#include "Tipple.h"

using namespace std;

char option() {
	char ch;
	cout << "[1] Beer\n";
	cout << "[2] Cognac\n";
	cout << "[3] Wine\n";
	cout << "[4] Lemonade\n";
	cout << "[5] Milk\n";
	cout << "[6] MineralWater\n";
	cout << "[0] exit\n";
	while ((ch = _getch()) != '1' && ch != '2' && ch != '3'
		&& ch != '4' && ch != '5' && ch != '6' && ch != '0');
	system("cls");
	return ch;
}

int main() {
	setlocale(LC_ALL, "Russian");
	char numb;
	int enumChoice;
	double volume, abv;
	string drinkName;

	Milk *tmpMilk = nullptr;
	Lemonade *tmpLem = nullptr;
	Mineral_Water *tmpMW = nullptr;
	Beer *tmpBeer = nullptr;
	Cognac *tmpCognac = nullptr;
	Wine *tmpWine = nullptr;
//Drink dr;

	while (true) {

		numb = option();

		if (numb != '0') {
			cout << "Введите название : ";
			getline(cin, drinkName);
			cout << "Введите объём : ";
			cin >> volume;
			if (numb == '1' || numb == '2' || numb == '3') {
				cout << "Введите процент алкоголя : ";
				cin >> abv;
			}
			switch (numb) {
			case '1': {
				cleaning bb;
				cout << "Тип(1.filtered, 2.unfiltered) : ";
				cin >> enumChoice;
				system("cls");
				if (enumChoice == 1)
					bb = filtered;
				else {
					if (enumChoice == 2)
						bb = unfiltered;
					else {
						cout << "Неправильный выбор\n";
						break;
					}
				}
				try {
					tmpBeer = new Beer(drinkName, volume, abv, bb);
					cout << "Beer\n";
					cout << "Название : " << tmpBeer->getName() << endl;
					cout << "Объем : " << tmpBeer->getVolume() << " л" << endl;
					cout << "Процент алкоголя : " << tmpBeer->getSturdiness() << " %" << endl;
					cout << "Тип : " << tmpBeer->getFilt() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;
			}
			case '2': {
				int i;
				cout << "Введите возраст : ";
				cin >> i;
				system("cls");
				try {
					tmpCognac = new Cognac(drinkName, volume, abv, i);
					cout << "Cognac\n";
					cout << "Название : " << tmpCognac->getName() << endl;
					cout << "Объем : " << tmpCognac->getVolume() << " л" << endl;
					cout << "Процент алкоголя : " << tmpCognac->getSturdiness() << " %" << endl;
					cout << "Выдержка : " << tmpCognac->getExcert() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;
			}
			case '3': {
				Color typeW;
				cout << "Введите тип(1.red, 2.white): ";
				cin >> enumChoice;
				system("cls");
				if (enumChoice == 1)
					typeW = red;
				else {
					if (enumChoice == 2)
						typeW = white;
					else {
						cout << "Неправильный выбор\n";
						break;
					}
				}
				try {
					tmpWine = new Wine(drinkName, volume, abv, typeW);
					cout << "Wine\n";
					cout << "Название : " << tmpWine->getName() << endl;
					cout << "Объем : " << tmpWine->getVolume() << " л" << endl;
					cout << "Процент алкоголя : " << tmpWine->getSturdiness() << " %" << endl;
					cout << "Цвет : " << tmpWine->getColor() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;

			}
			case '4': {
				Additive ad;
				cout << "Введите добавку(1.apple, 2.pear, 3.orange): ";
				cin >> enumChoice;
				system("cls");
				if (enumChoice == 1)
					ad = apple;
				else {
					if (enumChoice == 2)
						ad = pear;
					else
						if (enumChoice == 3)
							ad = orange;
						else {
							cout << "Неправильный выбор\n";
							break;
						}
				}
				try {
					tmpLem = new Lemonade(drinkName, volume, ad);
					cout << "Lemonade\n";
					cout << "Название : " << tmpLem->getName() << endl;
					cout << "Объем : " << tmpLem->getVolume() << " л" << endl;
					cout << "Добавка : " << tmpLem->getAdd() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;
			}
			case '5': {
				int fat;
				cout << "Введите процент жира: ";
				cin >> fat;
				system("cls");
				try {
					tmpMilk = new Milk(drinkName, volume, fat);
					cout << "Milk\n";
					cout << "Название : " << tmpMilk->getName() << endl;
					cout << "Объем : " << tmpMilk->getVolume() << " л" << endl;
					cout << "Жирность : " << tmpMilk->getFatness() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;
			}
			case '6': {
				TheNumberOfGas gs;
				cout << "Введите газированность(1.strong, 2.middling, 3.without): ";
				cin >> enumChoice;
				system("cls");
				if (enumChoice == 1)
					gs = strong;
				else {
					if (enumChoice == 2)
						gs = middling;
					else
						if (enumChoice == 3)
							gs = without;
						else {
							cout << "Неправильный выбор\n";
							break;
						}
				}
				try {
					tmpMW = new Mineral_Water(drinkName, volume, gs);
					cout << "MineralWater\n";
					cout << "Название : " << tmpMW->getName() << endl;
					cout << "Объем : " << tmpMW->getVolume() << " л" << endl;
					cout << "Газированность : " << tmpMW->getGas() << endl << endl;
				}
				catch (const exception& e) {
					cout << e.what() << endl;
				}
				break;
			}
			}
			system("pause");
			system("cls");
			cin.ignore();
		}
		else
			break;
	}
	delete tmpMilk;
	delete tmpLem;
	delete tmpMW;
	delete tmpBeer;
	delete tmpCognac;
	delete tmpWine;
	return 0;
}
