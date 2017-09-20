#pragma once
#include "Drink.h"

using namespace std;

class Tipple : public Drink {
private:
	double sturdiness;
	virtual void dummy() = 0;
public:
	Tipple(string aname, double avol, double stur);
	~Tipple();
	virtual double getSturdiness() const;
};

class Cognac : public Tipple {
private:
	const int excerptInYears;
	virtual void dummy() {};
public:
	Cognac(string aname, double avol, double stur, int years);
	~Cognac();
	int getExcert() const;
};

enum cleaning { filtered, unfiltered };

class Beer : public Tipple {
private:
	const cleaning filtInfo;
	virtual void dummy() {};
public:
	Beer(string aname, double avol, double stur, cleaning filt);
	~Beer();
	string getFilt() const;
	//clearing getFilt()
};

enum Color { red, white };

class Wine : public Tipple {
private:
	const Color color;
	virtual void dummy() {};
public:
	Wine(string aname, double avol, double stur, Color col);
	~Wine();
	string getColor() const;
};

