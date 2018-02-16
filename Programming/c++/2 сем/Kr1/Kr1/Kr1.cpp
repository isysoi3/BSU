// Kr1.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <set>

using namespace std;


int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("data.txt");
	ifstream in("q.txt");
	ofstream fout("answer.txt");
	map<string, vector<pair<string, string>>> inf;
	string name, date, doctor;

	while (getline(fin, name, ';')) {
		getline(fin, doctor, ';');
		getline(fin, date, '\n');
		//fin.ignore();
		inf[name].push_back(make_pair(doctor, date));
	}
	int n;
	string str;
	while (in >> n) {
		fout << n << ":" << endl;
		switch (n) {
		case 1:
		{
			in.ignore();
			getline(in, str);
			auto it = inf.find(str);
			if (it != inf.end()) {
				fout << it->first << ":" << endl;
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					fout << iter->first << " " << iter->second << endl;
			}
			else
				fout << "пациент не найден" << endl;
			break;
		}
		case 2:
		{
			in.ignore();
			getline(in, str);
			int count = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					if (iter->first == str) {
						count++;
						break;
					}

			if (count != 0)
				fout << "¬рач " << str << " имеет " << count << " похода(ов) к себе" << endl;
			else
				fout << "“акого врача не сущ" << endl;
			break;
		}
		case 3:
		{
			set< pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					pair.insert(make_pair(it->first, iter->second));

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

