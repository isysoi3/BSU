// Kr5.cpp: определяет точку входа для консольного приложения.
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
	map<string, list<pair<string, string>>> inf;
	string name, date, doctor;

	while (getline(fin, name, ';')) {
		getline(fin, doctor, ';');
		getline(fin, date);
		//fin.ignore();
		inf[doctor].push_back(make_pair(name, date));

	}


	int n;
	string str;
	while (in >> n) {
		switch (n) {
		case 1:
		{
			in.ignore();
			getline(in, str);
			auto it = inf.find(str);
			if (it != inf.end())
			{
				for (auto  iter = it->second.begin(); iter != it->second.end(); ++iter)
					fout << iter->first << " " << iter->second << endl;
			}
			else
				fout << "dasda" << endl;
			break;
		}
		case 2:
		{
			in.ignore();
			getline(in, str);
			int count = 0, size = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it) {
				size += it->second.size();
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					if (iter->first == str)
						count++;

			}
			if (count != 0)
				fout << "gsdg" << str << " = " << 1.0*count / size << endl;
			else
				fout << "gsdg\n";
			break;
		}
		case 3:
		{
			set< pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					pair.insert(make_pair(iter->second, it->first));

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