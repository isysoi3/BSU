// test_lab4.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>

using namespace std;

int found (char *str){
	const int N = 256;
	
	int *mas = new int [N];
	for (int i = 0; i < N ; i++)
		 mas[i] = 0;
	
	int n = strlen(str);
	
	int  k = 0, l = 0, b = 0, u = 0, c = 0, max = 0, max1 = 0, max2 = 0;
	
	for (int i = 0; i < n; i++)
		mas[str[i]]++;
	
	int maxMas = mas[0];
	for (int i = 1; i < N ; i++)
		if (maxMas < mas[i] && maxMas != mas[i] && i != 32){
			maxMas = mas[i];
			l = i;
		}
	
	while( str[u] != '\0' ){
		if (!(str[u] != ' ' && u == n - 1 || str[ u + 1 ] == ' ')) {	
			u++;
			continue;
		}
		else {
			c = 0;
			for (k = b  ; k <= u; k++)
				if (str[k] == l){
					c++;
				}
			if (c > max && c != max) {
				max = c;
				max1 = b  ;
				max2 = u ;
			}
			
		}
		u++;
		b = u + 1;
		
	}	

	cout << "The first word with the largest number of repeating characters :" << endl;
	
	for (max1; max1 <= max2 ; max1++)
		cout << str[max1];
	
	cout << endl << "This symbol is "  << (char)l ;
	
	delete [] mas;
	
	return 0;
	
}
int main() {
	char *str = new char [301];
	
	cout << "Enter your string:" << endl;
	cin.getline(str, 300);
	
	found(str);
	
	cout << endl;
	
	delete [] str;
	
	return 0;
}