#include <Windows.h>


int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	/*	1-	Register Window Class
		2-	Create Window Instance
	*/


	const auto pClassName = "hw3d DX11 Tutorial Series";
	// 1-	Register Window Class
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
	WNDCLASSEXA wc = { 0 }; // Struct to pass to Window class, zeroed out for initialization
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// 2-	Create Window Instance
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	HWND hWnd = CreateWindowEx(
		0,
		pClassName,
		"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
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

	while (true);

	return 0;
}