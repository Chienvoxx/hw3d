#include <Windows.h>

// https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
// Our custom message callback procedure - set with wc.lpfnWndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OnSize(HWND hwnd, UINT flag, int width, int height);


// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
int CALLBACK WinMain(
	HINSTANCE	hInstance,		// A handle to the current instance of the application. Can ignore because there is a function to get when you want it.
	HINSTANCE	hPrevInstance,	// Always null. A holdover from 16 bit windows
	LPSTR		lpCmdLine,		// Command line data. Comes in as a single string
	int			nCmdShow)		// How the window should be presented on startup		https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
{
	/*	1-	Register Window Class
		2-	Create Window Instance
	*/


	const auto pClassName = "dx11Window";
	// 1-	Register Window Class
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
	WNDCLASSEXA wc = { 0 };			// Struct to pass to Window class, zeroed out for initialization
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;			// Gives each window its own device context so it can be rendered to independently
	wc.lpfnWndProc = WndProc;	// Pointer to function that handles all the messages for the window. Initially set to default windows procedure. Later we'll create our own.
	wc.cbClsExtra = 0;				// Allocate extra bytes to store custom data in the class
	wc.cbWndExtra = 0;				// Allocate extra bytes to srore custom data in each instance of the window
	wc.hInstance = hInstance;		// A handle to the instance that contains the window procedure for the class.
	wc.hIcon = nullptr;				// 
	wc.hCursor = nullptr;			// 
	wc.hbrBackground = nullptr;		// A GDI brush. When this member is NULL, an application must paint its own background whenever it is requested to paint in its client area
	wc.lpszMenuName = nullptr;		// If this member is NULL, windows belonging to this class have no default menu
	wc.lpszClassName = pClassName;	// If lpszClassName is a string, it specifies the window class name. The class name can be any name registered with RegisterClass or RegisterClassEx
	wc.hIconSm = nullptr;			// A handle to a small icon that is associated with the window class.
	RegisterClassEx(&wc);			// 

	// 2-	Create Window Instance
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	
/*	HWND CreateWindowExA(
		DWORD     dwExStyle,
		LPCSTR    lpClassName,
		LPCSTR    lpWindowName,
		DWORD     dwStyle,
		int       X,
		int       Y,
		int       nWidth,
		int       nHeight,
		HWND      hWndParent,
		HMENU     hMenu,
		HINSTANCE hInstance,
		LPVOID    lpParam
	); */
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		"DX11 hw3d Tutorial Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		200,
		200,
		640,
		480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	// 3-	Show Window
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
	ShowWindow(hWnd, SW_SHOW);

	// 4-	Handle Messages
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
	/*	BOOL GetMessage(
		  LPMSG lpMsg,			// pointer to tagMSG struct
		  HWND  hWnd,			// NULL to get message to all windows on the thread
		  UINT  wMsgFilterMin,
		  UINT  wMsgFilterMax
	);
			If the function retrieves a message other than WM_QUIT, the return value is nonzero.
			If the function retrieves the WM_QUIT message, the return value is zero.
			If there is an error, the return value is -1. For example, the function fails if hWnd is an invalid window handle or lpMsg is an invalid pointer.
			To get extended error information, call GetLastError.
	*/

	// tagMSG structure
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg
	/*	typedef struct tagMSG {
			HWND   hwnd;
			UINT   message;
			WPARAM wParam;
			LPARAM lParam;
			DWORD  time;
			POINT  pt;
			DWORD  lPrivate;
		} MSG, *PMSG, *NPMSG, *LPMSG; */
	
	MSG msg; // the tagMSG struct


	BOOL gResult; // typedef int BOOL
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(69);
			break;
		case WM_SIZE:
			int width = LOWORD(lParam);  // Macro to get the low-order word.
			int height = HIWORD(lParam); // Macro to get the high-order word.

			// Respond to the message:
			OnSize(hwnd, (UINT)wParam, width, height);
			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
	// Handle resizing
}