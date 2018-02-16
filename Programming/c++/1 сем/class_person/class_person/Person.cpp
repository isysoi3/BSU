#include "Person.h"
#include <exception>


int Person::current_id = 0;

Person::Person(string aname, Gender sex) : id(++current_id), gender(sex) {
	if (id != 1 && id != 2)
		throw exception("Person should have a mother");
	if (aname == "")
		throw invalid_argument("Invalid name");
	name = aname;
}

Person::Person(string aname, Gender sex, const Person& amother) : id(++current_id), gender(sex) {
	if (aname == "")
		throw invalid_argument("Invalid name");
	name = aname;
	mother = &amother;
}

Person::Person(string aname, Gender sex, const Person& amother, const Person& afather) : id(++current_id), gender(sex) {
	if (aname == "")
		throw invalid_argument("Invalid name");
	name = aname;
	mother = &amother;
	father = &afather;
}

Person::~Person() {
}

string Person::getName() const {
	return name;
}

char* Person::getGender() const {
	if (gender == male)
		return "Male";
	else
		return "Female";
}

Person Person::giveBirth(string aname, Gender sex, const Person& father) const {
	if (this->gender == male)
		throw exception("I am male and i can not have a baby!!!");
	if (father.gender == female)
		throw exception("Two female can not give a baby");
	Person baby(aname, sex, *this, father);
	return baby;
}

Person Person::giveBirth(string aname, Gender sex) const {
	if (this->gender == male)
		throw exception("I am male and i can not have a baby!!!");
	Person baby(aname, sex, *this);
	return baby;
}

Person Person::getFather() const {
	if (father == nullptr)
		throw exception("Father unknown");
	else
		return *father;
}

Person Person::getMother() const {
	if (mother == nullptr)
		throw exception("Mother unknown");
	return *mother;
}

int Person::GetID() const {
	return id;
}

ostream& operator << (ostream &out, const Person &p) {
	out << p.getName() << " " << p.getGender() << " " << p.GetID() << endl;
	return out;
}