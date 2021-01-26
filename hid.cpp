# include "hid.h"
# include "error.h"
HID<>::~HID(void)
{
	if(RAWINPUT && ASSERT(cbSize) && ASSERT(hDevice))
	{
		free(RAWINPUT), free(hDevice);
		RAWINPUTDEVICE.dwFlags = RIDEV_REMOVE;
		RegisterRawInputDevices(& RAWINPUTDEVICE, 1, sizeof RAWINPUTDEVICE);
	}
	memset(this, 0, sizeof(HID<>));
}
HID<>::HID(void): dwCount(0)
{ }
HID<>::HID(HWND hWnd, USHORT usUsagePage, USHORT usUsage, DWORD dwFlags): dwCount(0),
dwType(usUsagePage == 1 ? usUsage == 2 ? RIM_TYPEMOUSE : usUsage == 6 ? RIM_TYPEKEYBOARD : RIM_TYPEHID : RIM_TYPEHID)
{	
	UINT uiNumDevices = 0;
	GetRawInputDeviceList(nullptr, & uiNumDevices, sizeof(RAWINPUTDEVICELIST)); 
	RAWINPUTDEVICELIST *RAWINPUTDEVICELIST = new ::RAWINPUTDEVICELIST[uiNumDevices];
	UINT n = GetRawInputDeviceList(RAWINPUTDEVICELIST, & uiNumDevices, sizeof(::RAWINPUTDEVICELIST)); 
	for(UINT i = 0; i < n; ++ i)
	# pragma warning (suppress: 6385) // Reading invalid data from 'pRawInputDeviceList':
	// the readable size is 'uiNumDevices*8' bytes, but '16' bytes may be read.
	if(RAWINPUTDEVICELIST[i].dwType == dwType)
	{
		RID_DEVICE_INFO RID_DEVICE_INFO {0};
		UINT cbSize = sizeof RID_DEVICE_INFO;
		# pragma warning(suppress: 6385)
		if(ASSERT(GetRawInputDeviceInfoA(RAWINPUTDEVICELIST[i].hDevice, RIDI_DEVICEINFO, & RID_DEVICE_INFO, & cbSize) == sizeof RID_DEVICE_INFO))
		if(dwType == RIM_TYPEMOUSE || dwType == RIM_TYPEKEYBOARD || RID_DEVICE_INFO.hid.usUsagePage == usUsagePage && RID_DEVICE_INFO.hid.usUsage == usUsage)
		{
			if(hDevice == nullptr)
			{
				hDevice = static_cast<HANDLE *>(malloc(sizeof(HANDLE) + sizeof(HANDLE)));
				hDevice[0] = RAWINPUTDEVICELIST[i].hDevice;
				hDevice[1] = nullptr;
			}
			else
			{
				size_t count = 0;
				for(size_t n(0); hDevice[n]; ++n) ++ count;
				hDevice[count ++] = RAWINPUTDEVICELIST[i].hDevice;
				# pragma warning(suppress: 6308) // 'realloc' might return null pointer:
				// assigning null to 'hDevice', which is passed as an argument to 'realloc', will cause the original memory block to be leaked.
				hDevice = static_cast<HANDLE *>(realloc(hDevice, sizeof(HANDLE)*count + sizeof(HANDLE)));
				# pragma warning(suppress: 28182) // Dereferencing NULL pointer. 'hDevice' contains the same NULL value as 'realloc()' did.
				hDevice[count] = nullptr;
			}
		}
	}
	delete[ ] RAWINPUTDEVICELIST;
	// 
	if(ASSERT(hDevice))
	{
		RAWINPUTDEVICE = {usUsagePage, usUsage, dwFlags, hWnd};
		ASSERT(RegisterRawInputDevices(& RAWINPUTDEVICE, 1, sizeof RAWINPUTDEVICE));
	}
}
void HID<void>::operator =(HID<void> &&HID) noexcept
{
	memcpy(this, &HID, sizeof HID);
	memset(&HID, 0, sizeof HID);
}
HANDLE HID<>::operator( )(WPARAM W, LPARAM L)
{
	HRAWINPUT HRAWINPUT = reinterpret_cast<::HRAWINPUT>(L);
	// realloc
	if(cbSize < sizeof(RAWINPUTHEADER)) 
	# pragma warning(suppress: 6308) // 'realloc' might return null pointer:
	// assigning null to 'RAWINPUT', which is passed as an argument to 'realloc', will cause the original memory block to be leaked.
	RAWINPUT = static_cast<::RAWINPUT *>(realloc(RAWINPUT, sizeof(RAWINPUTHEADER)));
	if(ASSERT(GetRawInputData(HRAWINPUT, RID_HEADER, RAWINPUT, &cbSize, sizeof(RAWINPUTHEADER)) == sizeof(RAWINPUTHEADER)))
	# pragma warning(suppress: 28182) // Dereferencing NULL pointer. 'RAWINPUT' contains the same NULL value as 'realloc()' did.
	if(RAWINPUT->header.dwType == dwType) for(HANDLE *phDevice = hDevice; *phDevice; ++phDevice)
	if(RAWINPUT->header.hDevice == *phDevice)
	{
		# pragma warning(suppress: 6001) // Using uninitialized memory 'cbSize'.
		if(UINT cbSize; GetRawInputData(HRAWINPUT, RID_INPUT, nullptr, &cbSize, sizeof(RAWINPUTHEADER)), this->cbSize != cbSize)
		# pragma warning(suppress: 6308) // 'realloc' might return null pointer:
		// assigning null to 'RAWINPUT', which is passed as an argument to 'realloc', will cause the original memory block to be leaked.
		RAWINPUT = static_cast<::RAWINPUT *>(realloc(RAWINPUT, this->cbSize = cbSize));
		if(ASSERT(GetRawInputData(HRAWINPUT, RID_INPUT, RAWINPUT, &cbSize, sizeof(RAWINPUTHEADER)) == cbSize))
		{
			const_cast<DWORD &>(dwCount) = dwType == RIM_TYPEHID ? RAWINPUT->data.hid.dwCount : 1;
			return RAWINPUT->header.hDevice;
		}
	}
	const_cast<DWORD &>(dwCount) = 0;
	return nullptr;
}
HID<>::operator void *(void) const
{
	if(sizeof(RAWINPUTHEADER) < cbSize) switch(dwType)
	{
		case RIM_TYPEMOUSE:	return & RAWINPUT->data.mouse;
		case RIM_TYPEKEYBOARD:	return & RAWINPUT->data.keyboard;
		case RIM_TYPEHID:	return & RAWINPUT->data.hid.bRawData;
		default: ERROR("RIM_"); return nullptr;
	}
	return nullptr;
}