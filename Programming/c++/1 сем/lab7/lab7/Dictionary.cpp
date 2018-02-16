#include "Dictionary.h"

Dictionary::Dictionary() {
}
Dictionary::Dictionary(map<string, string> trans) {
	dictionary.insert(trans.begin(), trans.end());
}
									
Dictionary::~Dictionary() {
}

string Dictionary::getWord(string en) {
	it = dictionary.find(en);
	if (it != dictionary.end())
		return string(it->first + " - " + it->second);
	else
		return string("Translation is not found");
}

int Dictionary::getSize() const {
	return dictionary.size();
}

void Dictionary::setWord(string en, string rus){
	it = dictionary.find(en);
	if (it != dictionary.end()) {
		dictionary.at(en)= rus;
	}
}

void Dictionary::insertWord(string en, string rus)  {
	dictionary.insert(pair<string, string>(en, rus));
}

void Dictionary::deleteWord(string en) {
	dictionary.erase(en);
}

ostream& operator << (ostream& out,const Dictionary& other){
	for (auto it = other.dictionary.begin(); it != other.dictionary.end(); ++it){
		out << it->first << " - " << it->second << '\n';
	}
	return out;
}

istream& operator >> (istream& in, Dictionary& other){
	string str, str1;
	cin >> str >> str1;
	other.dictionary.insert(pair<string, string>(str, str1));
	return in;
}

Dictionary Dictionary::operator+(const Dictionary& other) const {
	map<string, string> buf;
	buf.insert(dictionary.begin(),dictionary.end());
	buf.insert(other.dictionary.begin(), other.dictionary.end());
	return Dictionary(buf);
}

Dictionary Dictionary::operator = (const Dictionary &other) {
	dictionary.clear();
	dictionary.insert(other.dictionary.begin(),other.dictionary.end());
	return Dictionary(dictionary);
}
