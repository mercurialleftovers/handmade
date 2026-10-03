#include <windows.h>

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT Message, WPARAM WParam,
                                LPARAM LParam);

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine,
                     int CmdShow) {
  tagWNDCLASSA wc{}; // 0-initialized

  wc.style = CS_OWNDC | CS_HREDRAW |
             CS_VREDRAW; // CS_OWNDC: each window of this class has its own
                         // independent device context
  wc.lpfnWndProc = WindowCallback;
  wc.hInstance = Instance; // GetModuleHandle(0)
  wc.lpszClassName = "Handmade Window Class";

  if (RegisterClass(&wc)) {
    HWND WindowHandle = CreateWindowEx(
        0, wc.lpszClassName, "Handmade Hero", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
        Instance, 0);
    if (WindowHandle) {
      MSG Message;
      while (GetMessage(&Message, 0, 0, 0) > 0) {
        TranslateMessage(&Message); // kbd messages -> more proper kbd messages
        DispatchMessage(&Message);  // send message to lpfnWndProc ?
      }

    } else {
      // TODO(bader): handle failing to CreateWindow
    }

  } else {
    // TODO(bader): handle failign to RegisterClass
  }

  return (0);
}

LRESULT CALLBACK WindowCallback(HWND WindowHandle, UINT Message, WPARAM WParam,
                                LPARAM LParam) {
  // WindowHandle: which window are you talking about ? (opaque resource)
  // Message:

  LRESULT Result = 0;
  switch (Message) {
  case WM_SIZE: {
    MessageBoxA(0, "Window Size", "Callback", MB_OK | MB_ICONINFORMATION);
  } break;
  case WM_DESTROY: {
    MessageBoxA(0, "Window Destroy", "Callback", MB_OK | MB_ICONINFORMATION);
    DefWindowProc(WindowHandle, Message, WParam, LParam);
  } break;
  case WM_CLOSE: {
    MessageBoxA(0, "Window CLose", "Callback", MB_OK | MB_ICONINFORMATION);
  } break;
  default: {
    Result = DefWindowProc(WindowHandle, Message, WParam, LParam);
  } break;
  }

  return (Result);
}
