#include "G3D_AdapterReader.h"

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (Adapters.size() > 0)
		return Adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

	//Create DXGIFactory Object
	HRESULT Result = 0;
	Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
	if (FAILED(Result))
	{
		//(TODO): Error Logging.
	}

	Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		Adapters.emplace_back(AdapterData(pAdapter.Get()));
		index += 1;
	}

	return Adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	Adapter = pAdapter;
	HRESULT Result = 0;
	Result = pAdapter->GetDesc(&Description);
	if (FAILED(Result))
	{
		//(TODO): Error Logging.
	}
}