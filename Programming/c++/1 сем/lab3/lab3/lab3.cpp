// lab3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <cmath> 
#include <ctime>

using namespace std;

long double sh(long double x, long double toch) {
	
	long  double rez = x;
	long double x1 = x;
	long double n = 1;
	int m1 = 1;
	
	while (fabs (x1 / n) > toch) {
		x1 *= x*x;
		n *= (m1 + 1)*(m1 + 2);
		rez +=  x1 / n;
		m1 += 2;
	} 

	return rez;
}
int main() {
	setlocale ( LC_ALL, "RUS" );
	long double x, toch ;
	cout << "Введите точность" << endl;
	cin >> toch;
	srand( time ( 0 ) );
	x = (double) (rand () % 500 - 250) / (rand () % 100 - 50) ;
	cout << "x = " << x << endl;
	cout << "Вычисления = "  << sh(x, toch)  << endl;
	cout << "Значение стандартной функции = " << sinh(x) << endl;
	
	return 0;
}