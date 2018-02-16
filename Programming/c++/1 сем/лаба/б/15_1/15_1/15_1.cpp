// 15_1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale ( LC_ALL, "RUS" );
	
	int a[10];
	int n, c, k;
	k = 0;
	
	cout << "Введите число" << endl;
	cin >> n;
	
	while (n != 0)
    {
		c = n % 10;
		a[c] = 1;
		n = n / 10;
    }
	
	for ( int i = 0 ; i <= 9 ; i++ )
	{ 
		if ( a[i] == 1 ) 
			k++;
	}
	
	cout << "Количество различных цифр у заданного числа = " << k << endl;
	
	
	return 0;
}