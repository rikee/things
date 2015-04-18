#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <GdiPlus.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "helper.h"
#include "thieves.h"
#include "resource.h"


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
HMENU gMenu = NULL;
HDC gHDC = NULL;
RECT gRect = {0};
std::string winTitle = "Things";


////////////
// States //
////////////

char game = 'k';


LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


#endif