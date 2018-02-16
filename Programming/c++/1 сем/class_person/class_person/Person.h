#pragma once
#include <string>
using namespace std;

enum Gender {female, male};

class Person {
private:
	string name;
	const Gender gender;
	const Person *father = nullptr;
	const Person *mother = nullptr;
	const int id;
	static int current_id;
public:
	Person(string, Gender);
	Person(string, Gender, const Person&);
	Person(string, Gender, const Person&, const Person&);
	~Person();
	string getName() const;
	char* getGender() const;
	Person giveBirth(string, Gender, const Person&) const;
	Person giveBirth(string, Gender) const;
	Person getFather() const;
	Person getMother() const;
	int GetID() const;
	friend ostream& operator << (ostream&, const Person&);
};

