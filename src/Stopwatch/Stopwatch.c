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

Stopwatch StopwatchCreate( void)
{
	Stopwatch stopwatch;
	memset( &stopwatch, 0, sizeof(Stopwatch));
	
#ifdef _WIN32
	QueryPerformanceFrequency( (LARGE_INTEGER*)&stopwatch.Frequency);
#endif

	return stopwatch;
}

void StopwatchDestroy( Stopwatch* stopwatch)
{
	memset( stopwatch, 0, sizeof(Stopwatch));
}

void StopwatchStart( Stopwatch* stopwatch)
{
#ifdef _WIN32
	QueryPerformanceCounter( (LARGE_INTEGER*)&stopwatch->StartTime);
#endif
}

void StopwatchStop( Stopwatch* stopwatch)
{
#ifdef _WIN32
	QueryPerformanceCounter( (LARGE_INTEGER*)&stopwatch->EndTime);
	stopwatch->IntervalInSeconds = (double)(stopwatch->EndTime - stopwatch->StartTime) / stopwatch->Frequency;
#endif
}

double StopwatchGetIntervalInSeconds( Stopwatch* stopwatch)
{
	return stopwatch->IntervalInSeconds;
}