#include <iostream>
using namespace std;
 
int main(){
    int i, j, S, N; //индексы
	cout << "Enter  N ";
    cin >> S;
    N = S + 1;
    bool *mas =  new bool [N ];; //объ€вл€ем массив типа bool
    for(i = 1; i<=S; i++)
		mas[i] = true; //заполн€ем массив значением true;
    for(i=2; ((i*i)<=S); i++)  //јлгоритм "–ешето Ёратосфена"
	if(mas[i])
    for(j=(i*i); j<=S; j+=i)
        if(mas[j]) 
			mas[j]=false;
    for(i=1; i<=S; i++)
		if(mas[i]) 
			cout << i << " ";
        return 0;
}