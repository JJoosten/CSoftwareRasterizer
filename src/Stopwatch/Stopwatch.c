#include "Stopwatch.h"
#include <string.h>

// TODO: make this thread safe!

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define WIN32_EXTRA_LEAN
	#include <windows.h>
#else
	#error No other performance counter is implemented
#endif



Stopwatch Stopwatch_Init( void)
{
	Stopwatch stopwatch;
	memset( &stopwatch, 0, sizeof(Stopwatch));
	
#ifdef _WIN32
	QueryPerformanceFrequency( (LARGE_INTEGER*)&stopwatch.Frequency);
#else
	// add support for linux and mac
#endif

	return stopwatch;
}

void Stopwatch_Start( Stopwatch* stopwatch)
{
#ifdef _WIN32
	QueryPerformanceCounter( (LARGE_INTEGER*)&stopwatch->StartTime);
#else
	// add support for linux and mac
#endif
}

void Stopwatch_Stop( Stopwatch* stopwatch)
{
#ifdef _WIN32
	QueryPerformanceCounter( (LARGE_INTEGER*)&stopwatch->EndTime);
	stopwatch->IntervalInSeconds = (double)(stopwatch->EndTime - stopwatch->StartTime) / stopwatch->Frequency;
#else
	// add support for linux and mac
#endif
}

void Stopwatch_Reset( Stopwatch* stopwatch)
{
	stopwatch->StartTime = 0;
	stopwatch->EndTime = 0;
	stopwatch->IntervalInSeconds = 0;
}

double Stopwatch_GetIntervalInSeconds( Stopwatch* stopwatch)
{
	return stopwatch->IntervalInSeconds;
}