#pragma once
#include <string>

using namespace std;

class Drink{
private:
	double capacity;
	string name;
public:
	Drink(string aname, double acap);
	virtual ~Drink();
	virtual string getName() const;
	virtual double getCapacity() const ;
	virtual void dummy() = 0;
};

///////////////////////////////////////////////////////

class Soft_Drink: public Drink{
private:
	/////
public:
	Soft_Drink(string aname, double acap);
	~Soft_Drink();
	virtual void dummy() = 0;
};

class Milk : public Soft_Drink {
private:
	double fatness;
public:
	Milk(string aname, double acap, double afat);
	//написать еще конструктр
	~Milk();
	double getFatness() const;
	virtual void dummy() {};
};

class Lemonade : public Soft_Drink {
private:
	enum color {red, green, yellow, white};
	color colorOFdrink;
public:
	Lemonade(string aname, double acap, string col);
	//написать еще конструктр
	~Lemonade();
	string getColor() const;
	virtual void dummy() {};
};

class Mineral_Water : public Soft_Drink {
private:
	enum TheNumberOfGas {strong, middling, weakly, without};
	TheNumberOfGas gas;
public:
	Mineral_Water(string aname, double acap, string str);
	~Mineral_Water();
	string getGas() const;
	virtual void dummy() {};
};

////////////////////////////////////////

class Tipple : public Drink {
private:
	double sturdiness;
public:
	Tipple(string aname, double acap, double stur);
	~Tipple();
	virtual double getSturdiness() const ;
	virtual void dummy() = 0;
};

class Cognac : public Tipple{
private:
	int excerptInDays;
public:
	Cognac(string aname,double acap ,double stur, int days);
	~Cognac();
	int getExcert() const;
	void setExcert(int days);
	virtual void dummy(){};
};

class Beer : public Tipple {
private:
	enum cleaning {filtered, unfiltered};
	cleaning filtInfo;
public:
	Beer(string aname, double acap, double stur, string str);
	~Beer();
	string getFilt() const;
	virtual void dummy(){};
};

class Wine : public Tipple {
private:
	enum wColor { red, white };
	wColor color;
public:
	Wine(string aname, double acap, double stur, string str);
	~Wine();
	string getColor() const;
	virtual void dummy() {};
};