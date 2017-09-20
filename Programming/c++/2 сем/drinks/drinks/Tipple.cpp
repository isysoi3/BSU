#include "Tipple.h"



Tipple::Tipple(string aname, double avol, double stur) : Drink(aname, avol) {
	if (stur < 0 || stur > 100)
		throw exception("Sturdiness is incorrect");
	sturdiness = stur;
}

Tipple::~Tipple() {
}

double Tipple::getSturdiness() const {
	return sturdiness;
}

Cognac::Cognac(string aname, double avol, double stur, int years) : Tipple(aname, avol, stur), excerptInYears(years) {
}

Cognac::~Cognac() {
}

int Cognac::getExcert() const {
	return excerptInYears;
}

Beer::Beer(string aname, double avol, double stur, cleaning filt) : Tipple(aname, avol, stur), filtInfo(filt) {
}

Beer::~Beer() {
}

string Beer::getFilt() const {
	switch (filtInfo) {
	case filtered:
		return string("filtered");
	case unfiltered:
		return  string("unfiltered");
	}
}

Wine::Wine(string aname, double avol, double stur, Color col) : Tipple(aname, avol, stur), color(col) {
}

Wine::~Wine() {
}

string Wine::getColor() const {
	switch (color) {
	case red:
		return  string("red");
	case white:
		return string("white");
	}
}

