#include "Soft_Drink.h"



Soft_Drink::Soft_Drink()
{
}


Soft_Drink::~Soft_Drink()
{
}


Soft_Drink::Soft_Drink()
{
}

Soft_Drink::~Soft_Drink()
{
}

Milk::Milk(string aname, double acap, double afat) {
	name = aname;
	capacity = acap;
	fatness = afat;
}

Milk::~Milk()
{
}

string Milk::getName() const {
	return string(name);
}

double Milk::getCapacity() const {
	return capacity;
}

double Milk::getFatness() const {
	return fatness;
}

Lemonade::Lemonade(string aname, double acap, string sortOFdrink) {
	name = aname;
	capacity = acap;
	if (sortOFdrink == "original")
		sort = original;
	else
		if (sortOFdrink == "buratino")
			sort = buratino;
		else
			if (sortOFdrink == "duchess")
				sort = duchess;
			else
				if (sortOFdrink == "soda")
					sort = soda;
				else
					throw exception("Error: plese enter again sort of drink");
}

Lemonade::~Lemonade()
{
}

string Lemonade::getName() const {
	return string(name);
}

double Lemonade::getCapacity() const {
	return capacity;
}

string Lemonade::getSort() const {
	switch (sort)
	{
	case Lemonade::original:
		return string("original");
		break;
	case Lemonade::buratino:
		return string("buratino");
		break;
	case Lemonade::duchess:
		return string("duchess");
		break;
	case Lemonade::soda:
		return string("soda");
		break;
	}
}

Mineral_Water::Mineral_Water(string aname, double acap, string str) {
	name = aname;
	capacity = acap;
	if (str == "strong")
		gas = strong;
	else
		if (str == "middling")
			gas = middling;
		else
			if (str == "weakly")
				gas = weakly;
			else
				if (str == "without")
					gas = without;
				else
					throw exception("Error: plese enter again the number of gas");
}

Mineral_Water::~Mineral_Water()
{
}

string Mineral_Water::getName() const {
	return string(name);
}

double Mineral_Water::getCapacity() const {
	return capacity;
}

string Mineral_Water::getGas() const {
	switch (gas)
	{
	case Mineral_Water::strong:
		return string("strong");
		break;
	case Mineral_Water::middling:
		return string("middling");
		break;
	case Mineral_Water::weakly:
		return string("weakly");
		break;
	case Mineral_Water::without:
		return string("without");
		break;
	}
}