#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <GdiPlus.h>
#include <string>
#include "helper.h"
#include "thieves.h"
#include <cstdlib>
#include <ctime>


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


#endif