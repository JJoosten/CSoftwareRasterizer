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


Stopwatch Stopwatch_Init( void);
void Stopwatch_Start( Stopwatch* stopwatch);
void Stopwatch_Stop( Stopwatch* stopwatch);
void Stopwatch_Reset( Stopwatch* stopwatch);
double Stopwatch_GetIntervalInSeconds( Stopwatch* stopwatch);

#endif // CSR_STOPWATCH_H