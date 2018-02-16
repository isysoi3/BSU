// lab1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <iterator>
#include <algorithm>
#include "Compare.h"

using namespace std;

int main() {
	ifstream fin("in.txt");
	string str;
	deque<string> deq;

	while (getline(fin, str)) {
		deq.push_back(str);
	}
	stable_sort(deq.begin(), deq.end(), Compare());
	copy(deq.begin(), deq.end(), ostream_iterator<string>(cout, "\n"));

	fin.close();
	return 0;
}