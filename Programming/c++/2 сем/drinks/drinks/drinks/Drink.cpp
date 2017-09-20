#include "Drink.h"


Drink::Drink(string aname, double acap){
	name = aname;
	capacity = acap;
}

Drink::~Drink()
{
}

double Drink::getCapacity() const {
	return capacity;
}

string Drink::getName() const{
	return string(name);
}

/////////////////////////////////

Soft_Drink::Soft_Drink(string aname, double acap) : Drink(aname, acap){
}

Soft_Drink::~Soft_Drink()
{
}


Milk::Milk(string aname, double acap, double afat) : Soft_Drink(aname, acap){
	fatness = afat;
}

Milk::~Milk()
{
}

double Milk::getFatness() const {
	return fatness;
}

Lemonade::Lemonade(string aname, double acap, string col) : Soft_Drink(aname, acap){
	if (col == "red") //исправить IF
		colorOFdrink = red;
	else
		if (col == "green")
			colorOFdrink = green;
		else
			if (col == "yellow")
				colorOFdrink = yellow;
			else
				if (col == "white")
					colorOFdrink = white;
				else
					throw exception("Error: color of lemonade is unknown");
}

Lemonade::~Lemonade()
{
}

string Lemonade::getColor() const {
	switch (colorOFdrink){
	case Lemonade::green:
		return string("green");
		break;
	case Lemonade::yellow:
		return string("yellow");
		break;
	case Lemonade::white:
		return string("white");
		break;
	case Lemonade::red:
		return string("red");
		break;
	}
}

Mineral_Water::Mineral_Water(string aname, double acap, string str) : Soft_Drink(aname, acap){
	if (str == "strong") //исправить IF
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

string Mineral_Water::getGas() const{
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


Tipple::Tipple(string aname, double acap, double stur) : Drink(aname, acap) {
	sturdiness = stur;
}

Tipple::~Tipple()
{
}

double Tipple::getSturdiness() const{
	return sturdiness;
}

Cognac::Cognac(string aname, double acap, double stur, int days) : Tipple(aname, acap, stur){
	excerptInDays = days;
}

Cognac::~Cognac(){
}

int Cognac::getExcert() const{
	return excerptInDays;
}

void Cognac::setExcert(int days){
	excerptInDays = days;// можно выбросить исключение если <
}

Beer::Beer(string aname, double acap, double stur, string str) : Tipple(aname, acap, stur){
	if (str == "filtered")
		filtInfo = filtered;
	else
		if (str == "unfiltered")
			filtInfo = unfiltered;
		else
			throw;
}

Beer::~Beer(){
}

string Beer::getFilt() const{
	switch (filtInfo){
	case Beer::filtered:
		return string("filtered");
	case Beer::unfiltered:
		return  string("unfiltered");
	}
}

Wine::Wine(string aname, double acap, double stur, string str) : Tipple(aname, acap, stur){
	if (str == "white")
		color = white;
	else
		if (str == "red")
			color = red;
		else
			throw;
}

Wine::~Wine(){
}

string Wine::getColor() const{
	switch (color) {
	case Wine::white:
		return string("white");
	case Wine::red:
		return  string("red");
	}
}
