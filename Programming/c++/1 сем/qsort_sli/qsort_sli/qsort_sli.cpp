// qsort_sli.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string>
#include <ctime>


using namespace std;

int inputNumber (string str) {
	
	int n;
	cout << str;
	cin >> n;
	while (n < 1){
		cout << "Ввели не верно, повторите ввод" << endl;
		cout << str;
		cin >> n;
	}
	return n;
}
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
void q_sort (int *array, int f){
	int s = 0, end = f , r = 0;
	int m = array[rand() % f + s];
	do{ 
		while (array[s] < m)
			s++;
		while (array[f] > m)
			f--;
		if ( s <= f){
			r = array[s];
			array[s] = array[f];
			array[f] = r;
			s++;
			f--;
		}
	} while (s <= f);
	if (f > 0)
		q_sort(array, f);
	if (end > s)
		q_sort(array + s, end - s);
}
void sort1(int *array, int f, int l) {
	int  left, right, i;
	int *mas = new int[l+1];
	left = f; 
	right = (f + l) / 2 + 1;
	
	for(i = f; i <= l; i++)
		if ((left <= (f + l)/2) && ((right > l) || (array[left] < array[right]))){
			mas[i]= array [left];
			left++;
		}
		else{
			mas[i]= array[right];
			right++;
		}
	
	for (i = f; i <= l; i++) 
		array[i] = mas[i];

	delete [] mas;
}
void mergeSort(int *array, int f, int l){
	if (f < l){
		mergeSort(array, f, (f+l)/2); 
		mergeSort(array, (f+l)/2+1, l);
		sort1(array, f, l);
	}	
}
void randomarray (int array[], int n){
	srand( time( 0 ) );
	for ( int i = 0 ; i < n ; i ++){
		array [i] = rand () % 200 + 1 ;
	}
}
void inputArray(int array[], int n) {
	char a;
	cout << "Хотите заполнить сами (Y/N)? ";
	cin >> a;

	if ((a == 'Y') || (a == 'y'))
		for (int i = 0 ; i < n ; i++)
			cin >> array[i];
	else
		randomarray (array, n);
}
int main (){
	
	setlocale ( LC_ALL, "RUS" );
	
	int n, b;

	string str = "Введите число элементов массива " ;
	string str1 = "Выводить исходный массив (Y/N) ? ";
	string str2 = "Выводить отсортированный массив (Y/N) ? ";
	
	n = inputNumber(str) ;

	int *array = new int [n];

	inputArray(array, n);
	outputarray ( array, n , str1);
	
	cout << "Ведите 1 , чтобы отсортировать массив через слияние\n" << "Или 2, чтобы отсортировать массив через быструю сортировку" << endl;
	cin >> b;

	if (b == 1)
		mergeSort(array, 0, n - 1);
	else 
		q_sort(array, n-1);
	outputarray (array, n ,str2);	
	
	delete [] array;
	
	return 0;
}
