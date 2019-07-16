# include "wnd.h"
# include "ini.h"
# include <cstdio>
# include <cassert>
//const char * cmdline(nullptr);
HWND wnd(NULL);
//size_t FPS(0u);
int __main(const char * cmdline, HINSTANCE hInstance, int SW){
	/*{
		char buf[512];
		if( sscanf(cmdline, "%s", buf) ){
			char c ;
			do {
				c = buf[strlen(buf)-1];
				buf[strlen(buf)-1] = '\0';
			} while( c != '/' && c != '\\' );
			printf("SetCurrentDirectoryA(%s)\n", buf);
			SetCurrentDirectoryA(buf);
		}{}
	}*/
	INI __ini(RC("wnd.ini"));
//	ini __ini(RC("wnd.ini"));
	int width(CW_USEDEFAULT), height(CW_USEDEFAULT);
	LPCSTR name(NULL);
	//if(auto __ini = __ini.section("WND")){
		HICON ICON(NULL);
		for(INI::S & sect : __ini){
			for(INI::K & expr : sect){
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
			}
		}
/*		if(auto * a = __ini["name"])	name = a ;
		if(auto * a = __ini["icon"])	ICON = LoadIconA(hInstance, a);
		if(auto * a = __ini["width"])	assert(sscanf(a, "%i", &width));
		if(auto * a = __ini["height"])	assert(sscanf(a, "%i", &height));*/
	//}
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

/*	pyro::wnd = WND(
		CREATESTRUCTA {
			nullptr,
			hInstance,
			(HMENU)NULL,
			(HWND)NULL, // parent
			height,//(int)CW_USEDEFAULT,//pyro::height,
			width,//(int)CW_USEDEFAULT,//pyro::width,
			(int)CW_USEDEFAULT,
			(int)CW_USEDEFAULT,
			pyro::WS,
			"lpszName",
			"lpszClass",
			pyro::WS_EX
		},
		pyro::WNDPROC,
		pyro::CS
	);*/
	assert( wnd );
	ShowWindow(wnd, SW);
	MSG M[1] {0};
	while( IsWindow(wnd) ){
		while(/*FPS	?PeekMessageA(M,nullptr,0,0,PM_REMOVE)
					:*/ GetMessageA(M,nullptr,0,0)){
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
	/*	// send update message
		if( FPS ){
			SendMessageA(wnd, WM_TIMER, 0, 0L);
			Sleep(1000/FPS);
		}*/
	}
	return 0;
}
// __clrcall
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, // PWSTR (wWinMain)
    int nShowCmd
    ){
	MessageBoxA(NULL, lpCmdLine, "T", MB_OK);
//	printf("lpCmdLine`%s'\n", lpCmdLine);
	return __main(lpCmdLine, hInstance=GetModuleHandleA(NULL), nShowCmd=SW_SHOW);
}
int main(int argc, const char * argv[ ]){
/*	{
		size_t len(0u);
		for(int i(0); i<argc; ++i){
			len += 1u + strlen(argv[i]);
		}
		cmdline = new char[len]{0};
		for(int i(0); i<argc; ++i){
			if(i) strcat(const_cast<char*&>(cmdline), " ");
			strcat(const_cast<char*&>(cmdline), argv[i]);
		}
	}*/
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	int SW = SW_SHOW ;
//	int R = __main(cmdline, hInstance, SW);
	int R = __main(argv[1], hInstance, SW);
//	delete[ ] cmdline ;
	return 0;
}
