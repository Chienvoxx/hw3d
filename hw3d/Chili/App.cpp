#include "App.h"


App::App()
	:
	wnd(800, 600, "Chili DX11 Default Window")
{}

int App::Go()
{
	MSG msg; // the tagMSG struct
	BOOL gResult; // typedef int BOOL
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		// TranslateMessage will post auxiliary WM_CHAR messages from key msgs
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// check if GetMessage borked
	if (gResult == -1)
	{
		throw CHWND_LAST_EXCEPT();
	}

	// wParam here is the value passed to PostQuitMessage
	return msg.wParam;
}

void App::DoFrame()
{

}
