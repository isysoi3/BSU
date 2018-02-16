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
	multimap<string, pair<string, string>> inf;
	string name, date, doctor;

	while (getline(fin, name, ';')) {
		getline(fin, doctor, ';');
		getline(fin, date);
		//fin.ignore();
		inf.insert(make_pair(doctor, make_pair(name, date)));

	}


	int n;
	string str;
	while (in >> n) {
		in.ignore();
		switch (n) {
		case 1:
		{
			
			getline(in, str);
			bool flag = true;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				if (it->second.first == str) {
					fout << it->first << " " << it->second.second << endl;
					flag = false;
				}
				if(flag)
					fout << "dasda" << endl;
			break;
		}
		case 2:
		{
			getline(in, str);
			int count = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				if (it->second.second == str)
					count++;
			if (count != 0)
				fout  << str << " = " << count << endl;
			else
				fout << "gsdg\n";
			break;
		}
		case 3:
		{
			set< pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				pair.insert(make_pair(it->second.first, it->first));

			//copy(pair.begin(), pair.end(), ostreambuf_iterator <pair<string,string>>(fout, "\n"));
			for (auto it = pair.begin(); it != pair.end(); ++it)
				fout << it->first << " " << it->second << endl;
			break;
		}
		}
		fout << endl;
	}











	fin.close();
	in.close();
	fout.close();
	return 0;
}
