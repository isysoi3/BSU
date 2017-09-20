#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Dictionary {
private:
	map<string, string> dictionary;
	map<string, string>::iterator it;
	Dictionary(map<string, string>);
public:
	Dictionary();
	virtual ~Dictionary();
	string getWord(string);
	int getSize() const;
	void setWord(string, string);
	void insertWord(string, string);
	void deleteWord(string);
	friend ostream& operator << (ostream& out, const Dictionary&);
	friend istream& operator >> (istream& in, Dictionary&);
	Dictionary operator + (const Dictionary&) const;
	Dictionary operator = (const Dictionary&) ;
};