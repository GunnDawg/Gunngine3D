#pragma once
#include <vector>

namespace G3D
{
	struct AdapterData
	{
		AdapterData(IDXGIAdapter* pAdapter);
		IDXGIAdapter* Adapter = 0;
		DXGI_ADAPTER_DESC Description = { 0 };
	};

	struct AdapterReader
	{
		static std::vector<AdapterData> GetAdapters();
		inline static std::vector<AdapterData> Adapters;
	};
}