#include <iostream>

using namespace std;

int  max1 = 0, max2 = 0;

void found(char *str) {

	int u = -1, max = -1, k, b, i;
	
	do {
		b = u + 1;
		k = 0;
		u++;
		while (str[u] != ' ') {
			u++;
			if (str[u] == '\0')
				break;
		}
	
		for (i = b; i < u ; i++){
			for (int j = i + 1; j < u; j++) {
				if (str[j] == str[i])
					k++;
				}
			}
			if (k > max) {
				max = k;
				max1 = b;
				max2 = i;
			}
	
	} while(str[u] != '\0');
	
}
int main() {

	char *str = new char[301];
	
	cout << "Enter your string:" << endl;
	cin.getline(str, 300);
	found(str);
	
	cout << "The first word with the largest number of repeating characters :" << endl;
	
	for ( max1; max1 < max2; max1++)
		cout << str[max1];

	cout << endl;

	delete[] str;

	return 0;
}