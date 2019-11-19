#include "App.h"
#include <sstream>
#include <iomanip>


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
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}
