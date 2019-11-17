#include <Windows.h>
#include <sstream>
#include "WindowsMessageMap.h"
#include "Window.h"


LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OnSize(HWND hwnd, UINT flag, int width, int height);


// https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
int WINAPI WinMain(
	HINSTANCE	hInstance,		// A handle to the current instance of the application. Can ignore because there is a function to get when you want it.
	HINSTANCE	hPrevInstance,	// Always null. A holdover from 16 bit windows
	LPSTR		lpCmdLine,		// Command line data. Comes in as a single string
	int			nCmdShow)		// How the window should be presented on startup		https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
{

	try
	{

		Window wnd(800, 300, "Donkey DX11 Box");

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

			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse position: (" << e.GetPosX() << ", " << e.GetPosY() << ")";
					wnd.SetTitle(oss.str());
				}
			}
		}


		if (gResult == -1)
		{

			throw CHWND_LAST_EXCEPT();
		}
		else
		{
			return msg.wParam;
		}
	}
	catch (const ChiliException e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	OutputDebugString( mm(msg, lParam, wParam).c_str() );


	// Exactly 1000 messages listed here https://wiki.winehq.org/List_Of_Windows_Messages
	// Says all standard messages that are used https://en.wikichip.org/wiki/List_of_Windows_Messages_-_Win32
	// 
			static std::string title;
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(69);
			break;
		case WM_KEYDOWN:
			if (wParam == 'F')
			{
				//SetWindowText(hwnd, "F Pressed");
				break;
			}
			break;
		case WM_KEYUP:
			if (wParam == 'F')
			{
				//SetWindowText(hwnd, "F Released");
				break;
			}
			break;
		case WM_CHAR:
		{
			if (wParam == VK_BACK)
			{
				if(title.size() > 0)
					title.pop_back();
			}
			else
			{
				title.push_back((char)wParam);
			}
			SetWindowText(hwnd, title.c_str());
			break;
		}
		case WM_LBUTTONDOWN:
		{
			//static int xPos;
			//static int yPos;
			//xPos = GET_X_LPARAM(lParam);
			//yPos = GET_Y_LPARAM(lParam);
			POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << title << "   (" << pt.x << ", " << pt.y << ")";
			SetWindowText(hwnd, oss.str().c_str());
			break;
		}
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