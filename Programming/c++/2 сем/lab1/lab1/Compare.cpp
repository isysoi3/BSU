#include "Compare.h"


int Compare::counter(string str) const{
	set<char> symbols(str.begin(), str.end());
	return symbols.size();
}

bool Compare::operator()(string s1, string s2) const{
	return counter(s1) > counter(s2);
}
