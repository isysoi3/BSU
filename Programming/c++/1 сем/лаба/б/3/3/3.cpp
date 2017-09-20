// 3.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale ( LC_ALL, "RUS" );
	cout << "¬ведите 2 числа (второе должно быть больше первого) " << endl;
	
	int a, b, d, r;
	
	cin >> a >> b;
	cout << "ѕростые числа: ";
	
	for ( a ; a <= b ; a++ ){
		d = 2;
		do
		{
			r = a % d;
			if (r != 0)
				d++;
		} while (r != 0);
		if (a == d)
			cout << a << " ";
	}
	
	cout << endl;
	
	return 0;
}