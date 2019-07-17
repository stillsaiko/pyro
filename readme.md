# *.ini
``` 
; wnd.ini
name = WindowTitle
icon = custom.ico
width = 1280
height = 720
``` 
``` 
; glsl.ini
version = 430
include = shader_macros.h
``` 
# *.rc
```
# include <rc.h>
ICO(custom.ico)
RC(wnd.ini)
RC(glsl.ini)
RC(shader_macros.h)
```
# main
main, WinMain both are compiled in main.cpp
choose one of those mains with MSC (visual c++) link option
	... either /SUBSYSTEM:CONSOLE or /SUBSYSTEM:WINDOWS
# user-defined highlevel
``` 
// user-defined.h
class Gamepad
{
  float x, y
  bool A, B
  bool X, Y
  bool L, R
}
# include <pyro/io.h> // abstract template
class Object : public io<Gamepad>
{
	static constexpr float jump_momentum = 42.f
	float x = 0.f
	float y = 0.f
	float z = 0.f
public:
	GAMEPAD * flush(size_t count, Gamepad * gamepad)override
	{
		while( count )
		{
			if( gamepad->A )
				this->z += jump_momentum
			this->x += gamepad->x
			this->y += gamepad->y
			-- count
		}
		return nullptr
	}
	void render(void)
	{
		... render object here
	}
};
``` 
# WNDPROC
```extern LRESULT WND(HWND, UINT, WPARAM, LPARAM)```  decl in wnd.h
there is no wnd.cpp impl yet existing (do it your own way)
```
// wnd.cpp
# include <wnd.h>
# include <glrc.h> // OpenGL
# include <hid.h> // InputDevice
# include "user-defined.h" // Gamepad, Object
GLRC         OpenGL
HID<GAMEPAD> InputDevice
# include <pyro/unique.h> // global inline singleton-container
using namespace pyro
LRESULT WINAPI WND(HWND, UINT, WPARAM, LPARAM)
{
  case WM_CREATE:
    InputDevice = HID<Gamepad>(HWND, ...)
    OpenGL = GLRC(4, 3) // core profile
    ...initialize highlevel
    pyro::unique<Object>.init(...)
    ShowWindow(HWND, SW_SHOW) // following WINAPI convention here.
    return
  case WM_DESTROY:
    ...release highlevel
    pyro::unique<Object>.release( )
    OpenGL = GLRC( )              // release
    InputDevice = HID<GAMEPAD>( ) // release
    PostQuitMessage(0) // following WINAPI convention here.
    return
  case WM_INPUT:
    if( size_t n = InputDevice(WPARAM, LPARAM) )
    	pyro::unique<Object>.flush(n, &InputDevice[0])
    return
  case WM_PAINT:
    pyro::unique<Object>.render( ) // draw scene
    SwapBuffers(OpenGL.DC) // following WINAPI convention here.
    return
}
```
```extern const LONG WS```  decl in wnd.h

```extern const DWORD WS_EX```  decl in wnd.h

```extern const UINT CS```  decl in wnd.h

there is no impl yet existing (do it your own way)
```
const LONG WS = WS_OVERLAPPED // WND
const DWORD WS_EX = WS_EX_APPWINDOW // WND
const UINT CS = CS_OWNDC // WNDCLASS
``` 
![alt text](https://repository-images.githubusercontent.com/197114287/6509fe00-a804-11e9-829c-e87bcc9644dc "Pyro Logo")
