#include "G3D_Timers.h"

namespace G3D
{
	bool DeltaClock::Initialize()
	{
		if (!QueryPerformanceFrequency(&PerfCountFrequencyResult))
			return false;

		PerfCountFrequency = PerfCountFrequencyResult.QuadPart;

		if (!QueryPerformanceCounter(&LastCounter))
			return false;

		LastCycleCount = __rdtsc();

		return true;
	}

	void DeltaClock::Tick()
	{
		EndCycleCount = __rdtsc();
		QueryPerformanceCounter(&EndCounter);

		CyclesElapsed = EndCycleCount - LastCycleCount;
		TimeElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
		MSPerFrame = ((1000.0f * TimeElapsed) / (float)PerfCountFrequency);
		FPS = (float)PerfCountFrequency / (float)TimeElapsed;
		MCPF = (float)CyclesElapsed / (1000.0f * 1000.0f);
	}

	void DeltaClock::Reset()
	{
		LastCounter = EndCounter;
		LastCycleCount = EndCycleCount;
	}
}