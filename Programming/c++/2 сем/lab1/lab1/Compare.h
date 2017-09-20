#pragma once
#include <set>

using namespace std;

class Compare {
private :
	int counter(string str) const;
public:
	bool operator() (string s1, string s2) const;
};
										