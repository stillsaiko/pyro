
# Usage

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
}
```

``` 
// wnd.ini
name = WindowTitle
icon = custom.ico
width = 1280
height = 720
``` 

``` 
// glsl.ini
version = 430
include = shader_macros.h
``` 
![alt text](https://repository-images.githubusercontent.com/197114287/6509fe00-a804-11e9-829c-e87bcc9644dc "Pyro Logo")

# License
[MIT](https://choosealicense.com/licenses/mit/) hopefully
