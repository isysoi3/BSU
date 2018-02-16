#pragma once
#include <string>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

class SayClass{

private:
	string word;
	int repeat, delay;

public:
	static int TotalRepeats;
	static mutex mtx;
	SayClass(string s, int r, int d);
	virtual ~SayClass();
	void Say();
};

