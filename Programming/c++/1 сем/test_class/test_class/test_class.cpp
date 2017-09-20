// test_class.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

class my {
private:
	int a, b, c;
public:
	my(int number1, int number2, int number3) {
		set_abc(number1, number2, number3);
	}
	void error() {
		cout << "Error\n";
	}
	void set_abc(int number1, int number2, int number3) {
		a = number1;
		b = number2;
		c = number3;
	}
	void get_abc() {
		cout << c << " " << b << " " << a << endl;
	}
};
int main() {
	int number1, number2, number3;
	cin >> number1 >> number2 >> number3;
	my first(11, 12, 13);
	first.error();
	first.set_abc(number1, number2, number3);
	first.get_abc();
	return 0;
}
   