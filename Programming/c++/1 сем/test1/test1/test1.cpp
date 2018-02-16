#include <iostream> 
#include <ctime>

using namespace std;

int main(){
	
	int n, r = 0, s1 = 0, s2 = 0;
	cin >> n;
	int *mas = new int [n];

	srand(time(NULL));
	for (int i= 0; i < n; i++)
		mas[i] = rand() % 100 + 1;
		//cin >> mas[i];

	for ( int i= 0 ; i < n - 1 ; i ++) 
		for ( int g = i + 1 ; g < n ; g++ ) {
			if ( mas [i] > mas[g]) {
				r = mas[i];
				mas[i] = mas[g];
				mas [g] = r;
			}
		}
	
	for (int k = 0; k < n ; k ++){
		if (s1 >= s2){
			s1 += mas[k];
			
		}
		else {
			s2 += mas[k];
		
		}
	}
	while (true){
	cout << s2 - s1;
	return 0;
} 