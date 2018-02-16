#pragma once
#include <string>

using namespace std;

class Drink {
private:
	double volume;
	string name;
	virtual void dummy() = 0;
public:
	Drink(string aname, double acap);
	virtual ~Drink();
	virtual string getName() const;
	virtual double getVolume() const;
};
