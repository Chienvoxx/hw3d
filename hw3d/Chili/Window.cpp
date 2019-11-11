#include "Window.h"
#include <string>		//	temp include used to for Window text
#include <sstream>		//  temp include used in HandleMsg


// temp forward declaration
void OnSize(HWND hwnd, UINT flag, int width, int height);


	/*	1-	Register Window Class
		2-	Create Window Instance
		3-	Show Window
		4-	Handle Messages
				See while loop in WinMain.cpp
	*/

// WindowClass stuff
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
{
	const auto pClassName = "dx11Window";
	// 1-	Register Window Class
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
	WNDCLASSEXA wc = { 0 };					// Struct to pass to Window class, zeroed out for initialization
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;					// Gives each window its own device context so it can be rendered to independently
	wc.lpfnWndProc = HandleMessageSetup;	// Pointer to function that handles all the messages for the window. Initially set to default windows procedure. Later we'll create our own.
	wc.cbClsExtra = 0;						// Allocate extra bytes to store custom data in the class
	wc.cbWndExtra = 0;						// Allocate extra bytes to srore custom data in each instance of the window
	wc.hInstance = GetInstance();			// A handle to the instance that contains the window procedure for the class.
	wc.hIcon = nullptr;						
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;				// A GDI brush. When this member is NULL, an application must paint its own background whenever it is requested to paint in its client area
	wc.lpszMenuName = nullptr;				// If this member is NULL, windows belonging to this class have no default menu
	wc.lpszClassName = GetName();			// If lpszClassName is a string, it specifies the window class name. The class name can be any name registered with RegisterClass or RegisterClassEx
	wc.hIconSm = nullptr;					// A handle to a small icon that is associated with the window class.
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


//Window stuff
Window::Window(int width, int height, const char* name) noexcept
{
	// 2-	Create Window Instance
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
	// Calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	//create window and get hWind
	hWnd = CreateWindow(
		WindowClass::GetName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this
	);

	// 3-	Show Window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

// CALLBACK and WINAPI are #defines for __stdcall which tells the compiler how to structure the function in the manner that Windows expects it to be.
LRESULT CALLBACK Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		// extract pointer to window class from creation data
		// CREATESTRUCTW contains HINSTANCE, HWND, data past in RegisterClassEx(WNDCLASSEXA*), and CreateWindow(...).
		// data from CreateWindow(...) is contained in lpCreateParams, in particular the pointer this.
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to Window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal non-setup handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));
		// forward message to the Window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before WM_CREATE handle with the default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to Window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to the Window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

// https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	static std::string windowText;
	switch (msg)
	{
		case WM_CLOSE:
			// we don't want the DefProc to handle this message because
			// we want our destructor to destroy the window, so return 0 instead of break
			PostQuitMessage(0);
			return 0;
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
				if (windowText.size() > 0)
					windowText.pop_back();
			}
			else
			{
				windowText.push_back((char)wParam);
			}
			SetWindowText(hWnd, windowText.c_str());
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
			oss << windowText << "   (" << pt.x << ", " << pt.y << ")";
			SetWindowText(hWnd, oss.str().c_str());
			break;
		}
		case WM_SIZE:
			int width = LOWORD(lParam);  // Macro to get the low-order word.
			int height = HIWORD(lParam); // Macro to get the high-order word.

			// Respond to the message:
			OnSize(hWnd, (UINT)wParam, width, height);
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	: ChiliException(line, file), hr(hr)
{}


const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}


const char* Window::Exception::GetType() const noexcept
{
	return "Chili Window Exception";
}


std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}


HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}


std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
