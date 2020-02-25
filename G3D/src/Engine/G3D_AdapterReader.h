#pragma once
#include <vector>

struct AdapterData
{
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* Adapter = 0;
	DXGI_ADAPTER_DESC Description = { 0 };
};

class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapters();

private:
	inline static std::vector<AdapterData> Adapters;
};