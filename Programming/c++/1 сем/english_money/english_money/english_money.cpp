// english_money.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include "money.h"

using namespace std;

void input(long int *pound, int *shilling, double *pence) {
	long int a;
	int b;
	double c;
	cout << "Enter pounds ";	 
	cin >> a ;
	*pound = a;
	cout << "Enter shilings ";
	cin >> b;
	*shilling = b;
	cout << "Enter pences ";
	cin >> c;
	*pence = c;
	cout << endl;
}

int main() {
	long int pound = 0;
	int shilling = 0;
	double pence = 0;
	int check = 0;

	input(&pound, &shilling, &pence);

	Money *a = nullptr;
	Money *b = nullptr;

	try {
		a = new Money(pound, shilling, pence);
		check++;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	input(&pound, &shilling, &pence);
	try {
		b = new Money(pound, shilling, pence);
		check++;
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	if (check == 2) {
		Money *rez;
		rez = new Money;
		try {
			if (*a == *b)
				cout << "equal";
			else if (*a < *b)
				cout << "the second is more then the first";
			else
				cout << "the first is more then the second";
			cout << endl;
			
			*rez = *a + *b;
			cout << "a + b : ";
			rez->getMoney();
			*rez = *b - *a;
			cout << "b - a : ";
			rez->getMoney();
			*a += *a;
			cout << "a += a : ";
			a->getMoney();
			*a -= *a;
			cout << "a -= a : ";
			a->getMoney();
			*b = -(*b);
			cout << "b = -b : ";
			b->getMoney();

			
		}
		catch (const exception& e) {
			cout << e.what() << endl;
		}
		delete rez;
	}
	delete a;
	delete b;
	return 0;
}
