#include <iostream>
using namespace std;
#include "Fraction.h"

int main(){
								
	Fraction *frac = nullptr; 
	Fraction *frac1 = nullptr ; 
	Fraction *rez = nullptr ;
	try { 
		frac = new Fraction(2,-3); 
		frac1 = new Fraction(1,3); 
		rez = new Fraction;
		*rez = (*frac) + (*frac1);
		cout << rez->getValue() << endl;
		*rez = (*frac) - (*frac1);	  
		cout << rez->getValue() << endl;
		*rez = (*frac) * (*frac1);
		cout << rez->getValue() << endl;
		*rez = (*frac) / (*frac1);
		cout << rez->getValue() << endl;
		cout << frac->getNumerator() << "/" << frac->getDenominator() << endl;
	} 
	catch (const exception& e) { 
		cout << e.what() << endl;
	}

	delete rez;
	delete frac;
	delete frac1;
	
	return 0;
}

		