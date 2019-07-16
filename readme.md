![alt text](https://repository-images.githubusercontent.com/197114287/6509fe00-a804-11e9-829c-e87bcc9644dc "Pyro Logo")

# Usage
``` 
// wnd.ini
name = WindowTitle
icon = custom.ico
width = 1280
height = 720
``` 

``` 
// wnd.cpp
# include <wnd.h>
LRESULT WINAPI WND(HWND, UINT, WPARAM, LPARAM)
{
  case WM_CREATE:
    ...
    ShowWindow(HWND, SW_SHOW);
  case WM_DESTROY:
    ...
    PostQuitMessage(0);
}
```

# License
[MIT](https://choosealicense.com/licenses/mit/) hopefully
