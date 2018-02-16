#pragma once
#include  "Drink.h"

using namespace std;

class Soft_Drink : public Drink {
protected:

public:
	Soft_Drink();
	~Soft_Drink();
	virtual string getName() const = 0;
	virtual double getCapacity() const = 0;
};

class Milk : public Soft_Drink {
private:
	double fatness;
public:
	Milk(string aname, double acap, double afat);
	//написать еще конструктр
	~Milk();
	virtual string getName() const;
	virtual double getCapacity() const;
	double getFatness() const;
};

class Lemonade : public Soft_Drink {
private:
	enum asort { original, buratino, duchess, soda };
	asort sort;
public:
	Lemonade(string aname, double acap, string sortOFdrink);
	~Lemonade();
	virtual string getName() const;
	virtual double getCapacity() const;
	string getSort() const;
};

class Mineral_Water : public Soft_Drink {
private:
	enum TheNumberOfGas { strong, middling, weakly, without };
	TheNumberOfGas gas;
public:
	Mineral_Water(string aname, double acap, string str);
	~Mineral_Water();
	virtual string getName() const;
	virtual double getCapacity() const;
	string getGas() const;
};