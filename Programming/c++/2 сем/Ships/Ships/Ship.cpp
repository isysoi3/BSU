#include "Ship.h"

int Ship::curr_id = 0;

Ship::Ship(string aname) : id(++curr_id) {
	name = aname;
}

Ship::~Ship()
{
}

int Ship::getID(){
	return id;
}

string Ship::getName(){
	return string(name);
}
