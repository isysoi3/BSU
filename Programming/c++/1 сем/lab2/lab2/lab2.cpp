// lab2.cpp: определяет точку входа для консольного приложения.
//
//
// 
#include <iostream>

using namespace std;

void arraySort(float array[], int n) {
	
	float r;

	for (int i = 2 ; i <= n ; i += 2) {
		for (int g = i + 2 ; g <= n ; g += 2) {
			if (array [i] > array [g]) {
				r = array [i];
				array [i] = array [g];
				array [g] = r;
			}
		}
	}
}
void arrayOutput(float array[], int n) {
	
	for (int i = 1 ; i <= n ; i++)
		cout << array [i] << " " ;
	cout << endl;
}
void arrayInput (float array[], int n) {
		for (int i = 1 ; i <= n ; i++) {
					cout << "Введите значение элемента масаива под номером " << i << endl;
					cin >> array [i] ;
		}
}
int numberInput(int n) {
	while (true) {
		cout << "Введите количество элементов массива : ";
		cin >> n;
		if (n > 0) 
			break;
			cout << "Ввели не верно, повторите ввод" << endl;	
	}
	return n;
}
void sum(float array[], int n){
	
	float sum = 0;
	int k = 0;

	for (int i=1 ; i <= n ; i++) {
			if (array [i] < 0)
				sum += array[i];
			else 
				k++;
		}
	if (k == n)
        cout << "Отрицательных чисел нет  " << endl;
    else 
        cout << "Сумма отрицательных чисел = " << sum << endl ;
}
void multipl(float array[], int n) {
	
	int g = 0;
	int l = 0;
	float max = -200000;
	float min = 200000;
	double p = 1;

	for (int i = 1 ; i <= n ; i++){
		if (array[i] <= min){
			min = array[i];
			g = i;
		}
		if (array[i] >= max){
			max = array[i];
			l = i;
		}
	}
	if (l > g)
		if (l - g > 2) {
			for (g = g + 1 ; g < l ; g++)
				p = p * array[g];
				cout << "Произведение элементов массива, расположенных между последним макс и последним мин элементами = " << p << endl;
		}
		else
			if (l - g == 1)
				cout << "Между последним макс и мин нет элементов" << endl;
			else 
				cout << "Есть между последним макс и последним мин элементами один элемент = " << array[g+1]<< endl;
				
	else 
		if (g - l > 2) {
			for (l = l + 1 ; l < g ; l++) 
				p = p * array[l];
			cout << "Произведение элементов массива, расположенных между последним макс и последним мин элементами = " << p << endl;
	}
		else 
			if (g - l == 1)
				cout << "Между последним макс и мин нет элементов" << endl;
			else 
				cout << "Есть между последним макс и последним мин элементами один элемент = " << array[l+1]<< endl;
}
int main() {
    setlocale ( LC_ALL, "RUS");

	int n = 0;
	n = numberInput(n);
	float *array = new float [n+1];

	arrayInput(array, n);
	multipl(array, n);
	sum(array, n);
	arrayOutput(array, n);
	arraySort(array , n);
	arrayOutput(array, n);

	delete [] array;

    return 0;
}
