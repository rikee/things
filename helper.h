#ifndef HELPER_H
#define HELPER_H

#include <Windows.h>
#include <string>
#include "resource.h"
#include "thieves.h"
#include "kings.h"

BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

class Helper
{
public:
	static void initGameWindow(HWND hwnd, char game);
	static HWND initDialog(HWND hwnd);
};

#endif