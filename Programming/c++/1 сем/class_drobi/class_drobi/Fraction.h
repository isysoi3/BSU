#pragma once

class Fraction{
private:
	long numerator;
	long denomirator;
	void reduce();
	void setDen(long);
	void setNum(long);
public:
	Fraction(long = 1, long = 1);
	virtual ~Fraction();
	long getNumerator() const;
	long getDenominator() const;
	void setNumerator(long);
	void setDenominator(long);
	double getValue() const;
	Fraction operator + (const Fraction&) const;
	Fraction operator - (const Fraction&) const;
	Fraction operator * (const Fraction&) const;
	Fraction operator / (const Fraction&) const;
	Fraction operator - () const;
	
};
