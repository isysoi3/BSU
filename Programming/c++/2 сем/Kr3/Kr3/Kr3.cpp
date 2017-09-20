// Kr3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <set>

using namespace std;


int main() {
	ifstream fin("data.txt");
	ifstream in("q.txt");
	ofstream fout("answer.txt");
	multimap< string, pair < string, string >> inf;
	string name, doctor, date;
	while (getline(fin, name, ';'))
	{
		getline(fin, doctor, ';');
		getline(fin, date);
		inf.insert(make_pair(name, make_pair(doctor, date)));
	}

	int n;
	string str;
	while (in >> n)
	{
		switch (n)
		{
		case 1:
		{
			in.ignore();
			getline(in, str);
			auto it = inf.find(str);

			if (it != inf.end()) {
				fout << it->first << ":\n";
				for (it; it->first == str; ++it)
					fout << it->second.first << " " << it->second.second << endl;
			}
			else
					fout << "Такого пациента нет" << endl;
			break;
		}
		case 2:
		{
			in.ignore();
			getline(in, str);
			int count = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				if (str == it->second.second)
					count++;

			if (count != 0)
				fout << "Визитов " << str << " = " << count << endl;
			else
				fout << "Визитов в этот день нет\n";
			break;
		}
		case 3:
		{
			set<pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				pair.insert(make_pair(it->first, it->second.first));
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



