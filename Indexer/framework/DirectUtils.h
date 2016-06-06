#include <d3d11.h>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>

class Utils
{
public:
	static void COMRelease(IUnknown* comObject);
	static void DI8DeviceRelease(IDirectInputDevice8W* device);

	template<typename T>
	static void DeleteArray(T* arrayPtr)
	{
		if (arrayPtr != nullptr)
			delete[] arrayPtr;
	}

	static void* New16Aligned(size_t size);
	static void Delete16Aligned(void* ptr);
};