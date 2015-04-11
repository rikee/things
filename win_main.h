#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
//#include <tchar.h>
#include <string>


///////////////
// Constants //
///////////////

const std::string kClassName = "Things_Main";
const HBRUSH kBackground = CreateSolidBrush(RGB(0,127,0));

/////////////
// Globals //
/////////////

int kWinWid = 570;
int kWinHgt = 380;
HDC gHDC = NULL;
RECT gRect = {0};
std::string winTitle = "Things";

////////////
// States //
////////////

char game = 't';


LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

HWND CreateCustomWindow(std::string szClassName, std::string winTitle, int width, int height, HINSTANCE hinstance, HBRUSH background);

#endif