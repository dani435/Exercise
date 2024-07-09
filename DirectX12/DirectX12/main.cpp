#include <dxgi1_4.h>
#include <d3d12.h>

#include <iostream>
#include <vector>
#include <string>

#include <comdef.h>

#define COMPTR(x, y) __uuidof(x), reinterpret_cast<void**>(&y)

#define COMCHECK(x) {\
	HRESULT result = x;\
	if (result != S_OK)\
	{\
		_com_error err(result);\
		OutputDebugStringW((L"Error: " + std::wstring(err.ErrorMessage()) + L"\n").c_str());\
		throw std::exception();\
	}\
}

namespace aiv
{
	ID3D12Resource* create_buffer(ID3D12Device* device, const UINT64 size, const D3D12_HEAP_TYPE heap_type)
	{
		ID3D12Resource* resource = nullptr;
		D3D12_HEAP_PROPERTIES heap_properties = {};
		heap_properties.Type = heap_type;

		D3D12_RESOURCE_DESC resource_desc = {};
		resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resource_desc.Width = size;
		resource_desc.Height = 1;
		resource_desc.DepthOrArraySize = 1;
		resource_desc.MipLevels = 1;
		resource_desc.SampleDesc.Count = 1;
		resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		D3D12_RESOURCE_ALLOCATION_INFO allocation_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);

		COMCHECK(device->CreateCommittedResource(&heap_properties,
			D3D12_HEAP_FLAG_NONE,
			&resource_desc,
			heap_type == D3D12_HEAP_TYPE_READBACK ? D3D12_RESOURCE_STATE_COPY_DEST : D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			COMPTR(ID3D12Resource, resource)));

		return resource;
	}
}

int main(int argc, char** argv)
{

	IDXGIFactory* factory = nullptr;
	COMCHECK(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, COMPTR(IDXGIFactory, factory)));

	IDXGIFactory2* factory2 = nullptr;
	COMCHECK(factory->QueryInterface<IDXGIFactory2>(&factory2));

	UINT adapter_index = 0;
	IDXGIAdapter1* adapter = nullptr;
	std::vector<IDXGIAdapter1*> adapters;
	for (;;)
	{
		adapter = nullptr;
		if (factory2->EnumAdapters1(adapter_index, &adapter) != S_OK)
		{
			break;
		}

		adapters.push_back(adapter);

		adapter_index++;
	}

	for (IDXGIAdapter1* current_adapter : adapters)
	{
		DXGI_ADAPTER_DESC1 adapter_desc;
		current_adapter->GetDesc1(&adapter_desc);
		std::wcout << adapter_desc.Description << " " << adapter_desc.DedicatedVideoMemory / 1024 / 1024 << std::endl;
	}

	IDXGIAdapter1* best_adapter = adapters[0];

	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(COMPTR(ID3D12Debug, debug));
	debug->EnableDebugLayer();

	ID3D12Device* device = nullptr;
	COMCHECK(D3D12CreateDevice(best_adapter, D3D_FEATURE_LEVEL_12_0, COMPTR(ID3D12Device, device)));

	std::cout << "Number of GPU nodes: " << device->GetNodeCount() << std::endl;

	ID3D12Resource* default_buffer = aiv::create_buffer(device, 64, D3D12_HEAP_TYPE_DEFAULT);
	ID3D12Resource* upload_buffer = aiv::create_buffer(device, 64, D3D12_HEAP_TYPE_UPLOAD);
	ID3D12Resource* readback_buffer = aiv::create_buffer(device, 64, D3D12_HEAP_TYPE_READBACK);

	ID3D12CommandQueue* queue;
	D3D12_COMMAND_QUEUE_DESC queue_desc = {};
	queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	COMCHECK(device->CreateCommandQueue(&queue_desc, COMPTR(ID3D12CommandQueue, queue)));

	ID3D12Fence1* fence;
	COMCHECK(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, COMPTR(ID3D12Fence1, fence)));

	HANDLE fence_event = CreateEvent(NULL, FALSE, FALSE, NULL);

	uint8_t* data;
	COMCHECK(upload_buffer->Map(0, nullptr, reinterpret_cast<void**>(&data)));

	data[0] = 100;
	data[1] = 101;
	data[2] = 102;
	data[3] = 103;

	upload_buffer->Unmap(0, nullptr);

	ID3D12CommandAllocator* command_allocator;
	COMCHECK(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, COMPTR(ID3D12CommandAllocator, command_allocator)));

	ID3D12GraphicsCommandList* command_list;
	COMCHECK(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, nullptr, COMPTR(ID3D12GraphicsCommandList, command_list)));

	command_list->CopyResource(default_buffer, upload_buffer);

	command_list->Close();

	queue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList**>(&command_list));

	queue->Signal(fence, 1);
	fence->SetEventOnCompletion(1, fence_event);

	/*for (;;)
	{
		std::cout << fence->GetCompletedValue();
	}*/

	WaitForSingleObject(fence_event, INFINITE);


	D3D12_ROOT_PARAMETER1 param0 = {};
	param0.ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
	param0.Descriptor.ShaderRegister = 0;

	D3D12_VERSIONED_ROOT_SIGNATURE_DESC versioned_root_desc = {};
	versioned_root_desc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
	versioned_root_desc.Desc_1_1.NumParameters = 1;
	versioned_root_desc.Desc_1_1.pParameters = &param0;

	ID3DBlob* serialized_root_signature;
	COMCHECK(D3D12SerializeVersionedRootSignature(&versioned_root_desc, &serialized_root_signature, nullptr));

	ID3D12RootSignature* root_signature;
	COMCHECK(device->CreateRootSignature(0,
		serialized_root_signature->GetBufferPointer(),
		serialized_root_signature->GetBufferSize(), COMPTR(ID3D12RootSignature, root_signature)));

	D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc = {};
	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descriptor_heap_desc.NumDescriptors = 1;

	ID3D12DescriptorHeap* descriptor_heap;
	COMCHECK(device->CreateDescriptorHeap(&descriptor_heap_desc, COMPTR(ID3D12DescriptorHeap, descriptor_heap)));

	UINT descriptor_heap_increment = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	D3D12_UNORDERED_ACCESS_VIEW_DESC uav_desc = {};
	uav_desc.Format = DXGI_FORMAT_R32_UINT;
	uav_desc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uav_desc.Buffer.NumElements = 64 / 4;

	D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle = descriptor_heap->GetCPUDescriptorHandleForHeapStart();

	//cpu_handle.ptr += descriptor_heap_increment;

	device->CreateUnorderedAccessView(default_buffer, nullptr, &uav_desc, cpu_handle);

	/*
	RWBuffer<uint> target0;

	[numthreads(1, 1, 1)]
	void main()
	{
		target0[0] *= 2;
	}

	*/

	command_allocator->Reset();
	command_list->Reset(command_allocator, nullptr);

	command_list->CopyResource(readback_buffer, default_buffer);

	command_list->Close();

	queue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList**>(&command_list));

	queue->Signal(fence, 2);
	fence->SetEventOnCompletion(2, fence_event);

	WaitForSingleObject(fence_event, INFINITE);

	uint8_t* readback_data;
	COMCHECK(readback_buffer->Map(0, nullptr, reinterpret_cast<void**>(&readback_data)));

	std::cout << "task done " << readback_data[0] << " " << readback_data[1] << " " << readback_data[2] << " " << readback_data[3] << std::endl;

	readback_buffer->Unmap(0, nullptr);

	getchar();

	return 0;
}