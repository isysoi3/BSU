// Kr7.cpp: определяет точку входа для консольного приложения.
//

// Kr6.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <set>
#include <list>

using namespace std;


int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("data.txt");
	ifstream in("q.txt");
	ofstream fout("answer.txt");
	map<string, vector<pair<string, int>>> inf;
	string student, sub;
	int mark;

	while (getline(fin, student, ';')) {
		getline(fin, sub, ';');
		fin >> mark;
		fin.ignore();
		inf[student].push_back(make_pair(sub, mark));

	}


	int n;
	string str;
	while (in >> n) {


		in.ignore();
		getline(in, str);
		int count = 0, sum = 0;
		for (auto it = inf.begin(); it != inf.end(); ++it)
			for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
				if (str == iter->first) {
					count++;
					//sum += iter->second;
				}
		if (count != 0)
			//fout << str << " = " << 1.0*sum/count << endl;
			fout << str << " = " << count << endl;
		else
			fout << "gsdg\n";
		break;

		fout << endl;
	}
	fin.close();
	in.close();
	fout.close();
	return 0;
}


