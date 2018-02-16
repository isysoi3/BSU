// KR.cpp: определяет точку входа для консольного приложения.
//

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

int main() {
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
			in.ignore();
			switch (n) {
			case'1': {
				getline(in, str);
				auto it = inf.find(str);
				if (it != inf.end()) {
					fout << it->first << " : " << endl;
					for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
						fout << iter->first << ", " << iter->second << " звезды" << endl;
					}
				}
				else
					fout << "Такого города нет" << endl;
				break;
			}
			case'2': {
				int count = 0;
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
					fout << str << " : " << count << " Города" << endl;
				else
					fout << "Назване отеля не найдено" << endl;
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

