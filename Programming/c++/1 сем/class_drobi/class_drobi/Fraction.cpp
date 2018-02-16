#include "Fraction.h"
#include <cmath>
#include <exception>


void Fraction::reduce(){
	if (numerator != 0) {
		long x = abs(numerator);
		long y = denomirator;
		while (x != y) {
			if (x > y)
				x -= y;
			else
				y -= x;
		}
		numerator /= x;
		denomirator /= x;
	}
}

Fraction::Fraction(long num, long den){
	setNum(num);
	setDen(den);
	reduce();
}

Fraction::~Fraction(){
}

long Fraction::getNumerator() const{
	return numerator;
}

long Fraction::getDenominator() const{
	return denomirator;
}

void Fraction::setNumerator(long numb){
	setNum(numb);
	reduce();
}

void Fraction::setDenominator(long numb){
	setDen(numb);
	reduce();
}

void Fraction::setNum(long smth) {
	numerator = smth;
}

void Fraction::setDen(long smth) {
	if (smth == 0)
		throw std::exception("Division by zero");
	if (smth < 0)
		throw std::exception("Denumerator < 0");
	denomirator = smth;
}

double Fraction::getValue() const{
	return (double)(numerator) / denomirator;
}
Fraction Fraction::operator + (const Fraction& other ) const{
	return Fraction(numerator * other.denomirator + denomirator * other.numerator, denomirator * other.denomirator);
}
Fraction Fraction::operator - (const Fraction& other) const{
	return Fraction(numerator * other.denomirator - denomirator * other.numerator, denomirator * other.denomirator);
}
Fraction Fraction::operator * (const Fraction& other) const{
	return Fraction(numerator * other.numerator, denomirator * other.denomirator);
}
Fraction Fraction::operator / (const Fraction& other) const{
	return Fraction(numerator * other.denomirator, denomirator * other.numerator);
}
Fraction Fraction::operator - () const{
	return Fraction(-numerator, denomirator);
}