// Ships.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Ship.h"
#include <deque>

using namespace std;

//bool isFree(vector <Ship*> &a) {
//	if (a.back() == nullptr)
//		return true;
//	return false;
//}
//bool isFree(vector <Ship*> &a) {
//	for (unsigned int i = 0; i < a.size(); i++){
//		if (a[i] == nullptr)
//			return true;
//	}
//	return false;
//}
//
//int freePos(vector <Ship*> &a) {
//	for (unsigned int i = 0; i < a.size(); i++) {
//		if (a[i] == nullptr)
//			return i;
//	}
//}

pair<bool, int> position(vector <Ship*> &a) {
	for (unsigned int i = 0; i < a.size(); i++) {
		if (a[i] == nullptr)
			return make_pair(true, i);
	}
	return make_pair(false, 0);
}

int main() {
	ifstream fin("SHIPS.IN");
	ofstream fout("SHIPS.OUT");

	int N;

	if (fin.is_open()) {
		if (fin >> N) {

			int numb, size, pos;
			pair <bool, int> info;
			string str;
			

			vector <Ship*> port(N);
			deque <Ship*> raid;

			while (fin >> numb) {
				switch (numb) {
				case 1: {
					getline(fin, str);
					fout << "Ship"<< str <<" is arriving to the port\n\n";
					Ship *sh = new Ship(str);
					info = position(port);
					if (info.first)
						port[info.second] = sh;
					else
						raid.push_back(sh);
					break;
				}
				case 2: {
					fin >> pos;
					fout << "Ship" << port[pos-1]->getName() << " is leaving from the port\n\n";
					if (!raid.empty()) {
						delete port[pos - 1];
						port[pos - 1] = raid.front();
						raid.pop_front();
					}
					else {
						delete port[pos - 1];
						port[pos - 1] = nullptr;
					}
					break;
				}
				case 3: {
					fout << "Raid:\n";
					size = raid.size();
					for (int i = 0; i < size; i++) {
						fout << i + 1 << " -" << raid[i]->getName() << "\n";
					}
					fout << endl;
					break;
				}
				case 4: {
					fout << "Port:\n";
					for (int i = 0; i < N; i++) {
						if (port[i] == nullptr)
							fout << i + 1 << " -" << "\n";
						else
							fout << i + 1 << " -" << port[i]->getName() << " id" << port[i]->getID() << "\n";

					}
					fout << endl;
					break;
				}
				}
			}
		}
		else
			fout << "File is empty";
	}
	else
		fout << "Error opening file";

	fin.close();
	fout.close();
	return 0;
}

