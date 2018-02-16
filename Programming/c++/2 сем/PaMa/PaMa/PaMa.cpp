// PaMa.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include "SayClass.h"
using namespace std;

void GetInfo(string& str, int& r, int& deleay)
{
	cout << "¬ведите слово: ";
	cin >> str;
	cout << "¬ведите количесво повторений этого слова: ";
	cin >> r;
	cout << "¬ведите задержку: ";
	cin >> deleay;
	cout << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	int N, tmp;
	cout << "¬ведите количество слов: ";
	cin >> N;
	cout << "¬ведит общее количество повторений: ";
	cin >> tmp;
	cout << endl;
	SayClass::TotalRepeats = tmp;
	vector <SayClass> vec;
	string str;
	int r = 0, delay = 0;

	for (int i = 0; i < N; i++) {
		GetInfo(str, r, delay);
		auto sc = SayClass(str, r, delay);
		vec.push_back(sc);
	}

	thread *thr = new thread[vec.size()];

	for (int i = 0; i < vec.size(); i++)
	{
		thr[i] = thread(&SayClass::Say, vec[i]);
	}

	for (int i = 0; i < vec.size(); i++)
	{
		if (thr[i].joinable())
			thr[i].join();
	}

	delete[] thr;
	return 0;
}

