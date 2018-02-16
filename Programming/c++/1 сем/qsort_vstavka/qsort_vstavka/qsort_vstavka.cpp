// qsort_vstavka.cpp: определяет точку входа для консольного приложения.
//

// sort_array_puz.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string>
#include <ctime>


using namespace std;

void outputarray ( int array[], int n, string str){
	char t;
	cout << str;
	cin >> t;
	if ( (t == 'Y') || (t == 'y') ) {
		for ( int i = 0 ; i < n ; i ++) {
			cout << array[i] << " ";
		}
	}
	cout << endl;
}
void q_sort (int array[], int n){
	
}
void sort (int array[], int n){

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
	cout << "Введите число элементов массива " << endl;
	cin >> n ;
	string str1 = "Выводить исходный массив (Y/N) ? ";
	string str2 = "Выводить отсортированный массив (Y/N) ? ";
	
	int *array = new int [n];
	randomarray (array, n);
	outputarray ( array, n , str1);
	outputarray (array, n ,str2);	
	
	delete [] array;
	
	return 0;
}