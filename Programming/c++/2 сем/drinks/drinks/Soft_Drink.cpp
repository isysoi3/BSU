#include "Soft_Drink.h"

Soft_Drink::Soft_Drink(string aname, double avol) : Drink(aname, avol) {
}

Soft_Drink::~Soft_Drink(){
}

Milk::Milk(string aname, double avol, double afat) : Soft_Drink(aname, avol) {
	if (afat >= 7.5 || afat < 0)
		throw exception("The fatness is incorrect");
	fatness = afat;
}

Milk::~Milk(){
}

double Milk::getFatness() const {
	return fatness;
}

Lemonade::Lemonade(string aname, double avol, Additive add) : Soft_Drink(aname, avol) , additive(add){
}

Lemonade::~Lemonade()
{
}

string Lemonade::getAdd() const {
	switch (additive) {
	case apple:
		return string("apple");
	case pear:
		return string("pear");
	case orange:
		return string("orange");
	}
}

Mineral_Water::Mineral_Water(string aname, double avol, TheNumberOfGas gs) : Soft_Drink(aname, avol) {
	gas = gs;
}

Mineral_Water::~Mineral_Water()
{
}

string Mineral_Water::getGas() const {
	switch (gas)
	{
	case strong:
		return string("strong");
	case middling:
		return string("middling");
	case without:
		return string("without");
	}
}
