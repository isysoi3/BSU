// 1.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>

using namespace std;

int main(){
	setlocale (LC_ALL,"RUS");
	cout << "¬ведите число " << endl;
	int a, i;
	i = 2;
	cin >> a;
	cout <<a<<"=";
	while (i<=a)
	{
		if(a % i == 0)
		{
			cout << i;
			a = a / i;
			if (a>1)
				cout <<"*";
		}
		else 
			i++;
	}
	cout <<endl;
	return 0;
}