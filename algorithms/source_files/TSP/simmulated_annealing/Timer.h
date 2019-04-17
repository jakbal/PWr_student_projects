#pragma once
#include <Windows.h>

class Timer
{
public:
	Timer();

	void startTimer();
	float getTime();
	int getIntTime();
	void resetTimer();

	~Timer();

private:
	long long int frequency;
	long long int start;
	float time;

	long long int read_QPC();
};

