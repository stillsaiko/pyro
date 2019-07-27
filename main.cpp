# include "wnd.h"
# include "ini.h"
# include <cstdio>
# include <cassert>
HWND wnd(NULL);
# include "pyro/shared.h" // shared<INI>
int __main(const char * cmdline, HINSTANCE hInstance, int SW){
	INI& ini = pyro::shared<INI>[B40LL("wnd")] = INI(RC("wnd.ini"));
	int width(CW_USEDEFAULT), height(CW_USEDEFAULT);
	LPCSTR name(NULL);
	HICON ICON(NULL);
	for(INI::S & sect : ini)
	for(INI::K & expr : sect)
	switch( expr ){
		case B40LL("name"):
			name = expr.trim(" \t\r");
			break ;
		case B40LL("icon"):
			ICON = LoadIconA(hInstance, expr.trim(" \t\r"));
			break ;
		case B40LL("width"):
			width = expr.as_long( );
			break ;
		case B40LL("height"):
			height = expr.as_long( );
			break ;
		default:
			break ;
	}
	WNDCLASS WC {
		CS, WND, 0, 0, hInstance,
		ICON,//(HICON)LoadIcon(GetModuleHandleA(NULL), "fruit.ico"),
		(HCURSOR)LoadCursorA(NULL, IDC_HAND),
		(HBRUSH)GetStockObject(GRAY_BRUSH),
		(LPCSTR)nullptr,
		"lpszClass"
	};
	if(!GetClassInfoA(hInstance, WC.lpszClassName, &WC))
		RegisterClassA(&WC);
		
	if( CW_USEDEFAULT - width )
	if( CW_USEDEFAULT - height ){
		RECT R[1]{0, 0, width, height};
		AdjustWindowRectEx(R, WS, FALSE, WS_EX);
		width = R->right - R->left ;
		height = R->bottom - R->top ;
	}
	wnd = CreateWindowExA( WS_EX,
	WC.lpszClassName, name, WS, CW_USEDEFAULT, CW_USEDEFAULT,
	width, height, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)cmdline);
	assert( wnd );
	ShowWindow(wnd, SW);
	MSG M[1] {0};
	while(IsWindow(wnd) && GetMessageA(M,nullptr,0,0)){
		// window-procedure
		TranslateMessage(M);
		DispatchMessageA(M);
		// post-procedure
		switch(M->message){
			case WM_QUIT:
				return M->wParam ;
			case WM_DESTROY:
				if(M->hwnd == wnd) PostQuitMessage(0);
			default:
				break ;
		}
	}
	return 0;
}
// __clrcall
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd){
// PWSTR lpCmdLine (wWinMain)
	MessageBoxA(NULL, lpCmdLine, "T", MB_OK); // ?#@!
	return __main(lpCmdLine, hInstance=GetModuleHandleA(NULL), nShowCmd=SW_SHOW);
}
int main(int argc, const char * argv[ ]){
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	int SW = SW_SHOW ;
	int R = __main(argv[1], hInstance, SW);
	return 0;
}