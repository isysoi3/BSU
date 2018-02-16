// lab6.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstring>

using namespace std;

int numberOfStrings(string in) {
	ifstream fin(in);
	string strTmp;
	int N = 0;
	if (fin.is_open())
		while (getline(fin, strTmp)) {
			N++;
		}
	fin.close();
	return N;

}
void showFiles(string in, string out) {
	cout << "Display the contents of files?(y/n)";
	char ynDec;
	ynDec = _getch();
	system("cls");
	if (ynDec == 'y' || ynDec == 'Y') {
		ifstream fin(in);
		ifstream fout(out);
		cout << "\t\t\tin.txt\n-------------------------------------------------------------------\n";
		string str;
		while (!fin.eof()) {
			getline(fin, str);
			cout << str << endl;
		}
		cout << "-------------------------------------------------------------------\n";
		fin.close();
		cout << "\t\t\tout.txt\n-------------------------------------------------------------------\n";
		string str2;
		while (!fout.eof()) {
			getline(fout, str2);
			cout << str2 << endl;
		}
		cout << "-------------------------------------------------------------------\n";
		fout.close();
	}
}
void check(int N, int  numberOfReps, string str[], string out) {
	ofstream fout(out);
	for (int i = 0; i < N; i++) {
		int n = str[i].length();
		for (int g = 0; g < n - 1; g++) {
			if (str[i][g] != ' ')
				if (str[i][g] == '/' && str[i][g + 1] == '/') {
					if (i != N - 1 && str[i] == str[i + 1])
						numberOfReps++;
					else {
						fout << str[i] << " " << numberOfReps << " " << i - (numberOfReps - 1) << endl;
						numberOfReps = 1;
						break;
					}
				}
				else
					break;
		}
	}
	fout.close();
}
string file_in() {
	string s;
	cout << "Drag you input file here or write full way\n";
	getline(cin, s);
	return s;
}
string file_out() {
	string s;
	cout << "Do you want to write full way to output file?(y/n)\n";
	char ynDec;
	ynDec = _getch();
	if (ynDec == 'y' || ynDec == 'Y')
		getline(cin, s);
	else
		s = "out.txt";
	return s;
}
void openOrNotDialogIN(string in) {
	cout << "Open the input file?(y/n)";
	char ynDec;
	ynDec = _getch();
	if (ynDec == 'y' || ynDec == 'Y')
		system(in.c_str());
	cout << endl;
}
void openOrNotDialogOUT(string out) {
	char ynDec;
	cout << "Open the output file?(y/n)";
	ynDec = _getch();
	if (ynDec == 'y' || ynDec == 'Y')
		system(out.c_str());
	cout << endl;
}
int main() {

	string in;
	string out;
	in = file_in();
	out = file_out();
	
	int N = numberOfStrings(in);
	
	ifstream fin(in);
	openOrNotDialogIN(in);
	cout << "\nPress any key to fill in the output file ..." << endl;
	_getch();

	if (N != 0) {
		string *str = new string[N];
		int  numberOfReps = 1;
		for (int i = 0; i < N; i++)
			getline(fin, str[i]);
		check(N, numberOfReps, str, out);
		showFiles(in, out);
		delete[] str;
		
		fin.open(out);
	}
	else {
		ofstream fout(out);
		fout.close();
	}
	fin.close();
	system("pause");
	
	return 0;
}
//set массив неповторения