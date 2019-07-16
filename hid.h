/*# ifdef __MINGW32__
# define _WIN32_WINNT _WIN32_WINNT_WIN7
//#   define _WIN32_WINNT 0x0501
# include <winuser.h>
# else*/
# include "wnd.h"
//# endif
//#define WIN32_LEAN_AND_MEAN
//#define WIN32_EXTRA_LEANRAWINPUTDEVICE
//#endif // __MINGW32__
//#include <windows.h>
//# include "wnd.h"
# include <cassert>
# include <cstdio>
# include <set>
/*# ifdef __MINGW32__
#	include <ddk/hidsdi.h>
# else
#	include <hidsdi.h>
# endif // __MINGW32__*/
//extern "C"
//{
//	#include <setupapi.h>
 //   #include <ddk/hidsdi.h>
//	#include <ddk/hidclass.h>
//}
# include <cstddef>
// i hate MinGW
# ifdef __MINGW32__
//#	include <ddk/hidsdi.h>
# endif // __MINGW32__
struct __HID {
	virtual ~
	__HID(void);
	__HID(void);
	__HID(USHORT usUsagePage, USHORT usUsage, HWND hWnd);
	size_t operator( )(WPARAM W, LPARAM L);
protected:
	std::set<HANDLE> set ;
	RAWINPUTDEVICE RIDEV {0};
	DWORD RIM_TYPE = RIM_TYPEHID ;
	size_t size = 0u ;
	char * data = nullptr ;
};
template<class T>struct HID : public __HID {
	inline HID(void){ }
	inline HID(USHORT usUsagePage, USHORT usUsage, HWND hWnd):
		 __HID(usUsagePage, usUsage, hWnd){ }
	inline void operator = (HID<T> && refref) noexcept {
		RIDEV = refref.RIDEV ;
		size = refref.size ; size = 0u ;
		data = refref.data ; data = nullptr ;
		set = std::move(refref.set);
	}
	inline T * operator -> (void){ // '*!@?
		return data ? reinterpret_cast<T*>( data
							+ sizeof(RAWINPUTHEADER)
							+ offsetof(RAWHID, bRawData) ) : nullptr ;
	}
	inline T & operator[ ](size_t index){ // '*!@?
		return reinterpret_cast<T*>( data
							+ sizeof(RAWINPUTHEADER)
							+ offsetof(RAWHID, bRawData) )[index] ;
	}
};
