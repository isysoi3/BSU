// class_person.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

int main(){
	try {
		string str;
		str = "Clark";
		Person adam("Adam", male);
		Person eva("Eva", female);
		Person mum("Clara", female, eva, adam);
		Person dad("David",male,eva);
		Person docha = mum.giveBirth(str, female, dad);
		Person sob = docha.giveBirth("dadda", male);
		cout << adam;
		cout << mum;
		cout << mum.getFather().getName() << " " << mum.getMother().getName() << endl;
		cout << docha;
		cout << docha.getFather().getName() << " " << docha.getMother().getName() << endl;
		cout << sob.GetID() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}

