#include "G3D_Timers.h"

namespace G3D
{
	bool PerformanceClock::Initialize()
	{
		if (!QueryPerformanceFrequency(&PerfCountFrequencyResult))
			return G3D_ERROR;

		PerfCountFrequency = PerfCountFrequencyResult.QuadPart;

		if (!QueryPerformanceCounter(&LastCounter))
			return G3D_ERROR;

		LastCycleCount = __rdtsc();

		return G3D_OK;
	}

	void PerformanceClock::Tick()
	{
		EndCycleCount = __rdtsc();
		QueryPerformanceCounter(&EndCounter);

		CyclesElapsed = EndCycleCount - LastCycleCount;
		TimeElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
		MSPerFrame = ((1000.0f * TimeElapsed) / static_cast<float>(PerfCountFrequency));
		FPS = static_cast<float>(PerfCountFrequency) / static_cast<float>(TimeElapsed);
		MCPF = static_cast<float>(CyclesElapsed) / (1000.0f * 1000.0f);
		DeltaTime = MSPerFrame;

		LastCounter = EndCounter;
		LastCycleCount = EndCycleCount;
	}

	//TIMER STUFF
	Timer::Timer() noexcept
	{
		last = std::chrono::steady_clock::now();
	}

	float G3D::Timer::Mark() noexcept
	{
		const auto old = last;
		last = std::chrono::steady_clock::now();
		const std::chrono::duration<float> frameTime = last - old;
		return frameTime.count();
	}
}