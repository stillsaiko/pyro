# pragma once
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
template<class = void> struct HID;
// HID <struct {char [2], BTN, X[2], Y[2], Z[2], [2];}>	(hWnd, 0xFF00, 0x000A) // wacom
// HID <struct {char ID, [2], X, Y, BTN, LR;}>		(hWnd, 0x0001, 0x0004) // nintendo
// HID <RAWKEYBOARD>	(hWnd, 0x0001, 0x0006) // keyboard
// HID <RAWMOUSE>	(hWnd, 0x0001, 0x0002) // mouse
template<> struct HID<void>
{
	const DWORD dwCount;
	~
	HID(void);
	HID(void);
	HID(HWND hWnd, USHORT usUsagePage, USHORT usUsage, DWORD dwFlags = 0);
	void operator =(HID<void> &&) noexcept;
	HANDLE operator( )(WPARAM W, LPARAM L); // returns access length
	operator void *(void) const;
protected:
	HANDLE *hDevice = nullptr;
	RAWINPUTDEVICE RAWINPUTDEVICE { };
	DWORD dwType = 0;
	RAWINPUT *RAWINPUT = nullptr;
	UINT cbSize = 0;
};
template<class T> struct HID : public HID<void>
{
	HID(void) = default;
//	HID(HID<T> &&) = default;
	HID(HWND hWnd, USHORT usUsagePage, USHORT usUsage, DWORD dwFlags = 0):
	HID<void>(hWnd, usUsagePage, usUsage, dwFlags)
	{
		if(dwType == RIM_TYPEMOUSE) ASSERT(sizeof(T) == sizeof(RAWMOUSE));
		if(dwType == RIM_TYPEKEYBOARD) ASSERT(sizeof(T) == sizeof(RAWKEYBOARD));
	}
//	void operator =(HID<T> &&)
	const T *operator ->(void) const
	{
		return static_cast<const T*>(operator void *( ));
	}
	const T &operator *(void) const
	{
		return *static_cast<const T*>(operator void *( ));
	}
	const T &operator[ ](size_t n) const
	{
		return static_cast<const T*>(operator void *( ))[n];
	}
};
