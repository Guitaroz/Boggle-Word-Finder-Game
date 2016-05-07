#include"MyConsole.h"

HANDLE Console::out = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::ForegroundColor(ConsoleColor color)
{
	SetConsoleTextAttribute(out, color);
}
void Console::ResetForegroundColor()
{
	SetConsoleTextAttribute(out, Gray);
}

void Console::SetCursorPosition(int left, int top)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	COORD cp = { left, top, };
	SetConsoleCursorPosition(out, cp);
}

void Console::CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO curs;
	GetConsoleCursorInfo(out, &curs);
	if (curs.bVisible == TRUE && visible || curs.bVisible == FALSE && !visible)
		return;
	curs.bVisible = (visible) ? TRUE : FALSE;
	SetConsoleCursorInfo(out, &curs);
}
void Console::Wrap(bool on)
{
	DWORD mode;
	GetConsoleMode(out, &mode);
	if (on)
		mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	else
		mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(out, mode);
}

int Console::WindowWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.X;
}

int Console::WindowHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwSize.Y;
}
int Console::CursorLeft()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.X;
}

int Console::CursorTop()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	return info.dwCursorPosition.Y;
}