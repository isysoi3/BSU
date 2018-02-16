// drinks.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include "Drink.h"
#include <codecvt>

using namespace std;

int main(){
	Lemonade fdf("dada", 31,"white");
	cout << fdf.getColor();


    return 0;
}

