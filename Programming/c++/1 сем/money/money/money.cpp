// money.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string>

using namespace std;

void output (int array[2][8]){
	for ( int i = 0 ; i < 2 ; i++){
		for ( int g = 0 ; g < 8 ; g++ ){
			cout  << array[i][g] << " | ";
		}
		cout << endl;
}
}
int sum (int array[2][8], string str){
	int n, s, k;
	s = 0;
	k = 0;
	cout << str << endl;
	cin >> n;
	while ( n > 0){
		for (int i = 0 ; i < 8 ; i++){	
			if ( array[0][i] == n){
				s += array[0][i];
				array[1][i]++;
				k++;
				break;
			}
		}
		if ( k == 0){
			cout << "Неправильно.Повторите ввод" << endl;		
		}
		cout << str << endl;
		cin >> n;
		k = 0;
		
	}
	
	return s;
}
int main (){
	setlocale (LC_ALL, "RUS" );
	int array[2][8]={
		{100, 500, 1000, 5000, 10000, 50000 , 100000, 200000} ,
		{0, 0, 0, 0, 0, 0, 0, 0}
	};
	int s;
	string str = "Введите номинал банкноты";
	s = sum (array, str);
	output (array);
	cout << endl;
	cout << "Всего денег : " << s << endl;
	return 0;
}
