// Kr2.cpp: определяет точку входа для консольного приложения.
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
	map< string, list< pair < string, string >>> inf;
	string name, doctor, date;
	while (getline(fin, name, ';'))
	{
		getline(fin, doctor, ';');
		getline(fin, date);
		inf[name].push_back(make_pair(doctor, date));
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
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					fout << iter->first << " " << iter->second << endl;
			}
			else
				fout << "Такого пациента нет" << endl;
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
					{
						count++;
						break;
					}
			}
			if (count != 0)
				fout << "Коэфицент визитов к врчау " << str << " = " << 1.0*count / size << endl;
			else
				fout << "Такого врача не сущ\n";
			break;
		}
		case 3:
		{
			set<pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					pair.insert(make_pair(iter->second, iter->first));

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

