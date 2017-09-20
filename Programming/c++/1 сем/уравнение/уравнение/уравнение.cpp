// уравнение.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>

using namespace std;

int main() {
	setlocale ( LC_ALL, "RUS" );

	double a, b , c;
	cout << "Ведите коэфицент a ";
	cin >> a;
	cout << "Ведите коэфицент b ";
	cin >> b;
	cout << "Ведите коэфицент c ";
	cin >>c;
	
	if (( a == 0) && (c != 0) && (b != 0) )
		cout << "Корень = " << -c / b << endl;
	else {
		if ((a == 0) && (b == 0) && (c == 0))
			cout << "x принадлежит действительным числам" << endl;
		else {
			if (c == 0)
					cout << "Два корня. Первый = 0. Второй = " << -b / a <<endl;
			else {
				if ( b == 0) {
					if ( c > 0)
						cout << "Корней	нет" << endl;
					else
						cout << "Два корня. Первый = "<< sqrt(-c / a) << " Второй = " << -sqrt(-c / a) << endl;
				}
				else {
					double d = b * b - 4 * a * c;
					if (d >= 0 ) {
						if (d == 0)
							cout << "Один корень уравнения = " << -b/(2*a) <<endl;
						else
							cout << "Два корня уравнения. Первый = " << (-b + sqrt(d) ) / ( 2 * a ) << " Второй корень = " << (-b - sqrt(d) ) / ( 2 * a ) <<endl;
						}
					else 
						cout << "Корней	нет" << endl;
				}
			}
		}
	}
	return 0;
}