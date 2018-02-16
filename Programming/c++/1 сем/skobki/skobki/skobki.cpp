// skobki.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ifstream fin("SMILES.IN");
	ofstream fout("SMILES.OUT");
	setlocale(LC_ALL, "RUS");

	char str[30001];

	while (!fin.eof()) {

		fin >> str;
		int top = 0;
		int len = strlen(str);
		char *stack = new char[len];

		for (int i = 0; i < len; i++) {
			if (str[i] == ':') {
				i++;
			}
			else {
				stack[top] = str[i];
				if (!(stack[top] == '(' || stack[top] == '{' || stack[top] == '[')) {
					if (stack[top] == ']' && stack[top - 1] == '[')
						top -= 2;
					else
						if (stack[top] == ')' && stack[top - 1] == '(')
							top -= 2;
						else
							if (stack[top] == '}' && stack[top - 1] == '{')
								top -= 2;
							else
								top++;
				}
				top++;
			}
		}

		if (top == 0)
			fout << "Всего хватает :)";
		else
			for (int g = 0;g < top ; g++) {
				if (stack[g] == ']') {
					fout << "Не хватает [ ";
					break;
				}
				else
					if (stack[g] == '[') {
						fout << "Не хватает ] ";
						break;
					}
					else
						if (stack[g] == ')') {
							fout << "Не хватает ( ";
							break;
						}
						else
							if (stack[g] == '(') {
								fout << "Не хватает ) ";
								break;
							}
							else
								if (stack[g] == '}') {
									fout << "Не хватает { ";
									break;
								}
								else
									if (stack[g] == '}') {
										fout << "Не хватает { ";
										break;
									}
			}
		delete[] stack;
		fout << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
