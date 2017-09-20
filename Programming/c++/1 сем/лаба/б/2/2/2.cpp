// 2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main(){
    setlocale (LC_ALL,"RUS");
	cout << "Введите число" << endl;
	int n, d, r;  
	cin >> n;
	cout << "Простые:" ;
	for ( int i = 2; i < n; i++ )
	{
		d = 2;
		do {
			r = i % d;
			if (r != 0) 
				d++;
		}
		while ( r != 0 );
		if (d == i){
			cout << d <<",";
		}
	}
	cout << endl;
    return 0;
}