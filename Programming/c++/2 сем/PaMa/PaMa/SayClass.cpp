#include "SayClass.h"
#include <iostream>

int SayClass::TotalRepeats = 0;
mutex SayClass::mtx;

SayClass::SayClass(string s, int r, int d)
{
	word = s;
	repeat = r;
	delay = d;
}


SayClass::~SayClass()
{
}

void SayClass::Say() {
	for (int i = 0; i < repeat; i++) {
		this_thread::sleep_for(chrono::milliseconds(delay));
		lock_guard<mutex> lck(mtx);
		if (TotalRepeats > 0)
		{
			TotalRepeats--;
		}
		else
			break;
		cout << word + " ";
	}
}
