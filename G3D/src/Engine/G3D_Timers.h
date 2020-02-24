#pragma once
#include "G3D_Windows.h"

struct delta_clock
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

void DeltaClockInit(delta_clock* clock);
void DeltaClockTick(delta_clock* clock);
void DeltaClockReset(delta_clock* clock);