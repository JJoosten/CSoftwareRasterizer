#ifndef CSR_STOPWATCH_H
#define CSR_STOPWATCH_H

typedef struct sStopwatch
{
	unsigned long long StartTime;
	unsigned long long EndTime;
	double IntervalInSeconds;
#ifdef _WIN32
	unsigned long long Frequency;
#endif
} Stopwatch;


Stopwatch StopwatchCreate( void);
void StopwatchDestroy( Stopwatch* stopwatch);
void StopwatchStart( Stopwatch* stopwatch);
void StopwatchStop( Stopwatch* stopwatch);
double StopwatchGetIntervalInSeconds( Stopwatch* stopwatch);

#endif // CSR_STOPWATCH_H