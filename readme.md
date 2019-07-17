# io
``` 
struct Gamepad
{
  float x, y ;
  bool A, B ;
  bool X, Y ;
  bool L, R ;
};
using namespace pyro
class object : public io<Gamepad>
{
	static constexpr float jump_momentum = 42.f ;
	float x = 0.f ;
	float y = 0.f ;
	float z = 0.f ;
public:
	GAMEPAD * flush(size_t count, GAMEPAD * gamepad)override
	{
		while( count )
		{
			if( gamepad->A )
				this->z += jump_momentum ;
			this->x += gamepad->x ;
			this->y += gamepad->y ;
			-- count ;
		}
		return nullptr ;
	}
};
``` 
# WNDPROC

``` 
// wnd.cpp
# include <wnd.h>
# include <glrc.h> // OpenGL
GLRC OpenGL ;
LRESULT WINAPI WND(HWND, UINT, WPARAM, LPARAM)
{
  case WM_CREATE:
    OpenGL = GLRC(4, 3);
    ...initialize highlevel
    ShowWindow(HWND, SW_SHOW);
    return
  case WM_DESTROY:
    ...release highlevel
    OpenGL = GLRC( ); // release
    PostQuitMessage(0);
    return
  case WM_PAINT:
 	...render scene
	OpenGL.swap( ); // SwapBuffers(HDC)
	return
}
```
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
![alt text](https://repository-images.githubusercontent.com/197114287/6509fe00-a804-11e9-829c-e87bcc9644dc "Pyro Logo")
