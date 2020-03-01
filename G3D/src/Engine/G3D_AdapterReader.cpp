#include "G3D_AdapterReader.h"

namespace G3D
{
	AdapterData::AdapterData(IDXGIAdapter* pAdapter)
	{
		Adapter = pAdapter;
		HRESULT Result = 0;
		Result = pAdapter->GetDesc(&Description);
		if (FAILED(Result))
		{
			//(TODO): Error Logging.
		}

		SAFE_RELEASE(Adapter);
	}

	std::vector<AdapterData> AdapterReader::GetAdapters()
	{
		if (Adapters.size() > 0)
			return Adapters;

		IDXGIFactory* pFactory = 0;

		//Create DXGIFactory Object
		HRESULT Result = 0;
		Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
		if (FAILED(Result))
		{
			//(TODO): Error Logging.
		}

		IDXGIAdapter* pAdapter = 0;
		UINT index = 0;
		while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
		{
			Adapters.emplace_back(AdapterData(pAdapter));
			index += 1;
		}

		SAFE_RELEASE(pFactory);
		SAFE_RELEASE(pAdapter);

		return Adapters;
	}
}