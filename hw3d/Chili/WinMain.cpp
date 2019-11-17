#include "Window.h"
#include <sstream>



int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	try
	{
		Window wnd(800, 300, "Donkey DX11 Box");
	
		MSG msg; // the tagMSG struct
		BOOL gResult; // typedef int BOOL
		while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				switch (e.GetType())
				{
					case Mouse::Event::Type::Leave:
					{
						wnd.SetTitle("Gone!");
						break;
					}
					case Mouse::Event::Type::Move:
					{
						std::ostringstream oss;
						oss << "Mouse position: (" << e.GetPosX() << ", " << e.GetPosY() << ")";
						wnd.SetTitle(oss.str());
						break;
					}
				}
			}
		}

		if (gResult == -1)
		{
			throw CHWND_LAST_EXCEPT();
		}

			return msg.wParam;
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

