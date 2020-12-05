# include "wnd.h"
# include "error.h"
# include <cstdio>
int WINAPI WinMain(_In_ HINSTANCE hModule, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	LPCSTR lpszIcon="wnd.ico", lpszCursor=IDC_HAND;
	LPCSTR lpszMenu="lpszClass", lpszClass="lpszClass", lpszWindow=nullptr;
	constexpr int x=CW_USEDEFAULT, y=CW_USEDEFAULT, nWidth=CW_USEDEFAULT, nHeight=CW_USEDEFAULT, nBrush=GRAY_BRUSH;
	{
		WNDCLASS
		WNDCLASS
		{
			CS, WND, 0, 0, hModule,
			LoadIconA(hModule, lpszIcon),
			LoadCursorA(NULL, lpszCursor),
			static_cast<HBRUSH>(GetStockObject(nBrush)),
			lpszMenu, lpszClass
		};
		ASSERT(!GetClassInfoA(hModule, lpszClass, &WNDCLASS));
		if(!ASSERT(RegisterClassA(&WNDCLASS))) return 0;
	}
	# pragma warning(suppress: 28159)
	MSG
	MSG {NULL, WM_USER, 0, 0L, GetTickCount( ), {0, 0}};
	BOOL GetMessageA;
	if(HWND CreateWindowExA = ::CreateWindowExA(WS_EX, lpszClass, lpszWindow, WS,
	x, y, nWidth, nHeight, NULL, NULL, hModule, lpCmdLine); ASSERT(CreateWindowExA))
	while(/*IsWindow(CreateWindowExA) && */(GetMessageA = ::GetMessageA(&MSG, nullptr, 0, 0)) != -1 && GetMessageA)
	{
		// window-procedure
		TranslateMessage(&MSG);
		DispatchMessageA(&MSG);
	}
	if(GetMessageA == -1)
	{
		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError( ), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		printf("`%s'\n", messageBuffer);

		LocalFree(messageBuffer);
	}
	ASSERT(UnregisterClassA(lpszClass, hModule));
	return MSG.wParam;
}
int main(int argc, char * argv[ ])
{
	return WinMain(GetModuleHandleA(NULL), NULL, argv[1], SW_SHOWDEFAULT);
}