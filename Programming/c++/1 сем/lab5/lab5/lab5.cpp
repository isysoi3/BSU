// lab5.cpp: определяет точку входа для консольного приложения.
//

#include <iostream> 
#include <cmath> 

using namespace std; 

double f1(double x) { 
	return ((x) * sqrt( 1 + x)); 
} 
double f2(double x) { 
	return ((asin(sqrt(x))) / sqrt(x * (1 - x))); 
} 
double f3(double x) { 
	return (pow(2,x) / (1 - 4 * x)) ; 
} 
double integral (double (*f)(double), double touch,double a, double b, int &raz){ 
	double  h, x, rez1 = 0, rez2 = 0 ; 
	raz = 10; 
	 
	do { 
		x = a;
		h = (fabs((b) - (a)))/raz;
		rez1 = rez2;
		rez2 = 0;
		while(x < b) { 
			rez2 += 0.5*(f(x) + f(x + h)) * h; 
			x = x + h; 
			} 
		raz = raz << 1;
	} while(fabs(rez2 - rez1) > touch);

	return rez1 ; 
} 
int main() { 
	setlocale(LC_ALL,"RUS"); 
	double touch; 
	
	cout << "Введите точность "; 
	cin >> touch; 
	int raz;

	cout << "Вычисления первого интеграла: " << integral(&f1, touch, 2, 7, raz) << "\n";
	cout << "Количество разбиений = " << (raz >> 1) << "\n\n"; 
	cout << "Вычисления второго интеграла: " << integral(&f2, touch, 0.2, 0.3, raz) << "\n"; 
	cout << "Количество разбиений = " << (raz >> 1) << "\n\n"; 
	cout << "Вычисления третьего интеграла: " << integral(&f3, touch, -13, -2, raz) << "\n"; 
	cout << "Количество разбиений = " << (raz >> 1) << "\n\n"; 
	
	return 0; 
}