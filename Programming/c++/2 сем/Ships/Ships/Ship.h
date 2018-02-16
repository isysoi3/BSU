#pragma once
#include <string>

using namespace std;

class Ship{
private:
	string name;
	const int id;
	static int curr_id;
public:
	Ship(string aname);
	Ship();
	virtual ~Ship();
	int getID();
	string getName();
};

