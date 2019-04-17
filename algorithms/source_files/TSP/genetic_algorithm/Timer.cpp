#include "Timer.h"



Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = 0;
	time = 0;
}


void Timer::startTimer()
{
	start = read_QPC();
}

float Timer::getTime()
{
	if (start != 0) {
		long long int temp = read_QPC() - start; //czas kt鏎y up造n像 od wystartowania licznika
		time = (float)temp / frequency;			 //obliczenie czasu [time] podawanego w sekundach
	}

	return time;
}

int Timer::getIntTime()
{
	if (start != 0) {
		long long int temp = read_QPC() - start; //czas kt鏎y up造n像 od wystartowania licznika
		time = temp / frequency;			 //obliczenie czasu [time] podawanego w sekundach
	}

	return time;
}

void Timer::resetTimer()
{
	start = 0;
	time = 0;
}


Timer::~Timer()
{
}


long long int Timer::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}
