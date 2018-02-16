#pragma once
#include "Drink.h"
using namespace std;


class Soft_Drink : public Drink {
private:
	virtual void dummy() = 0;
public:
	Soft_Drink(string aname, double avol);
	virtual ~Soft_Drink();
};

class Milk : public Soft_Drink {
private:
	double fatness;
	virtual void dummy() {};
public:
	Milk(string aname, double avol, double afat);
	~Milk();
	double getFatness() const;
};

enum Additive { apple, pear, orange };

class Lemonade : public Soft_Drink {
private:
	const Additive additive;
	virtual void dummy() {};
public:
	Lemonade(string aname, double avol, Additive add);
	~Lemonade();
	string getAdd() const;
};

enum TheNumberOfGas { strong, middling, without };

class Mineral_Water : public Soft_Drink {
private:
	TheNumberOfGas gas;
	virtual void dummy() {};
public:
	Mineral_Water(string aname, double avol, TheNumberOfGas gs);
	~Mineral_Water();
	string getGas() const;
};
