// Kr16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <map>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("data.txt");
	ifstream in("q.txt");
	ofstream fout("Answer.txt");
	multimap <string, pair<string, double>> inf;
	string marka, model;
	double volmue;
	while (getline(fin, marka, ';'))
	{
		getline(fin, model, ';');
		fin >> volmue;
		fin.ignore();
		inf.insert(make_pair(marka, make_pair(model, volmue)));
	}

	int n;
	string str;
	double d;
	while (in >> n)
	{
		switch (n)
		{
		case 1:
		{
			in.ignore();
			getline(in, str);
			pair<multimap <string, pair<string, double>>::iterator, multimap <string, pair<string, double>>::iterator> pa;
			pa = inf.equal_range(str);
			if (pa.first != inf.end() && pa.first->first == str)
			{
				for (auto it = pa.first; it != pa.second; ++it)
				{
					fout << it->second.first << " " << it->second.second << endl;
				}
			}
			else
				fout << "1empty" << endl;
			break;
		}
		case 2:
		{
			in.ignore();
			in >> d;
			int count = 0;
			for (auto it = inf.begin(); it != inf.end(); ++it)
			{
				if (it->second.second == d)
					count++;
			}
			if (count != 0)
				fout << d << " = " << count << endl;
			else
				fout << "empty2" << endl;
			break;
		}
		case 3: {
			set<pair<string, double>> pair;
			for (auto it = inf.begin(); it != inf.end(); ++it)
				pair.insert(make_pair(it->first, it->second.second));
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

