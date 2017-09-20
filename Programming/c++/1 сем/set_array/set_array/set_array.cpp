// set_array.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <set>

using namespace std;

void input_output(int n, int array[]) {
	for (int i = 0; i < n; i++) {
		cout << "Введите " << i + 1 << " элемент мвссива ";
		cin >> array[i];
	}
}
int main() {
	setlocale(LC_ALL, "RUS");
	cout << "Введите размерность массива ";
	int n;
	cin >> n;
	set<int> Myset;
	int *array = new int[n];
	input_output(n, array);
	for (int i = 0; i < n; i++) {
		Myset.insert(array[i]);
	}
	cout << "Число различных элементов : " << Myset.size() << endl;
	delete[] array;
	return 0;
}



//сколько различных элементов в мас