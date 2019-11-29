#include "App.h"
#include <sstream>



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
	while (const auto e = wnd.mouse.Read())
	{
		switch (e->GetType())
		{
		case Mouse::Event::Type::Move:
		{
			std::ostringstream oss;
			oss << "Mouse moved to: (" << e->GetPosX() << ", " << e->GetPosY() << ")\n";
			wnd.SetTitle(oss.str());
			break;
		}
		}
	}
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, c);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}
