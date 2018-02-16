// 7.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int main(){
	setlocale(LC_ALL,"Rus");
	cout <<"Введите число"<<endl;
	int n,a,b;
	cin >>n;
	cout <<"Палиндром:";
	for (int i = 11; i < n; i++)
	{
		a=i;
		b=0;
		while (a>0)
		{
			b=b*10+a%10;
			a/=10;
		}
		if (b==i){
			cout <<i<<",";
		}
	}
	cout <<endl;
	return 0;
}