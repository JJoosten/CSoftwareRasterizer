#ifndef CSR_STOPWATCH_H
#define CSR_STOPWATCH_H

typedef struct
{
	unsigned long long StartTime;
	unsigned long long EndTime;
	double IntervalInSeconds;
#ifdef _WIN32
	unsigned long long Frequency;
#endif
} Stopwatch;


void Stopwatch_Init( Stopwatch* const stopwatch);
void Stopwatch_Start( Stopwatch* const stopwatch);
void Stopwatch_Stop( Stopwatch* const stopwatch);
void Stopwatch_Reset( Stopwatch* const stopwatch);
double Stopwatch_GetIntervalInSeconds( Stopwatch* const stopwatch);

#endif // CSR_STOPWATCH_H