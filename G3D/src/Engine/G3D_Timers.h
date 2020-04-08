#pragma once
#include <chrono>

namespace G3D
{
#ifdef _WIN64
	struct PerformanceClock
	{
		//@NOTE: Windows specific clock data here
		bool Initialize();
		void Tick();

		LARGE_INTEGER PerfCountFrequencyResult;
		LARGE_INTEGER LastCounter;
		LARGE_INTEGER EndCounter;
		INT64 PerfCountFrequency = 0;
		INT64 TimeElapsed = 0;
		UINT64 EndCycleCount = 0u;
		UINT64 LastCycleCount = 0u;
		UINT64 CyclesElapsed = 0u;
		float MSPerFrame = 0.0f;
		float FPS = 0.0f;
		float MCPF = 0.0f;
		float DeltaTime = 0.0f;
	};

	class Timer
	{
	public:
		Timer() noexcept;
		float Mark() noexcept;
		inline float Peek() const noexcept
		{
			return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
		}

	private:
		std::chrono::steady_clock::time_point last;
	};
#elif __APPLE__
	struct PerformanceClock
	{
		//@NOTE: Apple specific clock data here
	};
#elif __linux__
	struct PerformanceClock
	{
		//@NOTE: Linux specific clock data here
	};
#endif
}