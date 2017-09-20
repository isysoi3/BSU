#include "Drink.h"

Drink::Drink(string aname, double avol) {
	if (avol <= 0)
		throw exception("Volume value is incorrect");
	name = aname;
	volume = avol;
}

Drink::~Drink(){
}

double Drink::getVolume() const {
	return volume;
}

string Drink::getName() const {
	return string(name);
}