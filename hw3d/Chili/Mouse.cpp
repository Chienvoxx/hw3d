#include "Mouse.h"



std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x, y };
}

int Mouse::GetPosX() const noexcept
{
	return x;
}

int Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

Mouse::Event Mouse::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::OnMousMove(int X, int Y) noexcept
{
	x = X;
	y = Y;
	buffer.push(Mouse::Event(Event::Type::Move, *this));
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(Mouse::Event(Event::Type::Leave, *this));
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(Mouse::Event(Event::Type::Enter, *this));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::LPress, *this));
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::LRelease, *this));
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::RPress, *this));
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::RRelease, *this));
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::WheelUp, *this));
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Event::Type::WheelDown, *this));
}

void Mouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

