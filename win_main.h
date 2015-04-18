#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <GdiPlus.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "resource.h"
#include "helper.h"
#include "thieves.h"
#include "kings.h"


///////////////
// Constants //
///////////////

const std::string kClassName = "Things_Main";
const HBRUSH kBackground = CreateSolidBrush(RGB(0,127,0));


/////////////
// Globals //
/////////////

HMENU gMenu = NULL;
HDC gHDC = NULL;
RECT gRect = {0};
std::string winTitle = "Things";


////////////
// States //
////////////

char game = 't';


///////////////
// Functions //
///////////////

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


#endif