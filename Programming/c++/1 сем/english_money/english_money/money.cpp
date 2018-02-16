#include "Money.h"

#include <iostream>
using namespace std;

Money::Money(long long pen) {
	if (abs(pen) >  480000000000)
		throw exception("operation failed");
	else
		halfPence = pen;
}

Money::Money(long int pound, int shilling, double pence){

	if (pound < 0 || shilling < 0 || pence < 0)
		throw invalid_argument("negative amount of money");
	if (shilling >= 20)
		throw invalid_argument("shillings >= 20");
	if (pence >= 12)
		throw invalid_argument("pences >= 12");	
	if (pence * 2 - int(pence * 2) != 0)
		throw invalid_argument("It is not a half");
	halfPence = 0;
	halfPence = (long long)pound * 480 + shilling * 24 + pence * 2;
	if (halfPence > 480000000000) 
		throw invalid_argument("money > one billion");

}

Money::~Money(){
}

void Money::getMoney() const {
	long pound = halfPence / 480;
	int shilling = (halfPence % 480) / 24;
	double pence = ((halfPence % 480) % 24) / 2.0;

	if (halfPence < 0){
		shilling = -shilling;
		pence = -pence;
	}
	if (pound != 0)
		cout << pound << "pd.";
	if (shilling != 0)
		cout << shilling << "sh.";
	if (pence != 0)
		cout << pence << "p.";
	else 
		if (pound == 0 && shilling == 0)
			cout << pence << "p.";
	cout << endl;
}

Money Money::operator + (const Money& other) const{
	return Money(halfPence + other.halfPence);
}
																					   
Money Money::operator - (const Money& other) const {
	return Money(halfPence - other.halfPence);
}

Money Money::operator - () const {
	return Money(-halfPence);
}

Money& Money::operator += (const Money& other){
	halfPence += other.halfPence;
	return *this;
}

Money& Money::operator -= (const Money& other){
	return *this += (-other);
	//halfPence += other.halfPence;
	//return *this;
}

bool Money::operator == (const Money& other) const{
	return (halfPence == other.halfPence);
}

bool Money::operator != (const Money& other) const{
	return (!this->operator==(other));
}

bool Money::operator <= (const Money& other) const{
	return (halfPence <= other.halfPence);

}

bool Money:: operator >= (const Money&other) const{
	return (halfPence >= other.halfPence);
}

bool Money::operator < (const Money& other) const{
	return !(this->operator>=(other));
}

bool Money::operator > (const Money& other) const{
	return !(this->operator<=(other));
}
