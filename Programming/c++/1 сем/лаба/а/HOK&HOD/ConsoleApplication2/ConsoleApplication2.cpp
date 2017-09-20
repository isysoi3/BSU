// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main(){
	setlocale (LC_ALL, "Russian");
	cout << "Введите 2 числа" << endl;
	int a, b;
	cin >> a >> b;
	
	int a1 = a;
	int b1 = b;
	
	while (a != b)
	{
		if (a > b)
			a = a - b;
		else 
			b = b - a;
	}
	
	cout << "НОД(" << a1 << "," << b1 << ")=" << a << endl;
	cout << "НОК(" << a1 << "," << b1 << ")=" << a1 * (b1 / a) << endl;
	
	
	return 0;

}
