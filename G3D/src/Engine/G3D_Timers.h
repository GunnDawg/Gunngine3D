#pragma once

namespace G3D
{
#ifdef _WIN64
	struct DeltaClock
	{
		bool Initialize();
		void Tick();
		void Reset();

		LARGE_INTEGER PerfCountFrequencyResult;
		INT64 PerfCountFrequency = 0;
		LARGE_INTEGER LastCounter;
		UINT64 EndCycleCount = 0u;
		LARGE_INTEGER EndCounter;
		UINT64 LastCycleCount = 0u;
		UINT64 CyclesElapsed = 0u;
		INT64 TimeElapsed = 0;
		float MSPerFrame = 0.0f;
		float FPS = 0.0f;
		float MCPF = 0.0f;
	};
#elif __APPLE__
	struct DeltaClock
	{

	};
#elif __linux__
	struct DeltaClock
	{

	};
#endif
}