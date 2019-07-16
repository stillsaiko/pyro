# include "hid.h"
__HID :: ~ __HID(void){
	printf("warning: __HID (destructor)\n");
	if( data ){delete[ ]
		data ;
	RIDEV.dwFlags = RIDEV_REMOVE ;
	RegisterRawInputDevices(& RIDEV, 1, sizeof RIDEV);}
}
__HID :: __HID(void){ }
__HID :: __HID(USHORT usUsagePage, USHORT usUsage, HWND hWnd){
	if(usUsagePage == 1u && usUsage == 2u) RIM_TYPE = RIM_TYPEMOUSE ;
	if(usUsagePage == 1u && usUsage == 6u) RIM_TYPE = RIM_TYPEKEYBOARD ;
	{
		UINT count = 0u ;
		GetRawInputDeviceList(nullptr, & count, sizeof(RAWINPUTDEVICELIST)); 
		RAWINPUTDEVICELIST * list = new RAWINPUTDEVICELIST[count];
		size_t n = GetRawInputDeviceList(list, & count, sizeof(RAWINPUTDEVICELIST)); 
		for(size_t i = 0u ; i < n ; ++ i){
			RID_DEVICE_INFO info {0};
			UINT size = sizeof info ;
			GetRawInputDeviceInfoA(list[i].hDevice, RIDI_DEVICEINFO, &info, & size);
			if( list[i].dwType == RIM_TYPE )
			if( info.hid.usUsagePage == usUsagePage )
			if( info.hid.usUsage == usUsage ){
			set.emplace( list[i].hDevice );/* printf(" hDevice 0x%p\n", list[i].hDevice);
			if( info.dwType == RIM_TYPEMOUSE ) printf(" RIM_TYPEMOUSE\n");
			if( info.dwType == RIM_TYPEKEYBOARD ) printf(" RIM_TYPEKEYBOARD\n");
			if( info.dwType == RIM_TYPEHID ) printf(" RIM_TYPEHID (usUsagePage=%hu usUsage=%hu)\n", info.hid.usUsagePage, info.hid.usUsage);
			{
				printf(" HIDD_ATTRIBUTES\n");
				HIDD_ATTRIBUTES ATTRIBUTES ;
				HidD_GetAttributes(list[i].hDevice, & ATTRIBUTES);
				printf("VendorID %hu\n", ATTRIBUTES.VendorID);
				printf("ProductID %hu\n", ATTRIBUTES.ProductID);
				printf("VersionNumber %hu\n", ATTRIBUTES.VersionNumber);
			}
			GetRawInputDeviceInfoA(list[i].hDevice, RIDI_PREPARSEDDATA, nullptr, & size);
			BYTE * PREPARSEDDATA = new BYTE[size];
			GetRawInputDeviceInfoA(list[i].hDevice, RIDI_PREPARSEDDATA, PREPARSEDDATA, & size);
			{
				printf(" HIDP_CAPS\n");
				HIDP_CAPS CAPS ;
				HidP_GetCaps((PHIDP_PREPARSED_DATA)PREPARSEDDATA, & CAPS);
				printf("Usage %hu\n", CAPS.Usage);
				printf("UsagePage %hu\n", CAPS.UsagePage);
				printf("InputReportByteLength %hu\n", CAPS.InputReportByteLength);
				printf("OutputReportByteLength %hu\n", CAPS.OutputReportByteLength);
				printf("FeatureReportByteLength %hu\n", CAPS.FeatureReportByteLength);
				printf("Reserved[17]\n");
				printf("NumberLinkCollectionNodes %hu\n", CAPS.NumberLinkCollectionNodes);
				printf("NumberInputButtonCaps %hu\n", CAPS.NumberInputButtonCaps);
				printf("NumberInputValueCaps %hu\n", CAPS.NumberInputValueCaps);
				printf("NumberInputDataIndices %hu\n", CAPS.NumberInputDataIndices);
				printf("NumberOutputButtonCaps %hu\n", CAPS.NumberOutputButtonCaps);
				printf("NumberOutputValueCaps %hu\n", CAPS.NumberOutputValueCaps);
				printf("NumberOutputDataIndices %hu\n", CAPS.NumberOutputDataIndices);
				printf("NumberFeatureButtonCaps %hu\n", CAPS.NumberFeatureButtonCaps);
				printf("NumberFeatureValueCaps %hu\n", CAPS.NumberFeatureValueCaps);
				printf("NumberFeatureDataIndices %hu\n", CAPS.NumberFeatureDataIndices);
				{
					printf(" HIDP_VALUE_CAPS\n");
					HIDP_VALUE_CAPS *
							VALUE_CAPS = new
					HIDP_VALUE_CAPS[CAPS.NumberInputValueCaps];
					HidP_GetValueCaps(HidP_Input, VALUE_CAPS, &CAPS.NumberInputValueCaps, (PHIDP_PREPARSED_DATA)PREPARSEDDATA);
					for(size_t i=0; i<CAPS.NumberInputValueCaps; ++i){
						printf("UsagePage: %hu\n", VALUE_CAPS[i].UsagePage);
						printf("ReportID: %hhu\n", VALUE_CAPS[i].ReportID);
						printf("IsAlias: %s\n", VALUE_CAPS[i].IsAlias ? "TRUE" : "FALSE");

						printf("BitField: %hu\n", VALUE_CAPS[i].BitField);
						printf("LinkCollection: %hu\n", VALUE_CAPS[i].LinkCollection);   // A unique internal index pointer

						printf("LinkUsage: %hu\n", VALUE_CAPS[i].LinkUsage);
						printf("LinkUsagePage: %hu\n", VALUE_CAPS[i].LinkUsagePage);

						printf("IsRange: %s\n", VALUE_CAPS[i].IsRange ? "TRUE" : "FALSE");
						printf("IsStringRange: %s\n", VALUE_CAPS[i].IsStringRange ? "TRUE" : "FALSE");
						printf("IsDesignatorRange: %s\n", VALUE_CAPS[i].IsDesignatorRange ? "TRUE" : "FALSE");
						printf("IsAbsolute: %s\n", VALUE_CAPS[i].IsAbsolute ? "TRUE" : "FALSE");

						printf("HasNull: %s\n", VALUE_CAPS[i].HasNull ? "TRUE" : "FALSE");        // Does this channel have a null report   union
						//printf("Reserved: %hhu\n", VALUE_CAPS[i].Reserved);
						printf("BitSize: %hu\n", VALUE_CAPS[i].BitSize);        // How many bits are devoted to this value?

						printf("ReportCount: %hu\n", VALUE_CAPS[i].ReportCount);    // See Note below.  Usually set to 1.
						//printf("Reserved2[5]\n");

						printf("UnitsExp: %lu\n", VALUE_CAPS[i].UnitsExp);
						printf("Units: %lu\n", VALUE_CAPS[i].Units);

						printf("Logical: [%li, %li]\n", VALUE_CAPS[i].LogicalMin, VALUE_CAPS[i].LogicalMax);
						printf("Physical: [%li, %li]\n", VALUE_CAPS[i].PhysicalMin, VALUE_CAPS[i].PhysicalMax);
						if(VALUE_CAPS[i].IsRange){
							printf("Usage:     [%hu, %hu]\n",VALUE_CAPS[i].Range.UsageMin,     VALUE_CAPS[i].Range.UsageMax);
							printf("String:    [%hu, %hu]\n",VALUE_CAPS[i].Range.StringMin,    VALUE_CAPS[i].Range.StringMax);
							printf("Designator:[%hu, %hu]\n",VALUE_CAPS[i].Range.DesignatorMin,VALUE_CAPS[i].Range.DesignatorMax);
							printf("DataIndex: [%hu, %hu]\n",VALUE_CAPS[i].Range.DataIndexMin, VALUE_CAPS[i].Range.DataIndexMax);
						} else {
							printf("Usage:     [%hu,#%hu]\n",VALUE_CAPS[i].NotRange.Usage,     VALUE_CAPS[i].NotRange.Reserved1);
							printf("String:    [%hu,#%hu]\n",VALUE_CAPS[i].NotRange.StringIndex,    VALUE_CAPS[i].NotRange.Reserved2);
							printf("Designator:[%hu,#%hu]\n",VALUE_CAPS[i].NotRange.DesignatorIndex,VALUE_CAPS[i].NotRange.Reserved3);
							printf("DataIndex: [%hu,#%hu]\n",VALUE_CAPS[i].NotRange.DataIndex, VALUE_CAPS[i].NotRange.Reserved4);
						}
						printf("\n");
					}
					delete[ ] VALUE_CAPS ;
				}
			}
			delete[ ] PREPARSEDDATA ;*/
			}
		}
	}
	RIDEV.usUsagePage = usUsagePage ;
	RIDEV.usUsage = usUsage ;
	RIDEV.hwndTarget = hWnd ;
	assert( RegisterRawInputDevices(& RIDEV, 1, sizeof RIDEV) );
}
size_t __HID :: operator( )(WPARAM W, LPARAM L){
	HRAWINPUT
		RAWINPUT = reinterpret_cast<HRAWINPUT>(L);
	// ...
	RAWINPUTHEADER RIHDR ;
	// assert ?!
	assert( GetRawInputData(RAWINPUT, RID_HEADER, & RIHDR, & size, sizeof RIHDR) == sizeof RIHDR );
	if( RIHDR.dwType != RIM_TYPE )return 0u ;
	if( set.find(RIHDR.hDevice) == set.end( ) )return 0u ;
	// assert ?!
	assert( GetRawInputData(RAWINPUT, RID_INPUT, nullptr, &size, sizeof RIHDR) == 0u );
//		printf(" size = %u\n", size);
	if( data )delete[ ]
		data ;
		data = new char[size];
	// assert ?!
	assert( GetRawInputData(RAWINPUT, RID_INPUT, data, &size, sizeof RIHDR) == size );
/*	printf("size[%u] == sizeof(T)[%u]\n",
		size - sizeof RIHDR - offsetof(RAWHID, bRawData), sizeof(T));*/
//		if(!(size - sizeof RIHDR - offsetof(RAWHID, bRawData) == sizeof(T)))
//		printf(" %u != %u\n", size - sizeof RIHDR - offsetof(RAWHID, bRawData), sizeof(T));
//	assert( (size - sizeof RIHDR - offsetof(RAWHID, bRawData)) % sizeof(T) == 0u ); // '*!@?
	return RIHDR.dwType == RIM_TYPEHID ? reinterpret_cast<RAWHID*>(data
												+ sizeof RIHDR)->dwCount : 1u ; // '*!@?
}