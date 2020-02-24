#include "G3D_Timers.h"

internal void
DeltaClockInit(delta_clock* clock)
{
	QueryPerformanceFrequency(&clock->PerfCountFrequencyResult);
	clock->PerfCountFrequency = clock->PerfCountFrequencyResult.QuadPart;

	QueryPerformanceCounter(&clock->LastCounter);
	clock->LastCycleCount = __rdtsc();
}

internal void
DeltaClockTick(delta_clock* clock)
{
	clock->EndCycleCount = __rdtsc();
	QueryPerformanceCounter(&clock->EndCounter);

	clock->CyclesElapsed = clock->EndCycleCount - clock->LastCycleCount;
	clock->TimeElapsed = clock->EndCounter.QuadPart - clock->LastCounter.QuadPart;
	clock->MSPerFrame = ((1000.0f * clock->TimeElapsed) / (float)clock->PerfCountFrequency);
	clock->FPS = (float)clock->PerfCountFrequency / (float)clock->TimeElapsed;
	clock->MCPF = (float)clock->CyclesElapsed / (1000.0f * 1000.0f);
}

internal void
DeltaClockReset(delta_clock* clock)
{
	clock->LastCounter = clock->EndCounter;
	clock->LastCycleCount = clock->EndCycleCount;
}