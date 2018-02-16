#pragma once
class Money{
private:
	long long halfPence;
	Money(long long);
public:
	Money(long int = 0, int = 0, double = 0);
	~Money();
	void getMoney() const;
	Money operator + (const Money&) const;
	Money operator - (const Money&) const;
	Money operator - () const;
	Money& operator += (const Money&);
	Money& operator -= (const Money&);
	bool operator < (const Money&) const;
	bool operator > (const Money&) const;
	bool operator == (const Money&) const;
	bool operator != (const Money&) const;
	bool operator <= (const Money&) const;
	bool operator >= (const Money&) const;
};