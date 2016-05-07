#pragma once
#include <Windows.h>

enum ConsoleColor
{
	Black = 0,
	DarkBlue = FOREGROUND_BLUE,
	DarkGreen = FOREGROUND_GREEN,
	DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkRed = FOREGROUND_RED,
	DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
	DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
	Gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	DarkGray = FOREGROUND_INTENSITY,
	Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
	Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

class Console
{
public:
	static HANDLE out;
	static void CursorVisible(bool on);
	static void ForegroundColor(ConsoleColor color);
	static void ResetForegroundColor();
	static void SetCursorPosition(int left, int top);
	static void Wrap(bool on);
	static int WindowWidth();
	static int WindowHeight();
	static int CursorLeft();
	static int CursorTop();
};

