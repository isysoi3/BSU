// lab4_A.cpp: определяет точку входа для консольного приложения.
//


#include <iostream>
#include <cstdlib>

using namespace std;

void myAtoi (char *str) {
	int  n = 0;
	if (str[0] == '-'){
		for (int i = 1; str[i] >= '0' && str[i] <= '9'; i++)
			n = 10 * n + (str[i] - '0');
		n = -n;
	}
    else 
		for (int i = 0; str[i] >= '0' && str[i] <= '9'; i++)
			n = 10 * n + (str[i] - '0');
    cout << "The result of my function is " << n <<endl;

}
int main() {
	char str [50];
	cout << "Enter a number " << endl;
	cin >> str;
	char *p;
	p = str;
	cout << "The result of standart function is " << atoi(p) <<endl;
	myAtoi(p);
	return 0;
}