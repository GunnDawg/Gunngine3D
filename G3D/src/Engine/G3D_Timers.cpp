#include "G3D_Timers.h"

namespace G3D
{
	internal bool
	DeltaClockInitialize(G3D::Delta_Clock* clock)
	{
		if (!QueryPerformanceFrequency(&clock->PerfCountFrequencyResult))
			return false;
		clock->PerfCountFrequency = clock->PerfCountFrequencyResult.QuadPart;

		if (!QueryPerformanceCounter(&clock->LastCounter))
			return false;
		clock->LastCycleCount = __rdtsc();

		return true;
	}

	internal void
	DeltaClockTick(G3D::Delta_Clock* clock)
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
	DeltaClockReset(G3D::Delta_Clock* clock)
	{
		clock->LastCounter = clock->EndCounter;
		clock->LastCycleCount = clock->EndCycleCount;
	}
}