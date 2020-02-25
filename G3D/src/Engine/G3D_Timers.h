#pragma once

namespace G3D
{
	struct Delta_Clock
	{
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

	bool DeltaClockInitialize(G3D::Delta_Clock* clock);
	void DeltaClockTick(G3D::Delta_Clock* clock);
	void DeltaClockReset(G3D::Delta_Clock* clock);
}