// Kr17.cpp: определяет точку входа для консольного приложения.
//

#include <Windows.h>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <set>

using namespace std;

int main()
{
	/*setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/

	ifstream fin("data.txt");
	ofstream fout("answer.txt");

	map<string, list<pair<string, double>>> cars;
	map<string, list<pair<string, double>>>::iterator it;
	list<pair<string, double>>::iterator iter;
	if (fin.is_open())
	{
		string marka, model;
		double volume;
		while (getline(fin, marka, ';'))
		{
			getline(fin, model, ';');
			fin >> volume;
			fin.ignore();
			cars[marka].push_back(make_pair(model, volume));
		}

		fin.close();
		fin.open("q.txt");
		if (fin.is_open())
		{
			int n;
			string str;
			while (fin >> n)
			{
				fin.ignore();
				fout << n << ":\n";
				switch (n)
				{
				case 1:
				{
					getline(fin, str);
					it = cars.find(str);
					if (it != cars.end()) {
						fout << str << " :\n";
						for (iter = it->second.begin(); iter != it->second.end(); ++iter)
							fout << iter->first << ", объем двигателя = " << iter->second << "\n";
					}
					else
						fout << "Такой марки нет\n";
					break;
				}
				case 2:
				{
					bool flag = true;
					getline(fin, str);
					for (it = cars.begin(); it != cars.end(); ++it) {
						//iter = find(it->second.begin(), it->second.end(), str);
						for (iter = it->second.begin(); iter != it->second.end(); ++iter)
							if (iter->first == str) {
								fout << "Марка : " << it->first;
								flag = false;
							}
					}
					if (flag)
						fout << "Модель не была найдена.";
					break;
				}
				case 3:
				{
					set<pair<string, string>> pair;
					/*for (it = cars.begin(); it != cars.end(); ++it)
						for (iter = it->second.begin(); iter != it->second.end(); ++iter)*/
					for each(auto it in cars)
						for each (auto iter in it.second)
							pair.insert(make_pair(it.first, iter.first));

					for (auto i = pair.begin(); i != pair.end(); ++i)
						fout << i->first << " " << i->second << "\n";

					break;
				}
				}
				fout << endl;
			}
		}
		else
			fout << "Ошибка при чтении входного файла с запросами" << endl;
	}
	else
		fout << "Ошибка при чтении входного файла с данными" << endl;


	set <int> as;
	as.insert(2);
	as.insert(3);
	as.insert(4);
	auto iterator it = as.begin();
	for (it; it != as.end(); ++it)
		fout << *it << " ";
	return 0;
}