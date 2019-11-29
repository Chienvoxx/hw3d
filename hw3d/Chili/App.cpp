#include "App.h"



App::App()
	:
	wnd(800, 600, "Chili DX11 Default Window")
{}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but do not block for new messages
		if (const auto exitCode = Window::ProcessMessages())
		{
			// if return optional has value it means we're quitting so return exit code
			return *exitCode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	static std::string title;
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (e->IsPress() && e->GetCode() == VK_BACK)
		{
			title.clear();
			wnd.SetTitle(title);
		}
	}
	while (const auto c = wnd.kbd.ReadChar())
	{
		if (*c != 0x8) // don't print backspace
		{
			title += *c;
			wnd.SetTitle(title);
		}
	}
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, c);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}
