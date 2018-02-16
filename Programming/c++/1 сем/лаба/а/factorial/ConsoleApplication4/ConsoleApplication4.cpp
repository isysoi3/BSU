// ConsoleApplication4.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>;

using namespace std;

int main()
{
	cout << "enter number" << endl;

	int n = 0;
	long long p = 1;

	cin >> n;

	for ( int i = 1; i <= n; i++ )
	{
		p = i * p;
	}

	cout << "factorial "<<  p << endl;
	
	return 0;

}

