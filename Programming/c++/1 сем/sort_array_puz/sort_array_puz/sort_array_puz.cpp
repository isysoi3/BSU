// sort_array_puz.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string>
#include <ctime>


using namespace std;

void outputarray ( int array[], int n, string str){
	string t;
	cout << str;
	cin >> t ;
	if ( t == "Y" ) {
		for ( int i = 0 ; i < n ; i ++) {
			cout << array[i] << " ";
		}
	}
	cout << endl;
}
int inputnumber(string str) {
	int n;
		while(true){
		cout << str;
		cin >> n;
		if (!cin){
			cout << "Ввели не верно, повторите" << endl;
			cin.clear();
			while (cin.get() != '\n');
		}
		else 
			break;
		}
	return n;
	}
void sortarray (int array[], int n){
	int r;
	for ( int i= 0 ; i < n - 1 ; i ++) {
		for ( int g = i + 1 ; g < n ; g++ ) {
			if ( array [i] > array[g]) {
				r = array[i];
				array[i] = array[g];
				array [g] = r;
			}
		}
	}
}
void randomarray (int array[], int n){
	srand( time( 0 ) );
	for ( int i = 0 ; i < n ; i ++){
		array [i] = rand () % 200 + 1 ;
	}
}
int main (){
	setlocale ( LC_ALL, "RUS" );
	int n; 
	string str = "Введите число элементов массива ";
	string str1 = "Выводить исходный массив (Y/N) ? ";
	string str2 = "Выводить отсортированный массив (Y/N) ? ";
	n = inputnumber(str) ;
	int *array = new int [n];
	randomarray (array, n);
	outputarray ( array, n , str1);
	sortarray( array, n );
	outputarray (array, n ,str2);	
	delete [] array;
	return 0;
}