// KR.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <conio.h>
#include <set>
#include <iterator>
#include <Windows.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("data.txt");
	ifstream in("test.txt");
	ofstream fout("out.txt");
	map < string, vector< pair<string, int>>> inf;
	string name, city;
	int stars;
	while (getline(fin, city, ';')) {
		getline(fin, name, ';');
		fin >> stars;
		fin.ignore();
		inf[city].push_back(make_pair(name, stars));
	}
	char n;
	while (true) {
		string str;
		if (in >> n) {
			switch (n) {
			case'1': {
				for (auto it = inf.begin(); it != inf.end(); ++it) {
					fout << it->first << " : " << endl;
					for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
						fout << iter->first << ", " << iter->second << " stars" << endl;
					}

				}
				break;
			}
			case'2': {
				int count = 0;
				in.ignore();
				getline(in, str);
				for (auto it = inf.begin(); it != inf.end(); ++it) {
					for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
						if (iter->first == str) {
							count++;
							break;
						}
					}
				}
				if (count != 0)
					fout << str << " : " << count << " cites" << endl;
				else
					fout << "Hotel dosen`t find" << endl;
				break;
			}
			case'3': {
				set<pair<string, int>> pair;
				for (auto it = inf.begin(); it != inf.end(); ++it) {
					for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
						pair.insert(make_pair(it->first, iter->second));

					}
				}
				for (auto it = pair.begin(); it != pair.end(); ++it)
					fout << it->first << " : " << it->second << endl;
				break;
			}
			}
			fout << endl;
		}
		else
			break;
	}
	fin.close();
	fout.close();
	in.close();
	return 0;
}

