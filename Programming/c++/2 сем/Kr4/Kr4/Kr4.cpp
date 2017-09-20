// Kr4.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <fstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <string>
#include <set>

using namespace std;

int main()
{
	map<string, vector<pair<string, string>>> inf;
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("data.txt");
	ifstream in("q.txt");
	ofstream fout("answer.txt");
	string name, doctor, date;
	while (getline(fin, name, ';'))
	{
		getline(fin, doctor, ';');
		getline(fin, date);
		inf[doctor].push_back(make_pair(name, date));
	}

	int n;
	string str;
	while (in >> n)
	{
		switch (n)
		{
		case 1: {
			in.ignore();
			getline(in, str);
			auto it = inf.find(str);
			if (it != inf.end()) {
				fout << it->first << ":" << endl;
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					fout << iter->first << " " << iter->second << endl;
			}
			else
				fout << "Ќ≈т данных" << endl;
			break;
		}
		case 2: {
			in.ignore();
			getline(in, str);
			int count = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
					if (iter->first == str)
						count++;
			if (count == 0)
				fout << "Ќ≈т данных" << endl;
			else
				fout << str << " " << count;
			break;
		}
		case 3: {
			set < pair<string, string>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				pair.insert(it->second.begin(), it->second.end());

			for (auto it = pair.begin(); it != pair.end(); ++it)
				fout << it->first << " " << it->second << endl;

			break;
		}
		}
		fout << endl;
	}


	fin.close();
	fout.close();
	in.close();

	return 0;
}

