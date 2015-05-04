#ifndef HELPER_H
#define HELPER_H

#include <Windows.h>
#include <string>
#include "thieves.h"
#include "kings.h"

class Helper
{
public:
	static void initGameWindow(HWND hwnd, char game);
	static void eraseWindow(HWND hwnd);
};

#endif