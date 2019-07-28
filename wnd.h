# pragma once
# define WIN32_MEAN_AND_LEAN
# include <windows.h>
// WND
	extern const LONG WS ; // user reference
	extern const DWORD WS_EX ; // user reference
// WNDCLASS
	extern const UINT CS ; // user reference
//	if(HWND == NULL)
//		return 0L
//	switch(UINT)
//		case WM_CREATE: ShowWindow(HWND, SW_SHOW)
//		case WM_PAINT:
//		case WM_DESTROY:
//	return DefWindowProc(HWND, UINT, WPARAM, LPARAM)
	extern LRESULT WINAPI WND(HWND, UINT, WPARAM, LPARAM); // user impl
// alloceted by library it-self
	//extern size_t FPS ;
extern int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); // LPCSTR
// user defined impl
// should look like this:
/*
// extern
	const LONG WS(WS_OVERLAPPED);
	const DWORD WS_EX(WS_EX_APPWINDOW);
	const UINT CS(CS_OWNDC);
	LRESULT WINAPI WND(HWND H, UINT M, WPARAM W, LPARAM L){
		if(M==WM_CREATE)
			ShowWindow(H, SW_SHOW);
		if(M==WM_DESTROY)
			PostQuitMessage(0);
		return DefWindowProc(H, M, W, L);
	}
}
*/
